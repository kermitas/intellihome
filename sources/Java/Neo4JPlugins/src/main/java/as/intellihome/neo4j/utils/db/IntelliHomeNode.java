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
    public static void createDefaultData( GraphDatabaseService graphDb , boolean addDescriptionProperty , int majorVersion , int minorVersion )
    {
        Node intelliHomeNode = graphDb.createNode();
        
        if( addDescriptionProperty ) intelliHomeNode.setProperty( "description" , "IntelliHome main node." );
        intelliHomeNode.setProperty( "majorVersion" , majorVersion );
        intelliHomeNode.setProperty( "minorVersion" , minorVersion );
                
        graphDb.getReferenceNode().createRelationshipTo( intelliHomeNode , IntelliHomeRelationships.INTELLI_HOME );
        
        UserRightsNode.createDefaultData( intelliHomeNode , addDescriptionProperty );
        PhysicalityTypesNode.createDefaultData( intelliHomeNode , addDescriptionProperty );
        InSystemLocalizationTypesNode.createDefaultData( intelliHomeNode , addDescriptionProperty );
        DataIncomeTypesNode.createDefaultData( intelliHomeNode , addDescriptionProperty );
        DataCollectingTypesNode.createDefaultData( intelliHomeNode , addDescriptionProperty );
        SensorsGroupNode.createDefaultData( intelliHomeNode , addDescriptionProperty );
        DevicesGroupNode.createDefaultData( intelliHomeNode , addDescriptionProperty );
        UsersGroupNode.createDefaultData( intelliHomeNode , addDescriptionProperty );
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
            UserRightsNode.delete( intelliHomeNode );
            PhysicalityTypesNode.delete( intelliHomeNode );
            InSystemLocalizationTypesNode.delete( intelliHomeNode );
            DataIncomeTypesNode.delete( intelliHomeNode );
            DataCollectingTypesNode.delete( intelliHomeNode );
            SensorsGroupNode.delete( intelliHomeNode );
            DevicesGroupNode.delete( intelliHomeNode );
            
            UserNode.deleteAllUsers( UsersGroupNode.get( graphDb ) );
            UsersGroupNode.delete( intelliHomeNode );  
            
            mainRelationshipToIntelliHomeNode.delete();
            intelliHomeNode.delete();
        }
        else
        {
            throw new RuntimeException( "database does not contain IntelliHome reference node" );
        }
    }
    
    // ================================================
}

// ====================================================