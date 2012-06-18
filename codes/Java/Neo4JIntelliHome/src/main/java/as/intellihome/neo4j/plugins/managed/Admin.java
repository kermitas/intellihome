package as.intellihome.neo4j.plugins.managed;

import as.intellihome.Config;
import org.neo4j.graphdb.GraphDatabaseService;
import org.neo4j.server.plugins.*;

// ====================================================

@Description( "Administration." )
public class Admin extends ServerPlugin
{
    // ================================================
    
    @Name( Config.pathFor_managedPlugin_admin_installService )
    @Description( Config.descriptionFor_managedPlugin_admin_installService )
    @PluginTarget( GraphDatabaseService.class )
    public void installService( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.utils.Admin.installService( graphDb );
    }
    
    // ================================================
   
    @Name( Config.pathFor_managedPlugin_admin_createDb )
    @Description( Config.descriptionFor_managedPlugin_admin_createDb )
    @PluginTarget( GraphDatabaseService.class )
    public void createDb( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.utils.DatabaseAdmin.createDb( graphDb );
    }
    
    // ================================================
   
    @Name( Config.pathFor_managedPlugin_admin_deleteDb )
    @Description( Config.descriptionFor_managedPlugin_admin_deleteDb )
    @PluginTarget( GraphDatabaseService.class )
    public void deleteDb( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.utils.DatabaseAdmin.deleteDb( graphDb );
    }  
    
    // ================================================
   
    @Name( Config.pathFor_managedPlugin_admin_addDefaultDataToDb )
    @Description( Config.descriptionFor_managedPlugin_admin_addDefaultDataToDb )
    @PluginTarget( GraphDatabaseService.class )
    public void addDefaultDataToDb( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.utils.DatabaseAdmin.addDefaultDataToDb( graphDb );
    } 
    
    // ================================================
   
    @Name( Config.pathFor_managedPlugin_admin_shutdown )
    @Description( Config.descriptionFor_managedPlugin_admin_shutdown )
    @PluginTarget( GraphDatabaseService.class )
    public void shutdown( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.utils.Admin.shutdownIntelliHome( graphDb );
    }     
    
    // ================================================    
}
// ====================================================