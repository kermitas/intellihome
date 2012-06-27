package as.intellihome.neo4j;

import as.intellihome.neo4j.Config;
import as.intellihome.neo4j.objects.IntelliHome;
import as.intellihome.neo4j.objects.Relations;
import org.neo4j.graphdb.GraphDatabaseService;
import org.neo4j.graphdb.Node;
import org.neo4j.graphdb.Transaction;

// ====================================================

public class Operations
{
    private static boolean isInstalled = false;
    
    // ================================================
    
    public static synchronized void install( GraphDatabaseService graphDb )
    {
        if( !isInstalled )
        {
            IntelliHome ih = as.intellihome.neo4j.objects.IntelliHomeGeneral.getOrCreate( graphDb );
            ih.addNewStartupTime();
            
            // TODO maybe install graphDb.registerTransactionEventHandler( )
            
            isInstalled = true;
        }
        else
            throw new IllegalStateException( "already installed" );
    }
    
    // ================================================
    
    public static void shutdown( final GraphDatabaseService graphDb )
    {
        try
        { 
            if( as.intellihome.neo4j.objects.IntelliHomeGeneral.exists( graphDb ) )
            {
                IntelliHome ih = as.intellihome.neo4j.objects.IntelliHomeGeneral.getOrCreate( graphDb );
                ih.setShutdownTime();
            }
        }
        catch (Exception e) { }
        
        Thread t = new Thread()
        {
            @Override
            public void run()
            {
                //try { Thread.sleep( 1000 ); } catch (InterruptedException ie) { }
                
                graphDb.shutdown();
                
                try { Thread.sleep( as.intellihome.neo4j.Config.shutdownWaitTimeBeforeExecutionSystemExit ); } catch (InterruptedException ie) { }
                
                System.exit( 0 );
            }
        };
        
        t.setDaemon( true );
        t.start();
    }    
    
    // ================================================
    
    public static void addDefaultDataToDb( GraphDatabaseService graphDb )
    {
        if( as.intellihome.neo4j.objects.IntelliHomeGeneral.exists( graphDb ) )
        {
            Transaction tx = graphDb.beginTx();
            try
            {            
                IntelliHome ih = as.intellihome.neo4j.objects.IntelliHomeGeneral.getOrCreate( graphDb );

                as.intellihome.neo4j.objects.Relations.UserRight[] userRights = { as.intellihome.neo4j.objects.Relations.UserRight.CAN_LOGIN_TO_ADMIN };
                as.intellihome.neo4j.objects.User user = ih.createUser( Config.defaultUserNameAddedViaAddDefaultDataToDb , Config.defaultUserNameAddedViaAddDefaultDataToDb+"_pass" , Config.defaultUserNameAddedViaAddDefaultDataToDb+"_name" , Config.defaultUserNameAddedViaAddDefaultDataToDb+"_descr" , true , userRights );

                as.intellihome.neo4j.objects.Device device = user.createDevice( "test_device" , "This is a test device" , true , Relations.PhysicalityType.VIRTUAL , Relations.DataIncomeType.DEVICE_PUSH , Relations.InSystemLocalizationType.END_POINT , "laptop" , "Inside laptop on my desk." , 1.1d, 2.2d , 3.3d );

                Relations.DataCollectingType dct = Relations.DataCollectingType.getAppendLimitedByCount( 100 , Relations.DataCollectingLimitExceededAction.REMOVE_OLDEST );

                Relations.SensorDataType sdt = Relations.SensorDataType.STRING;
                Relations.SensorDataType.setMinLimit( sdt , 10  , Relations.SensorDataLimitExceededAction.TRIM );
                sdt.max = 150l;        

                as.intellihome.neo4j.objects.Sensor sensor = device.createSensor( "temperature" , "Temperature from Dallas DS18B20." , true , Relations.PhysicalityType.VIRTUAL ,  dct , Relations.DoorLocalizationType.INDOOR , sdt , "computer" , "Computer under my desk." , 5.5d , 6.6d , 7.7d ); 
       
                sensor.createSensorSample( "val1" );
                sensor.createSensorSample( "val2" );
                sensor.createSensorSample( "val3" );
                
                tx.success();
            }
            finally
            {
                tx.finish();
            }             
        }
        else
            throw new RuntimeException( "Database does not exists." );
    }
    
    // ================================================
    
    public static void deleteDb( GraphDatabaseService graphDb )
    {
        if( as.intellihome.neo4j.objects.IntelliHomeGeneral.exists( graphDb ) )
        {
            IntelliHome ih = as.intellihome.neo4j.objects.IntelliHomeGeneral.getOrCreate( graphDb );
            ih.delete(); 
        }
        else
            throw new RuntimeException( "Database does not exists." );
    }  
    
    // ================================================
    
    public static as.intellihome.neo4j.objects.User createUser( GraphDatabaseService graphDb , String login , String password , String name , String description , boolean enable , String[] userRightsAsStringArray )
    {
        as.intellihome.neo4j.objects.Relations.UserRight[] userRights = new as.intellihome.neo4j.objects.Relations.UserRight[ userRightsAsStringArray.length ];   
        for( int i = 0 ; i < userRights.length ; i++ ) userRights[ i ] = as.intellihome.neo4j.objects.Relations.UserRight.valueOf( userRightsAsStringArray[ i ] );            
            
        if( as.intellihome.neo4j.objects.IntelliHomeGeneral.exists( graphDb ) )
        {            
            IntelliHome ih = as.intellihome.neo4j.objects.IntelliHomeGeneral.getOrCreate( graphDb );
            return ih.createUser(login, password, name, description, enable, userRights);
        }
        else
            throw new RuntimeException( "Database does not exists." );
    }    
    
    // ================================================
    
    public static as.intellihome.neo4j.objects.Device createDevice( Node ownerUserNode , String name , String description , boolean enabled , String physicalityTypeAsString , String dataIncomeTypeAsString , String inSystemLocalizationTypeAsString , String locationName , String locationDescription , double locationX , double locationY , double locationZ )
    {
        as.intellihome.neo4j.objects.Relations.PhysicalityType pt = as.intellihome.neo4j.objects.Relations.PhysicalityType.valueOf( physicalityTypeAsString );
        as.intellihome.neo4j.objects.Relations.DataIncomeType dit = as.intellihome.neo4j.objects.Relations.DataIncomeType.valueOf( dataIncomeTypeAsString  );
        as.intellihome.neo4j.objects.Relations.InSystemLocalizationType islt = as.intellihome.neo4j.objects.Relations.InSystemLocalizationType.valueOf( inSystemLocalizationTypeAsString );
            
        if( as.intellihome.neo4j.objects.IntelliHomeGeneral.exists( ownerUserNode.getGraphDatabase() ) )
        {
            as.intellihome.neo4j.objects.User user = new as.intellihome.neo4j.objects.impl.User( ownerUserNode );

            as.intellihome.neo4j.objects.Device device = user.createDevice( name , description , enabled , pt , dit , islt , locationName , locationDescription , locationX , locationY , locationZ );
            
            return device;
        }
        else
            throw new RuntimeException( "Database does not exists." );
    } 
    
    // ================================================
    
    public static as.intellihome.neo4j.objects.Sensor createSensor( Node ownerDeviceNode , String name , String description , boolean enabled , String physicalityTypeAsString , String dataCollectingTypeAsString , String doorLocalizationTypeAsString , String sensorDataTypeAsString , String locationName , String locationDescription , double locationX , double locationY , double locationZ )
    {
        as.intellihome.neo4j.objects.Relations.PhysicalityType pt = as.intellihome.neo4j.objects.Relations.PhysicalityType.valueOf( physicalityTypeAsString );
        as.intellihome.neo4j.objects.Relations.DataCollectingType dct = as.intellihome.neo4j.objects.Relations.DataCollectingType.valueOf( dataCollectingTypeAsString  );
        as.intellihome.neo4j.objects.Relations.DoorLocalizationType dlt = as.intellihome.neo4j.objects.Relations.DoorLocalizationType.valueOf( doorLocalizationTypeAsString );
        as.intellihome.neo4j.objects.Relations.SensorDataType sdt = as.intellihome.neo4j.objects.Relations.SensorDataType.valueOf( sensorDataTypeAsString );
            
        if( as.intellihome.neo4j.objects.IntelliHomeGeneral.exists( ownerDeviceNode.getGraphDatabase() ) )
        {
            as.intellihome.neo4j.objects.Device device = new as.intellihome.neo4j.objects.impl.Device( ownerDeviceNode );

            as.intellihome.neo4j.objects.Sensor sensor = device.createSensor( name , description , enabled , pt , dct , dlt , sdt , locationName , locationDescription , locationX , locationY , locationZ );
            
            return sensor;
        }
        else
            throw new RuntimeException( "Database does not exists." );
    }  
    
    // ================================================
    
    public static as.intellihome.neo4j.objects.SensorSample createSensorSample( Node sensorNode , Object sample )
    { 
        //validateSensorValueObjectType( sample );
        
        if( as.intellihome.neo4j.objects.IntelliHomeGeneral.exists( sensorNode.getGraphDatabase() ) )
        {
            // TODO check if user is enabled
            // TODO check if device is enabled
            // TODO check if sensor is enabled
            // TODO check data type that collects this sensor and check incomming sample type
            
            as.intellihome.neo4j.objects.Sensor sensor = new as.intellihome.neo4j.objects.impl.Sensor( sensorNode );

            as.intellihome.neo4j.objects.SensorSample sensorSample = sensor.createSensorSample( sample );
            
            return sensorSample;
        }
        else
            throw new RuntimeException( "Database does not exists." );
    }    
    
    /*
    // ================================================
    
    private static void validateSensorValueObjectType( Object sample )
    {
        if(
            !( sample instanceof Boolean ) ||
            !( sample instanceof String ) ||
            !( sample instanceof Character ) ||
            !( sample instanceof Double ) ||
            !( sample instanceof Short ) ||
            !( sample instanceof Integer ) ||
            !( sample instanceof Byte ) ||
            !( sample instanceof Float )
        )
            throw new IllegalArgumentException( "Unsupported sensor value type " + sample.getClass().getSimpleName() + "." );
    }*/
    
    // ================================================
}

// ====================================================