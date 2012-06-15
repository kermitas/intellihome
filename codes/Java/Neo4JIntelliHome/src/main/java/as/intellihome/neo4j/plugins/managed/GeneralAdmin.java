package as.intellihome.neo4j.plugins.managed;

import as.intellihome.Config;
import org.neo4j.graphdb.GraphDatabaseService;
import org.neo4j.server.plugins.*;

// ====================================================

@Description( "General administration." )
public class GeneralAdmin extends ServerPlugin
{
    // ================================================
    
    @Name( Config.pathFor_managedPlugin_generalAdmin_installService )
    @Description( "Install IntelliHome service on Neo4J (one time action should be executed just after Neo4J startup)." )
    @PluginTarget( GraphDatabaseService.class )
    public void installService( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.utils.GeneralAdmin.installService( graphDb );
    }
    
    // ================================================
   
    @Name( Config.pathFor_managedPlugin_generalAdmin_createDb )
    @Description( "Create database." )
    @PluginTarget( GraphDatabaseService.class )
    public void createDb( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.utils.GeneralAdmin.createDb( graphDb );
    }
    
    // ================================================
   
    @Name( Config.pathFor_managedPlugin_generalAdmin_deleteDb )
    @Description( "Delete database." )
    @PluginTarget( GraphDatabaseService.class )
    public void deleteDb( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.utils.GeneralAdmin.deleteDb( graphDb );
    }  
    
    // ================================================
   
    @Name( Config.pathFor_managedPlugin_generalAdmin_addDefaultDataToDb )
    @Description( "Add default data to the graph." )
    @PluginTarget( GraphDatabaseService.class )
    public void addDefaultDataToDb( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.utils.GeneralAdmin.addDefaultDataToDb( graphDb );
    }  
    
    // ================================================    
}
// ====================================================