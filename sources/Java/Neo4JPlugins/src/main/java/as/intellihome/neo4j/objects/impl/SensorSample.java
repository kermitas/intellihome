package as.intellihome.neo4j.objects.impl;

import as.intellihome.neo4j.objects.Relations;
import org.neo4j.graphdb.*;

// ====================================================

public class SensorSample extends AbstractNodeContainer implements as.intellihome.neo4j.objects.SensorSample
{
    // ================================================
    
    public SensorSample( Node node )
    {
        super( node );
    }
    
    // ================================================
    
    public static as.intellihome.neo4j.objects.SensorSample createSensorSample( GraphDatabaseService graphDb , Object sample )
    {
        Transaction tx = graphDb.beginTx();
        try
        {
            Node sensorSampleNode = graphDb.createNode();

            sensorSampleNode.setProperty( "value" , sample.toString() );
            sensorSampleNode.setProperty( "creationTime" , System.currentTimeMillis() );
                
            tx.success();
            
            return new SensorSample( sensorSampleNode );
        }
        finally
        {
            tx.finish();
        }
    }
    
    // ================================================
    
    public static RelationshipType staticGetMainRelationshipType()
    {
        return Relations.SensorSample.LATEST_SAMPLE;
    }
    
    // ================================================
    
    @Override
    public RelationshipType getMainRelationshipType()
    {
        return SensorSample.staticGetMainRelationshipType();
    } 
    
    // ================================================
    
    @Override
    public void delete()
    {
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            Relationship latestSensorSampleRelationship = getRelationTo();

            if( latestSensorSampleRelationship != null )
            {
                Node latestSensorSampleNode = latestSensorSampleRelationship.getEndNode();

                Relationship prevSensorSampleRelationship = latestSensorSampleNode.getSingleRelationship( Relations.SensorSample.PREVIOUS_SAMPLE , Direction.INCOMING );

                latestSensorSampleRelationship.delete();
                latestSensorSampleNode.delete();

                while( prevSensorSampleRelationship != null )
                {
                    latestSensorSampleNode = prevSensorSampleRelationship.getStartNode();

                    prevSensorSampleRelationship.delete();

                    prevSensorSampleRelationship = latestSensorSampleNode.getSingleRelationship( Relations.SensorSample.PREVIOUS_SAMPLE , Direction.INCOMING );

                    latestSensorSampleNode.delete();
                }
            }
            
            tx.success();
        }
        finally
        {
            tx.finish();
        }        
    }
    
    // ================================================
}

// ====================================================