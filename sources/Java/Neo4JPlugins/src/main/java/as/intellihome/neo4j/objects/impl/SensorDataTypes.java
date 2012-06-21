package as.intellihome.neo4j.objects.impl;

import as.intellihome.neo4j.Config;
import as.intellihome.neo4j.objects.Relations;
import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================

public class SensorDataTypes extends AbstractNodeContainer implements as.intellihome.neo4j.objects.SensorDataTypes
{
    // ================================================
    
    private SensorDataTypes( Node node )
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
    
    public static as.intellihome.neo4j.objects.SensorDataTypes getOrCreate( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        Relationship mainRelation = getRelationTo( intelliHome );
        
        if( mainRelation == null )
        {
            return create( intelliHome );
        }
        else
        {
            return new SensorDataTypes( mainRelation.getEndNode() );
        }
    }
    
    // ================================================
    
    private static SensorDataTypes create( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        Transaction tx = intelliHome.getNode().getGraphDatabase().beginTx();
        try
        {
            Node sendorDataTypesNode = intelliHome.getNode().getGraphDatabase().createNode();

            if( Config.addDescriptionPropertyToNodes ) sendorDataTypesNode.setProperty( "description" , "Singleton node - a grup of sensor data types like BOOLEAN, BYTE/CHAR/LONG." );
                
            intelliHome.getNode().createRelationshipTo( sendorDataTypesNode , staticGetMainRelationshipType() );
            
            tx.success();
            
            return new SensorDataTypes( sendorDataTypesNode );
        }
        finally
        {
            tx.finish();
        }
    }
    
    // ================================================
    
    public static RelationshipType staticGetMainRelationshipType()
    {
        return Relations.SensorDataTypes.SENSOR_DATA_TYPES;
    }
    
    // ================================================
    
    @Override
    public RelationshipType getMainRelationshipType()
    {
        return SensorDataTypes.staticGetMainRelationshipType();
    } 
    
    // ================================================

    @Override
    public void setSensorDataType( as.intellihome.neo4j.objects.Sensor sensor , Relations.SensorDataType sensorDataType )
    {
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            Iterator< Relationship > iter = sensor.getNode().getRelationships( Direction.INCOMING , Relations.SensorDataType.values() ).iterator();
            while( iter.hasNext() ) iter.next().delete();

            Relationship r = node.createRelationshipTo( sensor.getNode() , sensorDataType );
            
            if( sensorDataType.min != null ) r.setProperty( "min" , sensorDataType.min );
            if( sensorDataType.max != null ) r.setProperty( "max" , sensorDataType.max );
            
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