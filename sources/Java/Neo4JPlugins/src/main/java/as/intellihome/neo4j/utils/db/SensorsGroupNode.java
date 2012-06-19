package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================


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
            sensorNode.createRelationshipTo( get( sensorNode.getGraphDatabase() ) , MemberOfRelationship.MEMBER_OF );
        }
    }
    
    // ================================================
    
    public static boolean isSensorInSensorsGroup( Node sensorNode )
    {
        Node sensorsGroupNode = get( sensorNode );
        
        Iterator< Relationship > iter = sensorNode.getRelationships( Direction.OUTGOING , MemberOfRelationship.MEMBER_OF ).iterator();
        
        while( iter.hasNext() )
        {
            Relationship r = iter.next();
            if( r.getEndNode().getId() == sensorsGroupNode.getId() ) return true;
        }
        
        return false;
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