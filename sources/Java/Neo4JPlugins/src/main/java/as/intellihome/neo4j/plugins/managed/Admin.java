package as.intellihome.neo4j.plugins.managed;

import as.intellihome.neo4j.Config;
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
            
            @Parameter( name = "userName", optional = false )
            @Description( "User name." )
            String userName ,
            
            @Parameter( name = "userLogin", optional = false )
            @Description( "User login." )
            String userLogin ,
            
            @Parameter( name = "userPassword", optional = false )
            @Description( "User password." )
            String userPassword ,
            
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
        return as.intellihome.neo4j.utils.db.GeneralDbOperations.createUser( graphDb , userName , userLogin , userPassword , enabled , userRights );
    }      
    
    // ================================================    
}
// ====================================================