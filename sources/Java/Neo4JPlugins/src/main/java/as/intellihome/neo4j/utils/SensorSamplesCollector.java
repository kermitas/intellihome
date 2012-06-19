package as.intellihome.neo4j.utils;

import org.neo4j.graphdb.GraphDatabaseService;
import org.neo4j.graphdb.Node;

// ====================================================

public class SensorSamplesCollector
{
    // ================================================
    
    public static void collect( GraphDatabaseService graphDb , Integer sensorId , Object sensorValue )
    {
        if( sensorId == null ) throw new NullPointerException( "sensor ID cannot be null" );
        if( sensorValue == null ) throw new NullPointerException( "sensor value object cannot be null" );
        
        validateSensorValueObjectType( sensorValue );
        
        Node sensor = as.intellihome.neo4j.utils.Sensor.getSensorNodeById( graphDb , sensorId );
        
        // if is sensor disabled ...
        
        
        Node device = as.intellihome.neo4j.utils.Device.getDeviceNodeByContainedSensor( graphDb , sensor );
        
        // if is device disabled ...
        
        {
            Node user = as.intellihome.neo4j.utils.User.getUserNodeByContainedDevice( graphDb , device );
            
            // if is device disabled ...
        }
        
        /* TODO
        try
        {
            // find node number of this device ; check if it is enabled
            // fund user that this device belongs to and check if it is enabled
            // find node number of sensor in this debice, check if it is enabled
            // create node that contains sensor value and creation time (long) and relate it (re-link linked list)
            
            // if all went ok then update sensor and device last activity time
        }
        catch( Exception e )
        {
            
        }
        finally
        {
            
        }*/
        
        if( Math.random() > 0.5 ) throw new RuntimeException( "it's just a test exception" );
        
    }
    
    // ================================================
    
    private static void validateSensorValueObjectType( Object sensorValue )
    {
        if(
            !( sensorValue instanceof Boolean ) ||
            !( sensorValue instanceof String ) ||
            !( sensorValue instanceof Integer ) ||
            !( sensorValue instanceof Float )
        )
            throw new IllegalArgumentException( "unsupported sensor value object type" );
    }
 
    // ================================================
}
// ====================================================