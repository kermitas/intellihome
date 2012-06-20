package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import java.util.Random;
import org.neo4j.graphdb.Direction;
import org.neo4j.graphdb.GraphDatabaseService;
import org.neo4j.graphdb.Node;
import org.neo4j.graphdb.Relationship;

// ====================================================

public class UserNode
{
    // ================================================
    
    // should be executed under active transaction
    public static synchronized Node createUserNode( Node usersGroupNode , boolean addDescriptionProperty , String userName , String userLogin , String userPassword , boolean enabled , UserRights ... rights )
    {
        if( existsByLogin( usersGroupNode , userLogin ) ) throw new RuntimeException( "User with login '" + userLogin + "' already exists." );
        
        Node userNode = usersGroupNode.getGraphDatabase().createNode();
        
        userNode.setProperty( "id" , generateUniqueUserId( usersGroupNode ) );
        userNode.setProperty( "userName" , userName );
        userNode.setProperty( "userLogin" , userLogin );
        userNode.setProperty( "userPassword" , userPassword );
        userNode.setProperty( "enabled" , enabled );
        userNode.setProperty( "creationTime" , System.currentTimeMillis() );
        if( addDescriptionProperty ) userNode.setProperty( "description" , "This node represents a user." );
        
        UsersGroupNode.addUserToUsersGroup( userNode );

        for( UserRights right : rights ) UserRightsNode.addRightToUser( userNode , right );
        
        return userNode;
    }
    
    // ================================================
    
    private static int generateUniqueUserId( Node usersGroupNode )
    {
        Random r = new Random();
        
        int id = r.nextInt( Integer.MAX_VALUE );
        
        while( !isUniqueUserId( id , usersGroupNode ) ) id = r.nextInt( Integer.MAX_VALUE );
        
        return id;
    }
    
    // ================================================
    
    private static boolean isUniqueUserId( int id , Node usersGroupNode )
    {
        Iterator< Relationship > iter = usersGroupNode.getRelationships( Direction.INCOMING , UsersGroup.MEMBER_OF_USERS_GROUP ).iterator();
        
        while( iter.hasNext() )
        {
            Relationship r = iter.next();
            Node n = r.getStartNode();
            
            if( n.getProperty( "id" ).equals( id ) ) return false;
        }
        
        return true;
    } 

    // ================================================
    
    public static boolean existsByLogin( GraphDatabaseService graphDb , String userLogin )
    {   
        return existsByLogin( UsersGroupNode.get( graphDb ) , userLogin );
    }
    
    // ================================================
    
    public static boolean existsByLogin( Node usersGroupNode , String userLogin )
    {   
        Iterator< Relationship > iter = usersGroupNode.getRelationships( Direction.INCOMING , UsersGroup.MEMBER_OF_USERS_GROUP ).iterator();
        
        while( iter.hasNext() )
        {
            Relationship r = iter.next();
            Node n = r.getStartNode();
            
            if( userLogin.equals( n.getProperty( "userLogin" ) ) ) return true;
        }
        
        return false;
    }
    
    // ================================================
    
    // should be executed under active transaction
    public static void deleteUser( Node userNode )
    {   
        Iterator< Relationship > iter = userNode.getRelationships( Direction.OUTGOING , UsersGroup.MEMBER_OF_USERS_GROUP ).iterator();
        while( iter.hasNext() ) iter.next().delete();
        
        iter = userNode.getRelationships( Direction.OUTGOING , UserRights.values() ).iterator();
        while( iter.hasNext() ) iter.next().delete();
        
        userNode.delete();
    }
    
    // ================================================
    
    // should be executed under active transaction
    public static void deleteAllUsers( Node usersGroupNode )
    {  
        Iterator< Relationship > iter = usersGroupNode.getRelationships( Direction.INCOMING , UsersGroup.MEMBER_OF_USERS_GROUP ).iterator();
        
        while( iter.hasNext() ) deleteUser( iter.next().getStartNode() );
    }   
    
    // ================================================
}

// ====================================================