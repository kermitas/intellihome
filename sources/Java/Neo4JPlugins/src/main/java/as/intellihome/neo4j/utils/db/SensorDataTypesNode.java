package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================

enum SensorDataTypesRelationships implements RelationshipType
{
    SENSOR_DATA_TYPES
}

// ====================================================

public class SensorDataTypesNode
{
    // ================================================
    
    // creates relation SENSOR_DATA_TYPES and empty node (as a group of sensor data types)
    // should be executed under active transaction
    public static void createDefaultData( Node intelliHomeNode , boolean addDescriptionProperty )
    {
        Node sensorDataTypesNode = intelliHomeNode.getGraphDatabase().createNode();
        if( addDescriptionProperty ) sensorDataTypesNode.setProperty( "description" , "Singleton node - group of types of data collected from sensor." );
        intelliHomeNode.createRelationshipTo( sensorDataTypesNode , SensorDataTypesRelationships.SENSOR_DATA_TYPES );
    }
    
    // ================================================
    
    // return PHISICALITY_TYPES relation (outgoing form IntelliHome) or null (or throws exception if there is more than one)
    public static Relationship getRelationTo( Node intelliHomeNode )
    {
        return intelliHomeNode.getSingleRelationship( SensorDataTypesRelationships.SENSOR_DATA_TYPES , Direction.OUTGOING );
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
    public static void setSensorDataType( Node sensorNode , SensorDataTypes sensorDataType )
    {
        Iterator< Relationship > iter = sensorNode.getRelationships( Direction.OUTGOING , SensorDataTypes.values() ).iterator();
        while( iter.hasNext() ) iter.next().delete();
            
        sensorNode.createRelationshipTo( get( sensorNode.getGraphDatabase() ) , sensorDataType );
    }
    
    // ================================================
    
    // delete main incomming relation, this node
    // should be executed under active transaction
    public static void delete( Node intelliHomeNode )
    {   
        Relationship sensorDataTypesRelationship = getRelationTo( intelliHomeNode );

        if( sensorDataTypesRelationship != null )
        {
            Node physicalityTypesNode = sensorDataTypesRelationship.getEndNode();

            sensorDataTypesRelationship.delete();
            physicalityTypesNode.delete();
        }  
    }
    
    // ================================================
}

// ====================================================