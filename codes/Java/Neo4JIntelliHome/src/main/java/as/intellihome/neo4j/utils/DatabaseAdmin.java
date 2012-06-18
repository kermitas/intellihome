package as.intellihome.neo4j.utils;

import as.intellihome.Config;
import org.neo4j.graphdb.*;

// ====================================================

public class DatabaseAdmin
{
    // ================================================
    
    private static enum RelationshipTypes implements RelationshipType
    {
        INTELLI_HOME , LATEST_STARTUP , PREV_STARTUP
    }
 
    // ================================================
    
    public static void createDb( GraphDatabaseService graphDb )
    {
        if( doDbContainsIntelliHomeGraph( graphDb ) )
        {
            throw new IllegalStateException( "database already contains IntelliHome graph" );
        }   
        else
        {
            Transaction tx = graphDb.beginTx();
            try
            {
                Node intelliHomeReferenceNode = graphDb.createNode();
                
                intelliHomeReferenceNode.setProperty( "majorVersion" , Config.interlliHomeMajorVersion );
                intelliHomeReferenceNode.setProperty( "minorVersion" , Config.interlliHomeMinorVersion );
                
                graphDb.getReferenceNode().createRelationshipTo( intelliHomeReferenceNode , RelationshipTypes.INTELLI_HOME );
                
                tx.success();
            }
            finally
            {
                tx.finish();
            }            
        }
    }   
    
    // ================================================
    
    public static boolean doDbContainsIntelliHomeGraph( GraphDatabaseService graphDb )
    {
        return graphDb.getReferenceNode().hasRelationship( RelationshipTypes.INTELLI_HOME , Direction.OUTGOING );
    }
    
    // ================================================
    
    public static void addNewIntelliHomeSystemStartupTime( GraphDatabaseService graphDb )
    {
        Transaction tx = graphDb.beginTx();
        try
        {
            Node intelliHomeReferenceNode = getIntelliHomeReferenceNode( graphDb );
            
            Node latestStartupNode = graphDb.createNode();
            latestStartupNode.setProperty( "startupTime" , System.currentTimeMillis() );
            
            Relationship currentRelationToLatestStartupNode = intelliHomeReferenceNode.getSingleRelationship( RelationshipTypes.LATEST_STARTUP , Direction.OUTGOING );
            
            if( currentRelationToLatestStartupNode != null )
            {
                Node currentLatestStartupNode = currentRelationToLatestStartupNode.getEndNode();
                
                intelliHomeReferenceNode.createRelationshipTo( latestStartupNode , RelationshipTypes.LATEST_STARTUP );
                
                currentLatestStartupNode.createRelationshipTo( latestStartupNode , RelationshipTypes.PREV_STARTUP );
                
                currentRelationToLatestStartupNode.delete();
            }
            else
            {
                intelliHomeReferenceNode.createRelationshipTo( latestStartupNode , RelationshipTypes.LATEST_STARTUP );
            }

            tx.success();
        }
        finally
        {
            tx.finish();
        }  
    }
    
    // ================================================
    
    public static void addNewIntelliHomeSystemShutdownTime( GraphDatabaseService graphDb )
    {
        Transaction tx = graphDb.beginTx();
        try
        {
            Node intelliHomeReferenceNode = getIntelliHomeReferenceNode( graphDb );
            Relationship currentRelationToLatestStartupNode = intelliHomeReferenceNode.getSingleRelationship( RelationshipTypes.LATEST_STARTUP , Direction.OUTGOING );
            
            if( currentRelationToLatestStartupNode != null )
            {
                Node latestStartupNode = currentRelationToLatestStartupNode.getEndNode();
                latestStartupNode.setProperty( "shutdownTime" , System.currentTimeMillis() );
            }
            
            tx.success();
        }
        finally
        {
            tx.finish();
        }  
    }   
    
    // ================================================
    
    private static Node getIntelliHomeReferenceNode( GraphDatabaseService graphDb )
    {
        Relationship mainRelationshipToIntelliHomeReferenceNode = graphDb.getReferenceNode().getSingleRelationship( RelationshipTypes.INTELLI_HOME , Direction.OUTGOING );
        
        if( mainRelationshipToIntelliHomeReferenceNode != null )
            return mainRelationshipToIntelliHomeReferenceNode.getEndNode();
        else
            throw new RuntimeException( "could not find IntelliHomeReferenceNode" );
    }   
    
    // ================================================
    
    public static void addDefaultDataToDb( GraphDatabaseService graphDb )
    {
        // TODO
        
        // check somehow if default data is already added? how? for example check if user with login "DefaultUser" exists
        
        // add user 'DefaultUser'
        // add device to this users
        // add temperature sensor to this device
        // add few temperature samples
        
        throw new UnsupportedOperationException( "not implemented yet" );      
    }
    
    // ================================================
    
    public static void deleteDb( GraphDatabaseService graphDb )
    {
        // TODO execute some kind of query that deletes all nodes and relations but omit ReferenceNode
        
        Transaction tx = graphDb.beginTx();
        try
        {
            Relationship mainRelationshipToIntelliHomeReferenceNode = graphDb.getReferenceNode().getSingleRelationship( RelationshipTypes.INTELLI_HOME , Direction.OUTGOING );
     
            if( mainRelationshipToIntelliHomeReferenceNode != null )
            {
                Node intelliHomeReferenceNode = mainRelationshipToIntelliHomeReferenceNode.getEndNode();

                Relationship latestStartupReference = intelliHomeReferenceNode.getSingleRelationship( RelationshipTypes.LATEST_STARTUP , Direction.OUTGOING );
                if( latestStartupReference != null )
                {
                    Node latestStartupNode = latestStartupReference.getEndNode();

                    Relationship prevStartupReference = latestStartupNode.getSingleRelationship( RelationshipTypes.PREV_STARTUP , Direction.INCOMING );

                    latestStartupReference.delete();
                    latestStartupNode.delete();
                    
                    while( prevStartupReference != null )
                    {
                        latestStartupNode = prevStartupReference.getStartNode();

                        prevStartupReference.delete();

                        prevStartupReference = latestStartupNode.getSingleRelationship( RelationshipTypes.PREV_STARTUP , Direction.INCOMING );

                        latestStartupNode.delete();
                    }
                }

                mainRelationshipToIntelliHomeReferenceNode.delete();
                intelliHomeReferenceNode.delete();
            }
            
            tx.success();
        }
        finally
        {
            tx.finish();
        }         
    }
    
    // ================================================
}

// ====================================================