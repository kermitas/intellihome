package as.intellihome.neo4j.utils.db;

import org.neo4j.graphdb.*;

// ====================================================

enum SensorsGroupRelationship implements RelationshipType
{
    SENSORS_GROUP
}

// ====================================================

public class SensorsGroupNode
{
    // ================================================
    
    // creates relation SENSORS_GROUP and empty node (as a group of sensor data types)
    // should be executed under active transaction
    public static void createDefaultData( Node intelliHomeNode , boolean addDescriptionProperty )
    {
        Node sensorsGroupNode = intelliHomeNode.getGraphDatabase().createNode();
        if( addDescriptionProperty ) sensorsGroupNode.setProperty( "description" , "Singleton node - group for all sensors." );
        intelliHomeNode.createRelationshipTo( sensorsGroupNode , SensorsGroupRelationship.SENSORS_GROUP );
    }
    
    // ================================================
    
    // return SENSORS_GROUP relation (outgoing form IntelliHome) or null (or throws exception if there is more than one)
    public static Relationship getRelationTo( Node intelliHomeNode )
    {
        return intelliHomeNode.getSingleRelationship( SensorsGroupRelationship.SENSORS_GROUP , Direction.OUTGOING );
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
    public static void addSensorToSensorsGroup( Node sensorNode )
    {
        if( !isSensorInSensorsGroup( sensorNode ) )
        {   
            sensorNode.createRelationshipTo( get( sensorNode.getGraphDatabase() ) , SensorsGroup.MEMBER_OF_SENSORS_GROUP );
        }
    }
    
    // ================================================
    
    public static boolean isSensorInSensorsGroup( Node sensorNode )
    {
        return sensorNode.hasRelationship( Direction.OUTGOING , SensorsGroup.MEMBER_OF_SENSORS_GROUP );
    } 
    
    // ================================================
    
    // delete main incomming relation, this node
    // should be executed under active transaction
    public static void delete( Node intelliHomeNode )
    {   
        Relationship sensorsGroupReference = getRelationTo( intelliHomeNode );

        if( sensorsGroupReference != null )
        {
            Node sensorsGroupNode = sensorsGroupReference.getEndNode();

            sensorsGroupReference.delete();
            sensorsGroupNode.delete();
        }  
    }
    
    // ================================================
}

// ====================================================