package as.intellihome.neo4j.objects.impl;

import as.intellihome.neo4j.Config;
import as.intellihome.neo4j.objects.Relations;
import org.neo4j.graphdb.*;

// ====================================================

public class SensorsGroup extends AbstractNodeContainer implements as.intellihome.neo4j.objects.SensorsGroup
{
    // ================================================
    
    private SensorsGroup( Node node )
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
    
    public static as.intellihome.neo4j.objects.SensorsGroup getOrCreate( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        Relationship mainRelation = getRelationTo( intelliHome );
        
        if( mainRelation == null )
        {
            return create( intelliHome );
        }
        else
        {
            return new SensorsGroup( mainRelation.getEndNode() );
        }
    }
    
    // ================================================
    
    private static SensorsGroup create( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        Transaction tx = intelliHome.getNode().getGraphDatabase().beginTx();
        try
        {
            Node sensorsGroupNode = intelliHome.getNode().getGraphDatabase().createNode();

            if( Config.addDescriptionPropertyToNodes ) sensorsGroupNode.setProperty( "description" , "Singleton node - a grup for all sensors." );
                
            intelliHome.getNode().createRelationshipTo( sensorsGroupNode , staticGetMainRelationshipType() );
            
            tx.success();
            
            return new SensorsGroup( sensorsGroupNode );
        }
        finally
        {
            tx.finish();
        }
    }
    
    // ================================================
    
    public static RelationshipType staticGetMainRelationshipType()
    {
        return Relations.SensorsGroup.SENSORS_GROUP;
    }
    
    // ================================================
    
    @Override
    public RelationshipType getMainRelationshipType()
    {
        return SensorsGroup.staticGetMainRelationshipType();
    } 
    
    // ================================================

    @Override
    public void addSensorToGroup( as.intellihome.neo4j.objects.Sensor sensor )
    {
        if( !sensor.getNode().hasRelationship( Direction.INCOMING , Relations.SensorsGroupContains.CONTAINS_SENSOR ) )
        {
            Transaction tx = node.getGraphDatabase().beginTx();
            try
            {
                node.createRelationshipTo( sensor.getNode() , Relations.SensorsGroupContains.CONTAINS_SENSOR );

                tx.success();
            }
            finally
            {
                tx.finish();
            }
        }
    }
    
    // ================================================
}

// ====================================================