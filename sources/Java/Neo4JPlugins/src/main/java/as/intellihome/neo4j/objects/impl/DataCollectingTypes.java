package as.intellihome.neo4j.objects.impl;

import as.intellihome.neo4j.Config;
import as.intellihome.neo4j.objects.Relations;
import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================

public class DataCollectingTypes extends AbstractNodeContainer implements as.intellihome.neo4j.objects.DataCollectingTypes
{
    // ================================================
    
    private DataCollectingTypes( Node node )
    {
        super( node );
    }
   
    // ================================================
    
    public static Relationship getRelationTo( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        return intelliHome.getNode().getSingleRelationship( staticGetMainRelationshipType() , Direction.OUTGOING );
    }   
    
    // ================================================
    
    public static boolean exists( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        return intelliHome.getNode().hasRelationship( staticGetMainRelationshipType() , Direction.OUTGOING );
    }   
    
    // ================================================
    
    public static as.intellihome.neo4j.objects.DataCollectingTypes getOrCreate( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        Relationship mainRelation = getRelationTo( intelliHome );
        
        if( mainRelation == null )
        {
            return create( intelliHome );
        }
        else
        {
            return new DataCollectingTypes( mainRelation.getEndNode() );
        }
    }
    
    // ================================================
    
    private static DataCollectingTypes create( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        Transaction tx = intelliHome.getNode().getGraphDatabase().beginTx();
        try
        {
            Node dataCollectingTypesNode = intelliHome.getNode().getGraphDatabase().createNode();

            if( Config.addDescriptionPropertyToNodes ) dataCollectingTypesNode.setProperty( "description" , "Singleton node - a grup of data collecting types like OVERRIDE/APPEND (for sensors)." );
                
            intelliHome.getNode().createRelationshipTo( dataCollectingTypesNode , staticGetMainRelationshipType() );
            
            tx.success();
            
            return new DataCollectingTypes( dataCollectingTypesNode );
        }
        finally
        {
            tx.finish();
        }
    }
    
    // ================================================
    
    public static RelationshipType staticGetMainRelationshipType()
    {
        return Relations.DataCollectingTypes.DATA_COLLECTING_TYPES;
    }
    
    // ================================================
    
    @Override
    public RelationshipType getMainRelationshipType()
    {
        return DataCollectingTypes.staticGetMainRelationshipType();
    } 
    
    // ================================================
    
    @Override
    public void setDataCollectingType( as.intellihome.neo4j.objects.Sensor sensor , Relations.DataCollectingType dataCollectingType )
    {
        boolean isLimited = !Relations.DataCollectingType.OVERRIDE.equals( dataCollectingType ) && !Relations.DataCollectingType.APPEND_UNLIMITED.equals( dataCollectingType );
        
        if( isLimited )
        {
            if( dataCollectingType.limit == null ) throw new IllegalArgumentException( "Enum '" + dataCollectingType.name() + "' should contain 'limit'." );
            if( dataCollectingType.limitExceededAction == null ) throw new IllegalArgumentException( "Enum '" + dataCollectingType.name() + "' should contain 'limitExceededAction'." );
        }
        
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            Iterator< Relationship > iter = sensor.getNode().getRelationships( Direction.INCOMING , Relations.DataCollectingType.values() ).iterator();
            while( iter.hasNext() ) iter.next().delete();

            Relationship r = node.createRelationshipTo( sensor.getNode() , dataCollectingType );
            
            if( isLimited )
            {
                r.setProperty( "limit" ,  dataCollectingType.limit );
                r.setProperty( "limitExceededAction" ,  dataCollectingType.limitExceededAction );
            }
            
            tx.success();
        }
        finally
        {
            tx.finish();
        }  
    }
    
    // ================================================
    /*
    @Override
    public void setOverrideDataCollectingType( as.intellihome.neo4j.objects.Sensor sensor )
    {
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            Iterator< Relationship > iter = sensor.getNode().getRelationships( Direction.INCOMING , Relations.DataCollectingType.values() ).iterator();
            while( iter.hasNext() ) iter.next().delete();

            node.createRelationshipTo( sensor.getNode() , Relations.DataCollectingType.OVERRIDE );
            
            tx.success();
        }
        finally
        {
            tx.finish();
        }         
    }
    
    // ================================================

    @Override
    public void setUnlimitedAppendDataCollectingType( as.intellihome.neo4j.objects.Sensor sensor )
    {
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            Iterator< Relationship > iter = sensor.getNode().getRelationships( Direction.INCOMING , Relations.DataCollectingType.values() ).iterator();
            while( iter.hasNext() ) iter.next().delete();

            node.createRelationshipTo( sensor.getNode() , Relations.DataCollectingType.APPEND_UNLIMITED );
            
            tx.success();
        }
        finally
        {
            tx.finish();
        }        
    }    
    
    // ================================================

    @Override
    public void setAppendLimitedByTimeDataCollectingType( as.intellihome.neo4j.objects.Sensor sensor , long expirationTime )
    {
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            Iterator< Relationship > iter = sensor.getNode().getRelationships( Direction.INCOMING , Relations.DataCollectingType.values() ).iterator();
            while( iter.hasNext() ) iter.next().delete();

            Relationship r = node.createRelationshipTo( sensor.getNode() , Relations.DataCollectingType.APPEND_LIMITED_BY_TIME );
            r.setProperty( "limit" ,  expirationTime );
            
            tx.success();
        }
        finally
        {
            tx.finish();
        }        
    }   
    
    // ================================================

    @Override
    public void setAppendLimitedBySamplesCountDataCollectingType( as.intellihome.neo4j.objects.Sensor sensor , int maxSamplesCount )
    {
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            Iterator< Relationship > iter = sensor.getNode().getRelationships( Direction.INCOMING , Relations.DataCollectingType.values() ).iterator();
            while( iter.hasNext() ) iter.next().delete();

            Relationship r = node.createRelationshipTo( sensor.getNode() , Relations.DataCollectingType.APPEND_LIMITED_BY_COUNT );
            r.setProperty( "limit" ,  maxSamplesCount );
            
            tx.success();
        }
        finally
        {
            tx.finish();
        }        
    }   
    */
    // ================================================
}

// ====================================================