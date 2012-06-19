package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.Direction;
import org.neo4j.graphdb.Node;
import org.neo4j.graphdb.Relationship;
import org.neo4j.graphdb.RelationshipType;

// ====================================================

enum PhysicalityTypesRelationships implements RelationshipType
{
    PHISICALITY_TYPES
}

// ====================================================

public class PhysicalityTypesNode
{
    // ================================================
    
    // creates relation PHISICALITY_TYPES and empty node (as a group of phisicality types), then creates all outgoing relations and nodes
    // should be executed under active transaction
    public static void createDefaultData( Node intelliHomeNode , boolean addDecriptionProperty )
    {
        Node phisicalityTypesNode = intelliHomeNode.getGraphDatabase().createNode();
        if( addDecriptionProperty ) phisicalityTypesNode.setProperty( "description" , "Singleton node - group of phisicality types like virtual/real (device, sensor)." );
        intelliHomeNode.createRelationshipTo( phisicalityTypesNode , PhysicalityTypesRelationships.PHISICALITY_TYPES );
        
        PhysicalityTypeNode.createDefaultData( phisicalityTypesNode , addDecriptionProperty );
    }
    
    // ================================================
    
    // return PHISICALITY_TYPES relation (outgoing form IntelliHome) or null (or throws exception if there is more than one)
    public static Relationship getRelationTo( Node intelliHomeNode )
    {
        return intelliHomeNode.getSingleRelationship( PhysicalityTypesRelationships.PHISICALITY_TYPES , Direction.OUTGOING );
    }   
    
    // ================================================
    
    // delete main incomming relation, this node, all outgoing relations and it's nodes
    // should be executed under active transaction
    public static void delete( Node intelliHomeNode )
    {   
        Relationship physicalityTypesReference = getRelationTo( intelliHomeNode );

        if( physicalityTypesReference != null )
        {
            //System.out.println( PhysicalityTypesNode.class.getName() + ": trying to delete child nodes..." );
            
            Node physicalityTypesNode = physicalityTypesReference.getEndNode();

            Iterator< Relationship > iter = physicalityTypesNode.getRelationships( Direction.OUTGOING , PhysicalityTypeRelationships.values() ).iterator();

            while( iter.hasNext() ) PhysicalityTypeNode.delete( iter.next().getEndNode() );
            
            //System.out.println( PhysicalityTypesNode.class.getName() + ": deleting node " + physicalityTypesNode.getId() );
            //System.out.println( PhysicalityTypesNode.class.getName() + ": deleting reference " + physicalityTypesReference.getId() );
                        
            physicalityTypesReference.delete();
            physicalityTypesNode.delete();
        }  
        else
        {
            //System.out.println( PhysicalityTypesNode.class.getName() + ": could not find physicalityTypesReference" );
        }
    }
    
    // ================================================
}

// ====================================================