package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================

enum PhysicalityTypesRelationships implements RelationshipType
{
    PHISICALITY_TYPES
}

// ====================================================

public class PhysicalityTypesNode
{
    // ================================================
    
    // creates relation PHISICALITY_TYPES and empty node (as a group of phisicality types)
    // should be executed under active transaction
    public static void createDefaultData( Node intelliHomeNode , boolean addDescriptionProperty )
    {
        Node phisicalityTypesNode = intelliHomeNode.getGraphDatabase().createNode();
        if( addDescriptionProperty ) phisicalityTypesNode.setProperty( "description" , "Singleton node - group of phisicality types like virtual/real (device, sensor)." );
        intelliHomeNode.createRelationshipTo( phisicalityTypesNode , PhysicalityTypesRelationships.PHISICALITY_TYPES );
    }
    
    // ================================================
    
    // return PHISICALITY_TYPES relation (outgoing form IntelliHome) or null (or throws exception if there is more than one)
    public static Relationship getRelationTo( Node intelliHomeNode )
    {
        return intelliHomeNode.getSingleRelationship( PhysicalityTypesRelationships.PHISICALITY_TYPES , Direction.OUTGOING );
    }   
    
    // ================================================
    
    public static Node get( GraphDatabaseService graphDb )
    {
        return get( IntelliHomeNode.get( graphDb ) );
    }  
    
    // ================================================
    
    public static Node get( Node intelliHomeNode )
    {
        return getRelationTo( intelliHomeNode ).getEndNode();
    }      
    
    // ================================================
    
    // should be executed under active transaction
    public static void setPhisicalityTypeForDeviceOrSensor( Node deviceOrSensorNode , PhysicalityTypes physicalityType )
    {
        Iterator< Relationship > iter = deviceOrSensorNode.getRelationships( Direction.OUTGOING , PhysicalityTypes.values() ).iterator();
        while( iter.hasNext() ) iter.next().delete();
            
        deviceOrSensorNode.createRelationshipTo( get( deviceOrSensorNode.getGraphDatabase() ) , physicalityType );
    }
    
    // ================================================
    
    // delete main incomming relation, this node
    // should be executed under active transaction
    public static void delete( Node intelliHomeNode )
    {   
        Relationship physicalityTypesRelationship = getRelationTo( intelliHomeNode );

        if( physicalityTypesRelationship != null )
        {
            Node physicalityTypesNode = physicalityTypesRelationship.getEndNode();

            physicalityTypesRelationship.delete();
            physicalityTypesNode.delete();
        }  
    }
    
    // ================================================
}

// ====================================================