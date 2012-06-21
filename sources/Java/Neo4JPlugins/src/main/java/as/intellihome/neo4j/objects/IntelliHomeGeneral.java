package as.intellihome.neo4j.objects;

import org.neo4j.graphdb.GraphDatabaseService;
    
// ====================================================

public class IntelliHomeGeneral
{
    // ================================================
    
    public static IntelliHome getOrCreate( GraphDatabaseService graphDb )
    {
        return as.intellihome.neo4j.objects.impl.IntelliHome.getOrCreate( graphDb );
    }
    
    // ================================================
    
    public static boolean exists( GraphDatabaseService graphDb )
    {
        return as.intellihome.neo4j.objects.impl.IntelliHome.exists( graphDb );
    }   
    
    // ================================================
}

// ====================================================