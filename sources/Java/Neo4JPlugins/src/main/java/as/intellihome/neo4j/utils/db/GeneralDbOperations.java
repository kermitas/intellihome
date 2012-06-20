package as.intellihome.neo4j.utils.db;

import as.intellihome.neo4j.Config;
import org.neo4j.graphdb.GraphDatabaseService;
import org.neo4j.graphdb.Node;
import org.neo4j.graphdb.Transaction;

// ====================================================

public class GeneralDbOperations
{
    // ================================================
    
    public static void createDb( GraphDatabaseService graphDb )
    {
        if( IntelliHomeNode.exists( graphDb ) )
        {
            throw new IllegalStateException( "database already contains IntelliHome graph" );
        }   
        else
        {
            Transaction tx = graphDb.beginTx();
            try
            {
                IntelliHomeNode.createDefaultData( graphDb , Config.addDescriptionPropertyToNodes , Config.interlliHomeMajorVersion , Config.interlliHomeMinorVersion );
                
                tx.success();
            }
            finally
            {
                tx.finish();
            }            
        }
    }   
    
    // ================================================
    
    public static void addDefaultDataToDb( GraphDatabaseService graphDb )
    {
        if( !UserNode.existsByLogin( graphDb , "as" ) )
        {
            Transaction tx = graphDb.beginTx();
            try
            {

                UserRights[] rights = { UserRights.CAN_LOGIN_TO_ADMIN , UserRights.CAN_CREATE_DEVICE , UserRights.CAN_CREATE_SENSOR };
                Node userNode = createUserUnderActiveTransaction( graphDb , Config.addDescriptionPropertyToNodes , "Default User" , "as" , "as1" , true , rights );

                // TODO

                // add device to this users
                // add temperature sensor to this device
                // add few temperature samples

                tx.success();
            }
            finally
            {
                tx.finish();
            }  
        }     
        else
        {
            throw new RuntimeException( "Default data already exists." );
        }
    }
    
    // ================================================
    
    public static void deleteDb( GraphDatabaseService graphDb )
    {
        // TODO execute some kind of query that deletes all nodes and relations but omit ReferenceNode
        
        Transaction tx = graphDb.beginTx();
        try
        {
            IntelliHomeNode.delete( graphDb );
            
            tx.success();
        }
        finally
        {
            tx.finish();
        }         
    }
    
    // ================================================
    
    public static Node createUser( GraphDatabaseService graphDb , String userName , String userLogin , String userPassword , boolean enabled , UserRights ... rights )
    {
        Transaction tx = graphDb.beginTx();
        try
        {
            Node userNode = createUserUnderActiveTransaction( graphDb , Config.addDescriptionPropertyToNodes , userName , userLogin , userPassword , enabled , rights );
            
            tx.success();
            
            return userNode;
        }
        finally
        {
            tx.finish();
        }         
    }
    
    // ================================================
    
    private static Node createUserUnderActiveTransaction( GraphDatabaseService graphDb , boolean addDescriptionPropertyToNodes , String userName , String userLogin , String userPassword , boolean enabled , UserRights ... rights )
    {
        return UserNode.createUserNode( UsersGroupNode.get( graphDb ) , addDescriptionPropertyToNodes , userName , userLogin , userPassword , enabled , rights );         
    }
    
    // ================================================
}

// ====================================================