package as.intellihome.neo4j.utils.db;

import org.neo4j.graphdb.*;

// ====================================================

enum ServerStartupRelationships implements RelationshipType
{
    LATEST_STARTUP , PREVIOUS_STARTUP
}

// ====================================================

public class StartupNode
{
    // ================================================
    
    // return LATEST_STARTUP relation (between IntelliHome reference node and latest startup node) or null (or throws exception if there is more than one)
    public static Relationship getRelationTo( Node intelliHomeNode )
    {
        return intelliHomeNode.getSingleRelationship( ServerStartupRelationships.LATEST_STARTUP , Direction.OUTGOING );
    }   
    
    // ================================================
    
    // creates new Startup node with creation time
    // connects it with IntelliHome node using LATEST_STARTUP relation
    // then connect to this newly created node previous Startup node using PREVIOUS_STARTUP and removes old LATEST_STARTUP relation
    public static void addNewStartupNode( Node intelliHomeNode )
    {
        Transaction tx = intelliHomeNode.getGraphDatabase().beginTx();
        try
        {
            Node latestStartupNode = intelliHomeNode.getGraphDatabase().createNode();
            latestStartupNode.setProperty( "startupTime" , System.currentTimeMillis() );
            
            Relationship currentRelationToLatestStartupNode = getRelationTo( intelliHomeNode );
            
            if( currentRelationToLatestStartupNode != null )
            {
                Node currentLatestStartupNode = currentRelationToLatestStartupNode.getEndNode();
                
                intelliHomeNode.createRelationshipTo( latestStartupNode , ServerStartupRelationships.LATEST_STARTUP );
                
                currentLatestStartupNode.createRelationshipTo( latestStartupNode , ServerStartupRelationships.PREVIOUS_STARTUP );
                
                currentRelationToLatestStartupNode.delete();
            }
            else
            {
                intelliHomeNode.createRelationshipTo( latestStartupNode , ServerStartupRelationships.LATEST_STARTUP );
            }

            tx.success();
        }
        finally
        {
            tx.finish();
        }  
    }
    
    // ================================================
    
    // add property 'shutdownTime' to LATEST_STARTUP node
    public static void setShutdownTime( Node intelliHomeNode )
    {
        Transaction tx = intelliHomeNode.getGraphDatabase().beginTx();
        try
        {
            Relationship currentRelationToLatestStartupNode = getRelationTo( intelliHomeNode );
            
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
    
    // delete main incomming relation and whole "startup time" linked list
    // should be executed under active transaction
    public static void delete( Node intelliHomeNode )
    {
        Relationship latestStartupReference = getRelationTo( intelliHomeNode );

        if( latestStartupReference != null )
        {
            Node latestStartupNode = latestStartupReference.getEndNode();

            Relationship prevStartupReference = latestStartupNode.getSingleRelationship( ServerStartupRelationships.PREVIOUS_STARTUP , Direction.INCOMING );

            latestStartupReference.delete();
            latestStartupNode.delete();

            while( prevStartupReference != null )
            {
                latestStartupNode = prevStartupReference.getStartNode();

                prevStartupReference.delete();

                prevStartupReference = latestStartupNode.getSingleRelationship( ServerStartupRelationships.PREVIOUS_STARTUP , Direction.INCOMING );

                latestStartupNode.delete();
            }
        }
    }
    
    // ================================================
}

// ====================================================