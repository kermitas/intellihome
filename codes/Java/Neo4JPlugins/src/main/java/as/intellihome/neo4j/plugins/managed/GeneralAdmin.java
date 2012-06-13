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
    
    @Name( "createInitialDatabaseGraph" )
    @Description( "Create initial database graph." )
    @PluginTarget( GraphDatabaseService.class )
    public void createInitialDatabaseGraph( @Source GraphDatabaseService graphDb )
    {
        as.intellihome.neo4j.utils.GeneralAdmin.createInitialDatabaseGraph( graphDb );
    }
    
    // ================================================    
}
// ====================================================