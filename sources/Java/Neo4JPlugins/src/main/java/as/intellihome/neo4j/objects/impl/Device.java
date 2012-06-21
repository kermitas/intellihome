package as.intellihome.neo4j.objects.impl;

import as.intellihome.neo4j.objects.Relations;
import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================

public class Device extends AbstractNodeContainer implements as.intellihome.neo4j.objects.Device
{
    // ================================================
    
    public Device( Node node )
    {
        super( node );
    }
    
    // ================================================
    
    public static Device createDevice( GraphDatabaseService graphDb , String name , String description , boolean enabled , as.intellihome.neo4j.objects.Relations.PhysicalityType physicalityType , as.intellihome.neo4j.objects.Relations.DataIncomeType dataIncomeType , as.intellihome.neo4j.objects.Relations.InSystemLocalizationType inSystemLocalizationType , String locationName , String locationDescription , double locationX , double locationY , double locationZ )
    {     
        Transaction tx = graphDb.beginTx();
        try
        {
            Node deviceNode = graphDb.createNode();

            deviceNode.setProperty( "name" , name );
            deviceNode.setProperty( "description" , description );
            deviceNode.setProperty( "enabled" , enabled );
            deviceNode.setProperty( "creationTime" , System.currentTimeMillis() );
                
            tx.success();
            
            return new Device( deviceNode );
        }
        finally
        {
            tx.finish();
        }
    }
    
    // ================================================
    
    public static RelationshipType staticGetMainRelationshipType()
    {
        return Relations.UserContains.USER_CONTAINS_DEVICE;
    }
    
    // ================================================
    
    @Override
    public RelationshipType getMainRelationshipType()
    {
        return Device.staticGetMainRelationshipType();
    } 
    
    // ================================================
    
    @Override
    public void delete()
    {
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            Iterator< Relationship > iter = node.getRelationships( Direction.OUTGOING , Relations.DeviceContains.DEVICE_CONTAINS_SENSOR ).iterator();
            while( iter.hasNext() ) new Sensor( iter.next().getEndNode() ).delete();
            
            node.getSingleRelationship( Relations.DevicesGroupContains.CONTAINS_DEVICE , Direction.INCOMING ).delete();
            
            iter = node.getRelationships( Direction.INCOMING , Relations.PhysicalityType.values() ).iterator();
            while( iter.hasNext() ) iter.next().delete();
            
            iter = node.getRelationships( Direction.INCOMING , Relations.InSystemLocalizationType.values() ).iterator();
            while( iter.hasNext() ) iter.next().delete();
            
            iter = node.getRelationships( Direction.INCOMING , Relations.DataIncomeType.values() ).iterator();
            while( iter.hasNext() ) iter.next().delete();
            
            LocationManager.get( node.getGraphDatabase() ).getLocation( this ).delete();
            
            super.delete();
            
            tx.success();
        }
        finally
        {
            tx.finish();
        }        
    }
    
    // ================================================
    
    @Override 
    public Sensor createSensor( String name , String description , boolean enabled , as.intellihome.neo4j.objects.Relations.PhysicalityType physicalityType ,  as.intellihome.neo4j.objects.Relations.DataCollectingType dataCollectingType , as.intellihome.neo4j.objects.Relations.DoorLocalizationType doorLocalizationType , as.intellihome.neo4j.objects.Relations.SensorDataType sensorDataType , String locationName , String locationDescription , double locationX , double locationY , double locationZ )
    {
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            Sensor sensor = Sensor.createSensor( node.getGraphDatabase() , name , description , enabled );
            
            as.intellihome.neo4j.objects.IntelliHome ih = as.intellihome.neo4j.objects.impl.IntelliHome.getOrCreate( node.getGraphDatabase() );
            
            SensorsGroup.getOrCreate( ih ).addSensorToGroup( sensor );
            
            node.createRelationshipTo( sensor.getNode() , Relations.DeviceContains.DEVICE_CONTAINS_SENSOR );
            
            LocationManager.get( node.getGraphDatabase() ).setLocation( sensor , locationName, locationDescription, locationX , locationY , locationZ );
            
            PhysicalityTypes.getOrCreate( ih ).setPhysicalityType( sensor , physicalityType );
            DoorLocalizationTypes.getOrCreate( ih ).setDoorLocalizationType( sensor , doorLocalizationType );
            SensorDataTypes.getOrCreate( ih ).setSensorDataType( sensor , sensorDataType );
            DataCollectingTypes.getOrCreate( ih ).setDataCollectingType( sensor , dataCollectingType );
            
            /*
            if( as.intellihome.neo4j.objects.Relations.DataCollectingType.APPEND_UNLIMITED.equals( dataCollectingType ) )
            {
                DataCollectingTypes.getOrCreate( ih ).setUnlimitedAppendDataCollectingType( sensor );
            }
            else
            if( as.intellihome.neo4j.objects.Relations.DataCollectingType.OVERRIDE.equals( dataCollectingType ) )
            {
                DataCollectingTypes.getOrCreate( ih ).setOverrideDataCollectingType( sensor );
            }
            else
            {
                // TODO we have to pass here time limit for APPEND_LIMITED_BY_TIME or maxSamplesCount for APPEND_LIMITED_BY_COUNT
                throw new UnsupportedOperationException( "DataCollectingType '" + dataCollectingType.name() + "' is not supported yet." );
            }*/
                
            tx.success();
            
            return sensor;
        }
        finally
        {
            tx.finish();
        } 
    }
    
    // ================================================
}

// ====================================================