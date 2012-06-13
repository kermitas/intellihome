package as.intellihome.neo4j.plugins.managed;

import org.neo4j.graphdb.GraphDatabaseService;
import org.neo4j.server.plugins.*;

// ====================================================

@Description( "Sensor samples collector." )
public class SensorSamplesCollector extends ServerPlugin
{
    // ================================================
    
    @Name( "collectInteger" )
    @Description( "Collect sensor integer sample." )
    @PluginTarget( GraphDatabaseService.class )
    public String collectInteger(
            
            @Source GraphDatabaseService graphDb , 
            
            @Description( "DeviceId" )
            @Parameter( name = "d", optional = false ) Integer deviceId ,
            
            @Description( "SensorId" )
            @Parameter( name = "s", optional = false ) Integer sensorId , 
            
            @Description( "SensorIntegerValue" )
            @Parameter( name = "v", optional = false ) Integer sensorIntegerValue       
        )
    {
        try
        {
            return "ok d=" + deviceId + ", s=" + sensorId + ", v=" + sensorIntegerValue;
        }
        catch( Exception e )
        {
            return "err (" + e + ")";
        }
    }

    // ================================================
}
// ====================================================