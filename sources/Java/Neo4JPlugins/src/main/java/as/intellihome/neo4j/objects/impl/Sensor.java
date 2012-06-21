package as.intellihome.neo4j.objects.impl;

import as.intellihome.neo4j.objects.Relations;
import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================

public class Sensor extends AbstractNodeContainer implements as.intellihome.neo4j.objects.Sensor
{
    // ================================================
    
    public Sensor( Node node )
    {
        super( node );
    }
    
    // ================================================
    
    public static Sensor createSensor( GraphDatabaseService graphDb , String name , String description , boolean enabled )
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
            
            return new Sensor( deviceNode );
        }
        finally
        {
            tx.finish();
        }
    }
    
    // ================================================
    
    public static RelationshipType staticGetMainRelationshipType()
    {
        return Relations.DeviceContains.DEVICE_CONTAINS_SENSOR;
    }
    
    // ================================================
    
    @Override
    public RelationshipType getMainRelationshipType()
    {
        return Sensor.staticGetMainRelationshipType();
    } 
    
    // ================================================
    
    @Override
    public void delete()
    {
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            node.getSingleRelationship( Relations.SensorsGroupContains.CONTAINS_SENSOR , Direction.INCOMING ).delete();
            
            Iterator< Relationship > iter = node.getRelationships( Direction.INCOMING , Relations.PhysicalityType.values() ).iterator();
            while( iter.hasNext() ) iter.next().delete();
            
            iter = node.getRelationships( Direction.INCOMING , Relations.DoorLocalizationType.values() ).iterator();
            while( iter.hasNext() ) iter.next().delete();
            
            iter = node.getRelationships( Direction.INCOMING , Relations.SensorDataType.values() ).iterator();
            while( iter.hasNext() ) iter.next().delete();
            
            iter = node.getRelationships( Direction.INCOMING , Relations.DataCollectingType.values() ).iterator();
            while( iter.hasNext() ) iter.next().delete();
            
            LocationManager.get( node.getGraphDatabase() ).getLocation( this ).delete();
            
            if( containsSensorSample() ) getLatestSensorSample().delete();
            
            super.delete();
            
            tx.success();
        }
        finally
        {
            tx.finish();
        }        
    }
    
    // ================================================
    
    public Relationship getRelationToLatestSensorSample()
    {
        return node.getSingleRelationship( SensorSample.staticGetMainRelationshipType() , Direction.OUTGOING );
    }
    
    
    // ================================================
    
    @Override
    public boolean containsSensorSample()
    {
        return node.hasRelationship( Direction.OUTGOING , SensorSample.staticGetMainRelationshipType() );
    }
    
    // ================================================
    
    @Override
    public as.intellihome.neo4j.objects.SensorSample getLatestSensorSample()
    {
        return new SensorSample( getRelationToLatestSensorSample().getEndNode() );
    }
    
    
    // ================================================
    
    @Override
    public Relations.DataCollectingType getDataCollectingType()
    {
        for( Relations.DataCollectingType dataCollectingType : Relations.DataCollectingType.values() )
        {
            Relationship r = node.getSingleRelationship( dataCollectingType , Direction.INCOMING );
            
            //System.out.println( "node " + node.getId() + ", checking incomming relation " + dataCollectingType.name() + ", r = " + r );
            
            if( r != null )
            {          
                if( r.hasProperty( "limit" ) ) dataCollectingType.limit = (long)r.getProperty( "limit" );
 
                return dataCollectingType;
            }
        }
        
        throw new RuntimeException( "Could not find data collecting type." );
    }
    
    // ================================================
    
    @Override
    public as.intellihome.neo4j.objects.SensorSample createSensorSample( Object sample )
    {
        Relations.DataCollectingType dataCollectingType = getDataCollectingType();
        
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            as.intellihome.neo4j.objects.SensorSample latestSensorSample = SensorSample.createSensorSample( node.getGraphDatabase() , sample );
            
            if( Relations.DataCollectingType.APPEND_UNLIMITED.equals( dataCollectingType ) )
            {
                Relationship currentRelationToLatestSensorSampleNode = getRelationToLatestSensorSample();

                if( currentRelationToLatestSensorSampleNode != null )
                {
                    Node currentSensorSampleNode = currentRelationToLatestSensorSampleNode.getEndNode();

                    node.createRelationshipTo( latestSensorSample.getNode() , SensorSample.staticGetMainRelationshipType() );

                    currentSensorSampleNode.createRelationshipTo( latestSensorSample.getNode() , Relations.SensorSample.PREVIOUS_SAMPLE );

                    currentRelationToLatestSensorSampleNode.delete();
                }
                else
                {
                    node.createRelationshipTo( latestSensorSample.getNode() , SensorSample.staticGetMainRelationshipType() );
                }
            }
            else  
            //if( Relations.DataCollectingType.OVERRIDE.equals( dataCollectingType ) )
            {
                // TODO attach sample with rules in dataCollectingType for this sensor (OVERRIDE, APPEND unlimited, limited, ... )
                //throw new UnsupportedOperationException( "Not implemented yet." );
                
                if( !Relations.DataCollectingType.OVERRIDE.equals( dataCollectingType ) )
                {
                    System.out.println( getClass().getName() + ".createSensorSample(): WARNING !! Data collecting type '" + dataCollectingType.name() + "' is not supported yet (works as OVERRIDE instead!)." );
                }
                
                if( containsSensorSample() ) getLatestSensorSample().delete();
 
                node.createRelationshipTo( latestSensorSample.getNode() , SensorSample.staticGetMainRelationshipType() );
            }                
            
            tx.success();
            
            return latestSensorSample;
        }
        finally
        {
            tx.finish();
        } 
    }
    
    // ================================================
}

// ====================================================