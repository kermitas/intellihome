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
        if( !UserNode.existsByLogin( graphDb , Config.defaultUserNameAddedViaAddDefaultDataToDb ) )
        {
            Transaction tx = graphDb.beginTx();
            try
            {

                UserRights[] rights = { UserRights.CAN_LOGIN_TO_ADMIN , UserRights.CAN_CREATE_DEVICE , UserRights.CAN_CREATE_SENSOR };
                Node userNode = createUserUnderActiveTransaction( graphDb , "John Doe" , Config.defaultUserNameAddedViaAddDefaultDataToDb , Config.defaultUserNameAddedViaAddDefaultDataToDb+"pass" , "This is testing user" , true , rights );

                Node deviceNode = DeviceNode.create( DevicesGroupNode.get( graphDb ) , userNode , "Arduino(test)" , "This is testing arduino" , true , PhysicalityTypes.VIRTUAL , DataIncomeTypes.DEVICE_PUSH , InSystemLocalizationTypes.END_POINT , "laptop" , "laptio on my desk" , 0.1d , 0.2d , 0.3d );

                Node temperatureSensorNode = SensorNode.create( SensorsGroupNode.get( graphDb ) , deviceNode , "temperature" , "Temperature sensor DS18B20" , true , PhysicalityTypes.VIRTUAL , DataCollectingTypes.UNLIMITED_APPEND , DoorLocalizationTypes.INDOOR , SensorDataTypes.FLOAT , "computer" , "computer in blue room" , 1.2d , 2.3d , 3.4d );
                
                // TODO

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
    
    public static Node createUser( GraphDatabaseService graphDb , String userLogin , String userPassword , String userName , String description , boolean enabled , UserRights ... rights )
    {
        Transaction tx = graphDb.beginTx();
        try
        {
            Node userNode = createUserUnderActiveTransaction( graphDb , userLogin , userPassword , userName , description , enabled , rights );
            
            tx.success();
            
            return userNode;
        }
        finally
        {
            tx.finish();
        }         
    }
    
    // ================================================
    
    private static Node createUserUnderActiveTransaction( GraphDatabaseService graphDb , String userLogin , String userPassword , String userName , String description , boolean enabled , UserRights ... rights )
    {
        return UserNode.create( UsersGroupNode.get( graphDb ) , userLogin , userPassword , userName , description , enabled , rights );         
    }
    
    // ================================================
    
    public static Node createDevice( GraphDatabaseService graphDb , Node ownerUserNode , String name , String description , boolean enabled , PhysicalityTypes physicalityType , DataIncomeTypes dataIncomeType , InSystemLocalizationTypes inSystemLocalizationType , String locationName , String locationDescription , Double locationX , Double locationY , Double locationZ )
    {
        Transaction tx = graphDb.beginTx();
        try
        {
            Node deviceNode = createDeviceUnderActiveTransaction( graphDb , ownerUserNode , name , description , enabled , physicalityType , dataIncomeType , inSystemLocalizationType , locationName , locationDescription , locationX , locationY , locationZ );
            
            tx.success();
            
            return deviceNode;
        }
        finally
        {
            tx.finish();
        }         
    }
    
    // ================================================
    
    private static Node createDeviceUnderActiveTransaction( GraphDatabaseService graphDb , Node ownerUserNode , String name , String description , boolean enabled , PhysicalityTypes physicalityType , DataIncomeTypes dataIncomeType , InSystemLocalizationTypes inSystemLocalizationType , String locationName , String locationDescription , Double locationX , Double locationY , Double locationZ )
    {
        return DeviceNode.create( DevicesGroupNode.get( graphDb ) , ownerUserNode , name , description , enabled , physicalityType , dataIncomeType , inSystemLocalizationType , locationName , locationDescription , locationX , locationY , locationZ );         
    }
    
    // ================================================
}

// ====================================================