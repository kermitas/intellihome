package as.intellihome.neo4j.plugins.managed;

import org.neo4j.graphdb.GraphDatabaseService;
import org.neo4j.server.plugins.*;

// ====================================================

@Description( "General administration." )
public class GeneralAdmin extends ServerPlugin
{
    // ================================================
    
    @Name( "installIntelliHomeOnNeo4J" )
    @Description( "Install IntelliHome on Neo4J (one time action should be executed after startup)." )
    @PluginTarget( GraphDatabaseService.class )
    public void installIntelliHomeOnNeo4J( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.utils.GeneralAdmin.installIntelliHomeOnNeo4J( graphDb );
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