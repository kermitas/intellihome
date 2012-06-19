package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.Direction;
import org.neo4j.graphdb.Node;
import org.neo4j.graphdb.Relationship;
import org.neo4j.graphdb.RelationshipType;

// ====================================================

enum PhysicalityTypeRelationships implements RelationshipType
{
    VIRTUAL , REAL
}

// ====================================================

public class PhysicalityTypeNode
{
    // ================================================
    
    // creates relation like VIRTUAL, REAL and empty nodes at the end of each relation
    // should be executed under active transaction
    public static void createDefaultData( Node phisicalityTypesNode , boolean addDecriptionProperty )
    {
        Node virtualNode = phisicalityTypesNode.getGraphDatabase().createNode();
        if( addDecriptionProperty ) virtualNode.setProperty( "description" , "Singleton node - this is virtual device/sensor (for example simulated by the computer)." );
        phisicalityTypesNode.createRelationshipTo( virtualNode , PhysicalityTypeRelationships.VIRTUAL );

        Node realNode = phisicalityTypesNode.getGraphDatabase().createNode();
        if( addDecriptionProperty ) realNode.setProperty( "description" , "Singleton node - this is real device/sensor (exists in phisical world)." );
        phisicalityTypesNode.createRelationshipTo( realNode , PhysicalityTypeRelationships.REAL );      
    }
    
    // ================================================
    
    // delete main incomming relation and node
    // should be executed under active transaction
    public static void delete( Node phisicalityTypeNode )
    {   
        Iterator< Relationship > iter = phisicalityTypeNode.getRelationships( Direction.INCOMING , PhysicalityTypeRelationships.values() ).iterator();

        while( iter.hasNext() )
        {
            Relationship r = iter.next();
            //System.out.println( PhysicalityTypeNode.class.getName() + ": deleting relation " + r.getId() );
            r.delete();
        }
        
        //System.out.println( PhysicalityTypeNode.class.getName() + ": deleting node " + phisicalityTypeNode.getId() );
        phisicalityTypeNode.delete();
    }
    
    // ================================================
}

// ====================================================