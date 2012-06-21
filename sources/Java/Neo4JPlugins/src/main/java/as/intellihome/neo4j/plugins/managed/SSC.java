package as.intellihome.neo4j.plugins.managed;

import as.intellihome.neo4j.Config;
import org.neo4j.graphdb.Node;
import org.neo4j.server.plugins.*;

// ====================================================

@Description( "Sensor samples collector." )
public class SSC extends ServerPlugin
{
    // ================================================
    
    @Name( Config.pathFor_managedPlugin_sensorSamplesCollector_collectBoolean )
    @Description( "Collect sensor boolean sample." )
    @PluginTarget( Node.class )
    public String collectBoolean(
            
            @Source
            Node sensorNode , 

            @Description( "SensorBooleanValue" )
            @Parameter( name = Config.restParameterNameFor_sensorSamplesCollector_sensorValue , optional = false )
            Boolean sensorBooleanValue       
        )
    {
        return collect( sensorNode , sensorBooleanValue );
    }
    
    // ================================================
    
    @Name( Config.pathFor_managedPlugin_sensorSamplesCollector_collectFloat )
    @Description( "Collect sensor float sample." )
    @PluginTarget( Node.class )
    public String collectFloat(
            
            @Source
            Node sensorNode , 
            
            @Description( "SensorFloatValue" )
            @Parameter( name = Config.restParameterNameFor_sensorSamplesCollector_sensorValue , optional = false )
            Float sensorFloatValue       
        )
    {
        return collect( sensorNode , sensorFloatValue );
    }
    
    // ================================================
    
    @Name( Config.pathFor_managedPlugin_sensorSamplesCollector_collectDouble )
    @Description( "Collect sensor double sample." )
    @PluginTarget( Node.class )
    public String collectDouble(
            
            @Source
            Node sensorNode , 
            
            @Description( "SensorDoubleValue" )
            @Parameter( name = Config.restParameterNameFor_sensorSamplesCollector_sensorValue , optional = false )
            Float sensorDoubleValue       
        )
    {
        return collect( sensorNode , sensorDoubleValue );
    }    
    
    // ================================================
    
    @Name( Config.pathFor_managedPlugin_sensorSamplesCollector_collectString )
    @Description( "Collect sensor string sample." )
    @PluginTarget( Node.class )
    public String collectString(
            
            @Source
            Node sensorNode , 

            @Description( "SensorStringValue" )
            @Parameter( name = Config.restParameterNameFor_sensorSamplesCollector_sensorValue , optional = false )
            String sensorStringValue       
        )
    {
        return collect( sensorNode , sensorStringValue );
    }
    
    // ================================================
    
    @Name( Config.pathFor_managedPlugin_sensorSamplesCollector_collectInteger )
    @Description( "Collect sensor integer sample." )
    @PluginTarget( Node.class )
    public String collectInteger(
            
            @Source
            Node sensorNode , 

            @Description( "SensorIntegerValue" )
            @Parameter( name = Config.restParameterNameFor_sensorSamplesCollector_sensorValue , optional = false )
            Integer sensorIntegerValue       
        )
    {
        return collect( sensorNode , sensorIntegerValue );
    }
    
    // ================================================
    
    @Name( Config.pathFor_managedPlugin_sensorSamplesCollector_collectByte )
    @Description( "Collect sensor byte sample." )
    @PluginTarget( Node.class )
    public String collectByte(
            
            @Source
            Node sensorNode , 

            @Description( "SensorByteValue" )
            @Parameter( name = Config.restParameterNameFor_sensorSamplesCollector_sensorValue , optional = false )
            Integer sensorByteValue       
        )
    {
        return collect( sensorNode , sensorByteValue );
    }    
    
    // ================================================
    
    @Name( Config.pathFor_managedPlugin_sensorSamplesCollector_collectChar )
    @Description( "Collect sensor char sample." )
    @PluginTarget( Node.class )
    public String collectChar(
            
            @Source
            Node sensorNode , 

            @Description( "SensorCharValue" )
            @Parameter( name = Config.restParameterNameFor_sensorSamplesCollector_sensorValue , optional = false )
            Integer sensorCharValue       
        )
    {
        return collect( sensorNode , sensorCharValue );
    }     
    
    // ================================================
    
    @Name( Config.pathFor_managedPlugin_sensorSamplesCollector_collectShort )
    @Description( "Collect sensor short sample." )
    @PluginTarget( Node.class )
    public String collectShort(
            
            @Source
            Node sensorNode , 

            @Description( "SensorShortValue" )
            @Parameter( name = Config.restParameterNameFor_sensorSamplesCollector_sensorValue , optional = false )
            Integer sensorShortValue       
        )
    {
        return collect( sensorNode , sensorShortValue );
    }     

    // ================================================
    
    private String collect( Node sensorNode , Object sensorValue )
    {
        try
        {
            as.intellihome.neo4j.Operations.createSensorSample( sensorNode , sensorValue );
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