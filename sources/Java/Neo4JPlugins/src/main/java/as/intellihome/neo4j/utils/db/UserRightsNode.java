package as.intellihome.neo4j.utils.db;

import org.neo4j.graphdb.*;

// ====================================================

enum UserRightsRelationships implements RelationshipType
{
    USER_RIGHTS_GROUP
}

// ====================================================

public class UserRightsNode
{
    // ================================================
    
    // creates relation SYSTEM_RIGHTS and empty node (as a group of rights)
    // should be executed under active transaction
    public static void createDefaultData( Node intelliHomeNode , boolean addDescriptionProperty )
    {
        Node systemRightsNode = intelliHomeNode.getGraphDatabase().createNode();
        if( addDescriptionProperty ) systemRightsNode.setProperty( "description" , "Singleton node - group of system rights." );
        intelliHomeNode.createRelationshipTo( systemRightsNode , UserRightsRelationships.USER_RIGHTS_GROUP );
    }
    
    // ================================================
    
    // return SYSTEM_RIGHTS relation (between IntelliHome reference node and system rights node) or null (or throws exception if there is more than one)
    public static Relationship getRelationTo( Node intelliHomeNode )
    {
        return intelliHomeNode.getSingleRelationship( UserRightsRelationships.USER_RIGHTS_GROUP , Direction.OUTGOING );
    }   
    
    // ================================================
    
    public static Node get( GraphDatabaseService graphDb )
    {
        return get( IntelliHomeNode.get( graphDb ) );
    }  
    
    // ================================================
    
    public static Node get( Node intelliHomeNode )
    {
        return getRelationTo( intelliHomeNode ).getEndNode();
    }      
    
    // ================================================
    
    // should be executed under active transaction
    public static void addRightToUser( Node userNode , UserRights right )
    {
        if( !userNode.hasRelationship( Direction.OUTGOING , right ) )
        {
            userNode.createRelationshipTo( get( userNode.getGraphDatabase() ) , right );
        }
    }
    
    // ================================================
    
    // delete main incomming relation, this node
    // should be executed under active transaction
    public static void delete( Node intelliHomeNode )
    {   
        Relationship systemRightsRelationship = getRelationTo( intelliHomeNode );

        if( systemRightsRelationship != null )
        {
            Node systemRightsNode = systemRightsRelationship.getEndNode();
  
            systemRightsRelationship.delete();
            systemRightsNode.delete();
        }         
    }
    
    // ================================================
}

// ====================================================