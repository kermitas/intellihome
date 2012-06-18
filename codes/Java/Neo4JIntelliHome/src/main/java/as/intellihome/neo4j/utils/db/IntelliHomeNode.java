package as.intellihome.neo4j.utils.db;

import org.neo4j.graphdb.*;

// ====================================================

enum IntelliHomeRelationships implements RelationshipType
{
    INTELLI_HOME
}

// ====================================================

public class IntelliHomeNode
{
    // ================================================
    
    // creates relation INTELLI_HOME and it's node, then create all outgoing relations and nodes
    // should be executed under active transaction
    public static void createDefaultData( GraphDatabaseService graphDb , int majorVersion , int minorVersion )
    {
        Node interlliHomeNode = graphDb.createNode();
        
        interlliHomeNode.setProperty( "majorVersion" , majorVersion );
        interlliHomeNode.setProperty( "minorVersion" , minorVersion );
                
        graphDb.getReferenceNode().createRelationshipTo( interlliHomeNode , IntelliHomeRelationships.INTELLI_HOME );
        
        SystemRightsNode.createDefaultData( interlliHomeNode );
        PhysicalityTypesNode.createDefaultData( interlliHomeNode );
        InSystemLocalizationTypesNode.createDefaultData( interlliHomeNode );
    }
    
    // ================================================
    
    // check if IntelliHome reference node exists
    public static boolean exists( GraphDatabaseService graphDb )
    {
        return graphDb.getReferenceNode().hasRelationship( IntelliHomeRelationships.INTELLI_HOME , Direction.OUTGOING );
    }   
    
    // ================================================
    
    // returns IntelliHome reference node or throws exception
    public static Node get( GraphDatabaseService graphDb )
    {
        Relationship mainRelationshipToIntelliHomeNode = getRelationTo( graphDb );
        
        if( mainRelationshipToIntelliHomeNode != null )
            return mainRelationshipToIntelliHomeNode.getEndNode();
        else
            throw new RuntimeException( "could not find IntelliHome reference node" );
    }   
    
    // ================================================
    
    // returns relation between general reference node and IntelliHome reference node or null (or throws exception if there is more than one)
    public static Relationship getRelationTo( GraphDatabaseService graphDb )
    {
        return graphDb.getReferenceNode().getSingleRelationship( IntelliHomeRelationships.INTELLI_HOME , Direction.OUTGOING );
    }
    
    // ================================================
    
    // delete main incomming relation this node and all outgoing
    // should be executed under active transaction
    public static void delete( GraphDatabaseService graphDb )
    {
        Relationship mainRelationshipToIntelliHomeNode = getRelationTo( graphDb );

        if( mainRelationshipToIntelliHomeNode != null )
        {
            Node intelliHomeNode = mainRelationshipToIntelliHomeNode.getEndNode();

            StartupNode.delete( intelliHomeNode );
            SystemRightsNode.delete( intelliHomeNode );
            PhysicalityTypesNode.delete( intelliHomeNode );
            InSystemLocalizationTypesNode.delete( intelliHomeNode );
            
            //System.out.println( IntelliHomeNode.class.getName() + ": deleting node " + intelliHomeNode.getId() );
            //System.out.println( IntelliHomeNode.class.getName() + ": deleting reference " + mainRelationshipToIntelliHomeNode.getId() );
            
            mainRelationshipToIntelliHomeNode.delete();
            intelliHomeNode.delete();
        }
    }
    
    // ================================================
}

// ====================================================