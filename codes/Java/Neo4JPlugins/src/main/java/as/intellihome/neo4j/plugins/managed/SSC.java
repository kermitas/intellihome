package as.intellihome.neo4j.plugins.managed;

import org.neo4j.graphdb.GraphDatabaseService;
import org.neo4j.server.plugins.*;

// ====================================================

@Description( "Sensor samples collector." )
public class SSC extends ServerPlugin
{
    // ================================================
    
    @Name( "b" )
    @Description( "Collect sensor boolean sample." )
    @PluginTarget( GraphDatabaseService.class )
    public String collectBoolean(
            
            @Source
            GraphDatabaseService graphDb , 
            
            @Description( "DeviceId" )
            @Parameter( name = "d" , optional = false )
            Integer deviceId ,
            
            @Description( "SensorId" )
            @Parameter( name = "s" , optional = false )
            Integer sensorId , 
            
            @Description( "SensorBooleanValue" )
            @Parameter( name = "v" , optional = false )
            Boolean sensorBooleanValue       
        )
    {
        return collect( graphDb , deviceId , sensorId , sensorBooleanValue );
    }
    
    // ================================================
    
    @Name( "f" )
    @Description( "Collect sensor float sample." )
    @PluginTarget( GraphDatabaseService.class )
    public String collectFloat(
            
            @Source
            GraphDatabaseService graphDb , 
            
            @Description( "DeviceId" )
            @Parameter( name = "d" , optional = false )
            Integer deviceId ,
            
            @Description( "SensorId" )
            @Parameter( name = "s" , optional = false )
            Integer sensorId , 
            
            @Description( "SensorFloatValue" )
            @Parameter( name = "v" , optional = false )
            Float sensorFloatValue       
        )
    {
        return collect( graphDb , deviceId , sensorId , sensorFloatValue );
    }
    
    // ================================================
    
    @Name( "s" )
    @Description( "Collect sensor string sample." )
    @PluginTarget( GraphDatabaseService.class )
    public String collectString(
            
            @Source
            GraphDatabaseService graphDb , 
            
            @Description( "DeviceId" )
            @Parameter( name = "d" , optional = false )
            Integer deviceId ,
            
            @Description( "SensorId" )
            @Parameter( name = "s" , optional = false )
            Integer sensorId , 
            
            @Description( "SensorStringValue" )
            @Parameter( name = "v" , optional = false )
            String sensorStringValue       
        )
    {
        return collect( graphDb , deviceId , sensorId , sensorStringValue );
    }
    
    // ================================================
    
    @Name( "i" )
    @Description( "Collect sensor integer sample." )
    @PluginTarget( GraphDatabaseService.class )
    public String collectInteger(
            
            @Source
            GraphDatabaseService graphDb , 
            
            @Description( "DeviceId" )
            @Parameter( name = "d" , optional = false )
            Integer deviceId ,
            
            @Description( "SensorId" )
            @Parameter( name = "s" , optional = false )
            Integer sensorId , 
            
            @Description( "SensorIntegerValue" )
            @Parameter( name = "v" , optional = false )
            Integer sensorIntegerValue       
        )
    {
        return collect( graphDb , deviceId , sensorId , sensorIntegerValue );
    }

    // ================================================
    
    private String collect( GraphDatabaseService graphDb , Integer deviceId , Integer sensorId , Object sensorValue )
    {
        try
        {
            as.intellihome.neo4j.utils.SensorSamplesCollector.collect( graphDb , deviceId , sensorId , sensorValue );
            return null;
        }
        catch( Exception e )
        {
            return "ERR (" + e + ")";
        }
    }
    
    // ================================================
}
// ====================================================