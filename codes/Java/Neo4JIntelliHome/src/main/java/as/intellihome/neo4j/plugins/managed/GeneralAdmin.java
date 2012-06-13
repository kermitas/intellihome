package as.intellihome.neo4j.plugins.managed;

import org.neo4j.graphdb.GraphDatabaseService;
import org.neo4j.server.plugins.*;

// ====================================================

@Description( "General administration." )
public class GeneralAdmin extends ServerPlugin
{
    // ================================================
    
    @Name( "installService" )
    @Description( "Install IntelliHome service on Neo4J (one time action should be executed just after startup)." )
    @PluginTarget( GraphDatabaseService.class )
    public void installService( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.utils.GeneralAdmin.installService( graphDb );
    }
    
    // ================================================
   
    @Name( "addDefaultData" )
    @Description( "Add default data to the graph." )
    @PluginTarget( GraphDatabaseService.class )
    public void addDefaultData( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.utils.GeneralAdmin.addDefaultData( graphDb );
    }  
    
    // ================================================
   
    @Name( "deleteDb" )
    @Description( "Delete database." )
    @PluginTarget( GraphDatabaseService.class )
    public void deleteDb( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.utils.GeneralAdmin.deleteDb( graphDb );
    }  
    
    // ================================================    
}
// ====================================================