package as.intellihome.neo4j.plugins.managed;

import as.intellihome.neo4j.Config;
import org.neo4j.graphdb.GraphDatabaseService;
import org.neo4j.graphdb.Node;
import org.neo4j.server.plugins.*;

// ====================================================

@Description( "Administration." )
public class Admin extends ServerPlugin
{
    // ================================================
    
    @Name( Config.pathFor_managedPlugin_admin_install )
    @Description( Config.descriptionFor_managedPlugin_admin_install )
    @PluginTarget( GraphDatabaseService.class )
    public void installService( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.Operations.install( graphDb );
    }
    
    // ================================================
   
    @Name( Config.pathFor_managedPlugin_admin_deleteDb )
    @Description( Config.descriptionFor_managedPlugin_admin_deleteDb )
    @PluginTarget( GraphDatabaseService.class )
    public void deleteDb( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.Operations.deleteDb( graphDb );           
    }  
    
    // ================================================
   
    @Name( Config.pathFor_managedPlugin_admin_addDefaultDataToDb )
    @Description( Config.descriptionFor_managedPlugin_admin_addDefaultDataToDb )
    @PluginTarget( GraphDatabaseService.class )
    public void addDefaultDataToDb( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.Operations.addDefaultDataToDb( graphDb );            
    } 
    
    // ================================================
   
    @Name( Config.pathFor_managedPlugin_admin_shutdown )
    @Description( Config.descriptionFor_managedPlugin_admin_shutdown )
    @PluginTarget( GraphDatabaseService.class )
    public void shutdown( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.Operations.shutdown( graphDb );
    }  
    
    // ================================================
   
    @Name( Config.pathFor_managedPlugin_admin_createUser )
    @Description( Config.descriptionFor_managedPlugin_admin_createUser )
    @PluginTarget( GraphDatabaseService.class )
    public Node createUser(
            @Source GraphDatabaseService graphDb , 
            
            @Parameter( name = "login", optional = false )
            @Description( "User login (must be uniqie)." )
            String login ,
            
            @Parameter( name = "password", optional = false )
            @Description( "User password." )
            String password ,
            
            @Parameter( name = "name", optional = false )
            @Description( "User name." )
            String name ,
            
            @Parameter( name = "description", optional = false )
            @Description( "Description of this user." )
            String description ,
            
            @Parameter( name = "enabled", optional = false )
            @Description( "Mark if user is enabled." )
            Boolean enabled ,   
            
            @Parameter( name = "userRights", optional = false )
            @Description( "System rights for this user." )
            String[] userRightsAsStringArray           
        )
    {
        as.intellihome.neo4j.objects.User user = as.intellihome.neo4j.Operations.createUser( graphDb , login , password , name , description , enabled , userRightsAsStringArray );
        return user.getNode();
    }      
    
    // ================================================ 
    
    @Name( Config.pathFor_managedPlugin_admin_createDevice )
    @Description( Config.descriptionFor_managedPlugin_admin_createDevice )
    @PluginTarget( Node.class )
    public Node createDevice(

            @Source Node ownerUserNode ,
            
            @Parameter( name = "name", optional = false )
            @Description( "Short name for device." )
            String name ,
            
            @Parameter( name = "description", optional = false )
            @Description( "Description of device." )
            String description ,
            
            @Parameter( name = "enabled", optional = false )
            @Description( "Mark if device is enabled." )
            Boolean enabled ,     
            
            @Parameter( name = "physicalityType", optional = false )
            @Description( "Is this device REAL or VIRTUAL." )
            String physicalityTypeAsString ,       
            
            @Parameter( name = "dataIncomeType", optional = false )
            @Description( "Is this device DEVICE_PUSH or SERVER_TCPIP_PULL." )
            String dataIncomeTypeAsString ,
            
            @Parameter( name = "inSystemLocalizationType", optional = false )
            @Description( "Is this device HEAD, PASS_THROUGH or END_POINT." )
            String inSystemLocalizationTypeAsString ,   
            
            @Parameter( name = "locationName", optional = false )
            @Description( "Short name for physical/geographical location name." )
            String locationName , 
            
            @Parameter( name = "locationDescription", optional = false )
            @Description( "Physical/geographical location description." )
            String locationDescription ,      
            
            @Parameter( name = "locationX", optional = false )
            @Description( "Location X." )
            Double locationX ,   
            
            @Parameter( name = "locationY", optional = false )
            @Description( "Location Y." )
            Double locationY , 
            
            @Parameter( name = "locationZ", optional = false )
            @Description( "Location Z." )
            Double locationZ           
        )
    {
        as.intellihome.neo4j.objects.Device device = as.intellihome.neo4j.Operations.createDevice( ownerUserNode , name , description , enabled , physicalityTypeAsString , dataIncomeTypeAsString , inSystemLocalizationTypeAsString , locationName , locationDescription , locationX , locationY , locationZ );
        return device.getNode();        
    }      
    
    // ================================================ 
    
    @Name( Config.pathFor_managedPlugin_admin_createSensor )
    @Description( Config.descriptionFor_managedPlugin_admin_createSensor )
    @PluginTarget( Node.class )
    public Node createSensor(

            @Source Node ownerDeviceNode ,
            
            @Parameter( name = "name", optional = false )
            @Description( "Short name for sensor." )
            String name ,
            
            @Parameter( name = "description", optional = false )
            @Description( "Description of sensor." )
            String description ,
            
            @Parameter( name = "enabled", optional = false )
            @Description( "Mark if sensor is enabled." )
            Boolean enabled ,     
            
            @Parameter( name = "physicalityType", optional = false )
            @Description( "Is this sensor REAL or VIRTUAL." )
            String physicalityTypeAsString ,       
            
            @Parameter( name = "dataCollectingType", optional = false )
            @Description( "Are this sensor samples OVERRIDE or APPEND_UNLIMITED, ..." )
            String dataCollectingTypeAsString ,
            
            @Parameter( name = "doorLocalizationType", optional = false )
            @Description( "Is this senso INDOOR or OUTDOOR." )
            String doorLocalizationTypeAsString ,   
            
            @Parameter( name = "sensorDataType", optional = false )
            @Description( "Samples data type like BOOLEAN, BYTE, INT, STRING, ..." )
            String sensorDataTypeAsString ,
            
            @Parameter( name = "locationName", optional = false )
            @Description( "Short name for physical/geographical location name." )
            String locationName , 
            
            @Parameter( name = "locationDescription", optional = false )
            @Description( "Physical/geographical location description." )
            String locationDescription ,      
            
            @Parameter( name = "locationX", optional = false )
            @Description( "Location X." )
            Double locationX ,   
            
            @Parameter( name = "locationY", optional = false )
            @Description( "Location Y." )
            Double locationY , 
            
            @Parameter( name = "locationZ", optional = false )
            @Description( "Location Z." )
            Double locationZ           
        )
    {
        as.intellihome.neo4j.objects.Sensor sensor = as.intellihome.neo4j.Operations.createSensor( ownerDeviceNode , name , description , enabled , physicalityTypeAsString , dataCollectingTypeAsString , doorLocalizationTypeAsString , sensorDataTypeAsString , locationName , locationDescription , locationX , locationY , locationZ );
        return sensor.getNode();        
    }  
    
    // ================================================     
}
// ====================================================