package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================

enum UsersGroupRelationship implements RelationshipType
{
    USERS_GROUP
}

// ====================================================

public class UsersGroupNode
{
    // ================================================
    
    // creates relation USERS_GROUP and empty node (as a group of sensor data types)
    // should be executed under active transaction
    public static void createDefaultData( Node intelliHomeNode , boolean addDescriptionProperty )
    {
        Node usersGroupNode = intelliHomeNode.getGraphDatabase().createNode();
        if( addDescriptionProperty ) usersGroupNode.setProperty( "description" , "Singleton node - group for all users." );
        intelliHomeNode.createRelationshipTo( usersGroupNode , UsersGroupRelationship.USERS_GROUP );
    }
    
    // ================================================
    
    // return USERS_GROUP relation (outgoing form IntelliHome) or null (or throws exception if there is more than one)
    public static Relationship getRelationTo( Node intelliHomeNode )
    {
        return intelliHomeNode.getSingleRelationship( UsersGroupRelationship.USERS_GROUP , Direction.OUTGOING );
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
    public static void addUserToUsersGroup( Node userNode )
    {
        if( !isUserInUsersGroup( userNode ) )
        {   
            userNode.createRelationshipTo( get( userNode.getGraphDatabase() ) , UsersGroup.MEMBER_OF_USERS_GROUP );
        }
    }
    
    // ================================================
    
    public static boolean isUserInUsersGroup( Node userNode )
    {
        return userNode.hasRelationship( Direction.OUTGOING , UsersGroup.MEMBER_OF_USERS_GROUP );
    } 
    
    // ================================================
    
    // delete main incomming relation, this node
    // should be executed under active transaction
    public static void delete( Node intelliHomeNode )
    {   
        Relationship usersGroupReference = getRelationTo( intelliHomeNode );

        if( usersGroupReference != null )
        {
            Node usersGroupNode = usersGroupReference.getEndNode();

            Iterator< Relationship > iter = usersGroupNode.getRelationships( Direction.INCOMING , UsersGroup.MEMBER_OF_USERS_GROUP ).iterator();
            while( iter.hasNext() ) UserNode.delete( iter.next().getStartNode() );
        
            usersGroupReference.delete();
            usersGroupNode.delete();
        }  
    }
    
    // ================================================
}

// ====================================================