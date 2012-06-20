package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.Direction;
import org.neo4j.graphdb.Node;
import org.neo4j.graphdb.Relationship;

// ====================================================

public class SensorNode
{
    // ================================================
    
    // should be executed under active transaction
    public static synchronized Node create( Node sensorsGroupNode , Node ownerDeviceNode , String name , String description , boolean enabled , PhysicalityTypes physicalityType , DataCollectingTypes dataCollectingType , DoorLocalizationTypes doorLocalizationType , SensorDataTypes sensorDataType , String locationName , String locationDescription , Double locationX , Double locationY , Double locationZ )
    {   
        Node sensorNode = sensorsGroupNode.getGraphDatabase().createNode();
        
        sensorNode.setProperty( "name" , name );
        sensorNode.setProperty( "enabled" , enabled );
        sensorNode.setProperty( "creationTime" , System.currentTimeMillis() );
        sensorNode.setProperty( "description" ,  description );
        
        SensorsGroupNode.addSensorToSensorsGroup( sensorNode );

        DeviceNode.attachSensorToDevice( ownerDeviceNode , sensorNode );
        
        PhysicalityTypesNode.setPhisicalityTypeForDeviceOrSensor( sensorNode , physicalityType );

        if( DataCollectingTypes.OVERRIDE.equals( dataCollectingType ) )
        {
            DataCollectingTypesNode.setOverrideDataCollectingTypeForSensor( sensorNode );
        }
        else
        if( DataCollectingTypes.UNLIMITED_APPEND.equals( dataCollectingType ) )
        {
            DataCollectingTypesNode.setUnlimitedAppendDataCollectingTypeForSensor( sensorNode );
        }
        else            
        {
            // TODO
            // how to pass time_limit or maximal_samples_count_limit in REST?
            throw new UnsupportedOperationException( "Method " + dataCollectingType.name() + " is not implemented yet." );
        }
        
        DoorLocalizationTypesNode.setDoorLocalizationTypeForSensor( sensorNode , doorLocalizationType );
        
        SensorDataTypesNode.setSensorDataType( sensorNode , sensorDataType );
  
        LocationNode.create( sensorNode , locationName , locationDescription , locationX , locationY , locationZ );
        
        return sensorNode;
    }
   
    // ================================================
    
    // should be executed under active transaction
    public static void delete( Node sensorNode )
    {   
        Iterator< Relationship > iter = sensorNode.getRelationships( Direction.INCOMING , DeviceContainsSensorRelationship.CONTAINS_SENSOR ).iterator();
        while( iter.hasNext() ) iter.next().delete();
        
        iter = sensorNode.getRelationships( Direction.OUTGOING , SensorsGroup.MEMBER_OF_SENSORS_GROUP ).iterator();
        while( iter.hasNext() ) iter.next().delete();
        
        iter = sensorNode.getRelationships( Direction.OUTGOING , PhysicalityTypes.values() ).iterator();
        while( iter.hasNext() ) iter.next().delete();
        
        iter = sensorNode.getRelationships( Direction.OUTGOING , DataCollectingTypes.values() ).iterator();
        while( iter.hasNext() ) iter.next().delete();
        
        iter = sensorNode.getRelationships( Direction.OUTGOING , DoorLocalizationTypes.values() ).iterator();
        while( iter.hasNext() ) iter.next().delete();
        
        iter = sensorNode.getRelationships( Direction.OUTGOING , SensorDataTypes.values() ).iterator();
        while( iter.hasNext() ) iter.next().delete();
        
        LocationNode.delete( sensorNode );
        
        // TODO delete all other outgoing relations (and dedicated nodes)
        
        sensorNode.delete();
    }
    
    // ================================================
}

// ====================================================