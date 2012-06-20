package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================

enum UserContainsDeviceRelationship implements RelationshipType
{
    CONTAINS_DEVICE
}

// ====================================================

public class UserNode
{
    // ================================================
    
    // should be executed under active transaction
    public static synchronized Node create( Node usersGroupNode , String userLogin , String userPassword , String userName , String description , boolean enabled , UserRights ... rights )
    {
        if( existsByLogin( usersGroupNode , userLogin ) ) throw new RuntimeException( "User with login '" + userLogin + "' already exists." );
        
        Node userNode = usersGroupNode.getGraphDatabase().createNode();
        
        userNode.setProperty( "userLogin" , userLogin );
        userNode.setProperty( "userPassword" , userPassword );
        userNode.setProperty( "userName" , userName );
        userNode.setProperty( "description" , description );
        userNode.setProperty( "enabled" , enabled );
        userNode.setProperty( "creationTime" , System.currentTimeMillis() );
        
        UsersGroupNode.addUserToUsersGroup( userNode );

        for( UserRights right : rights ) UserRightsNode.addRightToUser( userNode , right );
        
        return userNode;
    }
    
    /*
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
    } */

    // ================================================
    
    public static void attachDeviceToUser( Node userNode , Node deviceNode )
    {
        Iterator< Relationship > iter = deviceNode.getRelationships( Direction.OUTGOING , UserContainsDeviceRelationship.values() ).iterator();
        while( iter.hasNext() ) iter.next().delete();
            
        userNode.createRelationshipTo( deviceNode , UserContainsDeviceRelationship.CONTAINS_DEVICE );
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
    public static void delete( Node userNode )
    {   
        Iterator< Relationship > iter = userNode.getRelationships( Direction.OUTGOING , UsersGroup.MEMBER_OF_USERS_GROUP ).iterator();
        while( iter.hasNext() ) iter.next().delete();
        
        iter = userNode.getRelationships( Direction.OUTGOING , UserRights.values() ).iterator();
        while( iter.hasNext() ) iter.next().delete();
        
        iter = userNode.getRelationships( Direction.OUTGOING , UserContainsDeviceRelationship.CONTAINS_DEVICE ).iterator();
        while( iter.hasNext() ) DeviceNode.delete( iter.next().getEndNode() );
        
        userNode.delete();
    }
    
    // ================================================
    
    /*
    // should be executed under active transaction
    public static void deleteAllUsers( Node usersGroupNode )
    {  
        Iterator< Relationship > iter = usersGroupNode.getRelationships( Direction.INCOMING , UsersGroup.MEMBER_OF_USERS_GROUP ).iterator();
        
        while( iter.hasNext() ) delete( iter.next().getStartNode() );
    }*/   
    
    // ================================================
}

// ====================================================