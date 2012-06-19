package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================

enum SystemRightsRelationships implements RelationshipType
{
    SYSTEM_RIGHTS
}

// ====================================================

public class SystemRightsNode
{
    // ================================================
    
    // creates relation SYSTEM_RIGHTS and empty node (as a group of rights)
    // should be executed under active transaction
    public static void createDefaultData( Node intelliHomeNode , boolean addDescriptionProperty )
    {
        Node systemRightsNode = intelliHomeNode.getGraphDatabase().createNode();
        if( addDescriptionProperty ) systemRightsNode.setProperty( "description" , "Singleton node - group of system rights." );
        intelliHomeNode.createRelationshipTo( systemRightsNode , SystemRightsRelationships.SYSTEM_RIGHTS );
    }
    
    // ================================================
    
    // return SYSTEM_RIGHTS relation (between IntelliHome reference node and system rights node) or null (or throws exception if there is more than one)
    public static Relationship getRelationTo( Node intelliHomeNode )
    {
        return intelliHomeNode.getSingleRelationship( SystemRightsRelationships.SYSTEM_RIGHTS , Direction.OUTGOING );
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
    public static void addRightToUser( Node userNode , SystemRights right )
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