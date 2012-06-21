package as.intellihome.neo4j.objects.impl;

import as.intellihome.neo4j.objects.Relations;
import org.neo4j.graphdb.Node;
import org.neo4j.graphdb.RelationshipType;

// ====================================================

public class Location extends AbstractNodeContainer implements as.intellihome.neo4j.objects.Location
{
    // ================================================
    
    public Location( Node node )
    {
        super( node );
    }
    
    // ================================================
    
    public static RelationshipType staticGetMainRelationshipType()
    {
        return Relations.Location.HAS_LOCATION;
    }
    
    // ================================================
    
    @Override
    public RelationshipType getMainRelationshipType()
    {
        return Location.staticGetMainRelationshipType();
    } 
    
    // ================================================
}

// ====================================================