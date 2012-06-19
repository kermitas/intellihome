package as.intellihome.neo4j.plugins.managed;

import as.intellihome.neo4j.Config;
import org.neo4j.graphdb.GraphDatabaseService;
import org.neo4j.server.plugins.*;

// ====================================================

@Description( "Sensor samples collector." )
public class SSC extends ServerPlugin
{
    // ================================================
    
    @Name( Config.pathFor_managedPlugin_sensorSamplesCollector_collectBoolean )
    @Description( "Collect sensor boolean sample." )
    @PluginTarget( GraphDatabaseService.class )
    public String collectBoolean(
            
            @Source
            GraphDatabaseService graphDb , 
            
            @Description( "SensorId" )
            @Parameter( name = Config.restParameterNameFor_sensorSamplesCollector_sensorId , optional = false )
            Integer sensorId , 
            
            @Description( "SensorBooleanValue" )
            @Parameter( name = Config.restParameterNameFor_sensorSamplesCollector_sensorValue , optional = false )
            Boolean sensorBooleanValue       
        )
    {
        return collect( graphDb , sensorId , sensorBooleanValue );
    }
    
    // ================================================
    
    @Name( Config.pathFor_managedPlugin_sensorSamplesCollector_collectFloat )
    @Description( "Collect sensor float sample." )
    @PluginTarget( GraphDatabaseService.class )
    public String collectFloat(
            
            @Source
            GraphDatabaseService graphDb , 

            @Description( "SensorId" )
            @Parameter( name = Config.restParameterNameFor_sensorSamplesCollector_sensorId , optional = false )
            Integer sensorId , 
            
            @Description( "SensorFloatValue" )
            @Parameter( name = Config.restParameterNameFor_sensorSamplesCollector_sensorValue , optional = false )
            Float sensorFloatValue       
        )
    {
        return collect( graphDb , sensorId , sensorFloatValue );
    }
    
    // ================================================
    
    @Name( Config.pathFor_managedPlugin_sensorSamplesCollector_collectString )
    @Description( "Collect sensor string sample." )
    @PluginTarget( GraphDatabaseService.class )
    public String collectString(
            
            @Source
            GraphDatabaseService graphDb , 
            
            @Description( "SensorId" )
            @Parameter( name = Config.restParameterNameFor_sensorSamplesCollector_sensorId , optional = false )
            Integer sensorId , 
            
            @Description( "SensorStringValue" )
            @Parameter( name = Config.restParameterNameFor_sensorSamplesCollector_sensorValue , optional = false )
            String sensorStringValue       
        )
    {
        return collect( graphDb , sensorId , sensorStringValue );
    }
    
    // ================================================
    
    @Name( Config.pathFor_managedPlugin_sensorSamplesCollector_collectInteger )
    @Description( "Collect sensor integer sample." )
    @PluginTarget( GraphDatabaseService.class )
    public String collectInteger(
            
            @Source
            GraphDatabaseService graphDb , 
            
            @Description( "SensorId" )
            @Parameter( name = Config.restParameterNameFor_sensorSamplesCollector_sensorId , optional = false )
            Integer sensorId , 
            
            @Description( "SensorIntegerValue" )
            @Parameter( name = Config.restParameterNameFor_sensorSamplesCollector_sensorValue , optional = false )
            Integer sensorIntegerValue       
        )
    {
        return collect( graphDb , sensorId , sensorIntegerValue );
    }

    // ================================================
    
    private String collect( GraphDatabaseService graphDb , Integer sensorId , Object sensorValue )
    {
        try
        {
            as.intellihome.neo4j.utils.SensorSamplesCollector.collect( graphDb , sensorId , sensorValue );
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