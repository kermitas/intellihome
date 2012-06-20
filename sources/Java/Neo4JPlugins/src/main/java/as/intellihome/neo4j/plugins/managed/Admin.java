package as.intellihome.neo4j.plugins.managed;

import as.intellihome.neo4j.Config;
import as.intellihome.neo4j.utils.db.DataIncomeTypes;
import as.intellihome.neo4j.utils.db.InSystemLocalizationTypes;
import as.intellihome.neo4j.utils.db.PhysicalityTypes;
import as.intellihome.neo4j.utils.db.UserRights;
import org.neo4j.graphdb.*;
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
        as.intellihome.neo4j.utils.Admin.install( graphDb );
    }
    
    // ================================================
   
    /*
    @Name( Config.pathFor_managedPlugin_admin_createDb )
    @Description( Config.descriptionFor_managedPlugin_admin_createDb )
    @PluginTarget( GraphDatabaseService.class )
    public void createDb( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.utils.db.GeneralDbOperations.createDb( graphDb );
    }*/
    
    // ================================================
   
    @Name( Config.pathFor_managedPlugin_admin_deleteDb )
    @Description( Config.descriptionFor_managedPlugin_admin_deleteDb )
    @PluginTarget( GraphDatabaseService.class )
    public void deleteDb( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.utils.db.GeneralDbOperations.deleteDb( graphDb );
    }  
    
    // ================================================
   
    @Name( Config.pathFor_managedPlugin_admin_addDefaultDataToDb )
    @Description( Config.descriptionFor_managedPlugin_admin_addDefaultDataToDb )
    @PluginTarget( GraphDatabaseService.class )
    public void addDefaultDataToDb( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.utils.db.GeneralDbOperations.addDefaultDataToDb( graphDb );
    } 
    
    // ================================================
   
    @Name( Config.pathFor_managedPlugin_admin_shutdown )
    @Description( Config.descriptionFor_managedPlugin_admin_shutdown )
    @PluginTarget( GraphDatabaseService.class )
    public void shutdown( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.utils.Admin.shutdown( graphDb );
    }  
    
    // ================================================
   
    @Name( Config.pathFor_managedPlugin_admin_createUser )
    @Description( Config.descriptionFor_managedPlugin_admin_createUser )
    @PluginTarget( GraphDatabaseService.class )
    public Node createUser(
            @Source GraphDatabaseService graphDb , 
            
            @Parameter( name = "userLogin", optional = false )
            @Description( "User login (must be uniqie)." )
            String userLogin ,
            
            @Parameter( name = "userPassword", optional = false )
            @Description( "User password." )
            String userPassword ,
            
            @Parameter( name = "userName", optional = false )
            @Description( "User name." )
            String userName ,
            
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
        UserRights[] userRights = new UserRights[ userRightsAsStringArray.length ];   
        for( int i = 0 ; i < userRights.length ; i++ ) userRights[ i ] = UserRights.valueOf( userRightsAsStringArray[ i ] );
        
        return as.intellihome.neo4j.utils.db.GeneralDbOperations.createUser( graphDb , userLogin , userPassword , userName , description , enabled , userRights );
    }      
    
    // ================================================ 
    
    @Name( Config.pathFor_managedPlugin_admin_createDevice )
    @Description( Config.descriptionFor_managedPlugin_admin_createDevice )
    @PluginTarget( Node.class )
    public Node createDevice(

            @Source Node ownerUserNode ,
            
            @Parameter( name = "name", optional = false )
            @Description( "Short name for this device." )
            String name ,
            
            @Parameter( name = "description", optional = false )
            @Description( "Description of this device." )
            String description ,
            
            @Parameter( name = "enabled", optional = false )
            @Description( "Mark if device is enabled." )
            Boolean enabled ,     
            
            @Parameter( name = "physicalityType", optional = false )
            @Description( "Is this device is REAL or VIRTUAL." )
            String physicalityTypeAsString ,       
            
            @Parameter( name = "dataIncomeType", optional = false )
            @Description( "Is this device is DEVICE_PUSH or SERVER_TCPIP_PULL." )
            String dataIncomeTypeAsString ,
            
            @Parameter( name = "inSystemLocalizationType", optional = false )
            @Description( "Is this device is HEAD, PASS_THROUGH or END_POINT." )
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
        return as.intellihome.neo4j.utils.db.GeneralDbOperations.createDevice( ownerUserNode.getGraphDatabase() , ownerUserNode , name , description , enabled , PhysicalityTypes.valueOf( physicalityTypeAsString ) , DataIncomeTypes.valueOf( dataIncomeTypeAsString ) , InSystemLocalizationTypes.valueOf( inSystemLocalizationTypeAsString ) , locationName , locationDescription , locationX , locationY , locationZ );
    }      
    
    // ================================================     
}
// ====================================================