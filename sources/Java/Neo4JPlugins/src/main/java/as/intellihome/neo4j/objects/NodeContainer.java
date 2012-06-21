package as.intellihome.neo4j.objects;

import org.neo4j.graphdb.Node;
import org.neo4j.graphdb.Relationship;

// ====================================================

public interface NodeContainer
{
    // ================================================
    
    public Node getNode();
    
    // ================================================
    
    public Relationship getRelationTo();
    
    // ================================================
    
    public void delete();
    
    // ================================================
}

// ====================================================