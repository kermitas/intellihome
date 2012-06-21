package as.intellihome.neo4j.objects.impl;

import as.intellihome.neo4j.Config;
import as.intellihome.neo4j.objects.Relations;
import org.neo4j.graphdb.*;

// ====================================================

public class DevicesGroup extends AbstractNodeContainer implements as.intellihome.neo4j.objects.DevicesGroup
{
    // ================================================
    
    private DevicesGroup( Node node )
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
    
    public static as.intellihome.neo4j.objects.DevicesGroup getOrCreate( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        Relationship mainRelation = getRelationTo( intelliHome );
        
        if( mainRelation == null )
        {
            return create( intelliHome );
        }
        else
        {
            return new DevicesGroup( mainRelation.getEndNode() );
        }
    }
    
    // ================================================
    
    private static DevicesGroup create( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        Transaction tx = intelliHome.getNode().getGraphDatabase().beginTx();
        try
        {
            Node devicesGroupNode = intelliHome.getNode().getGraphDatabase().createNode();

            if( Config.addDescriptionPropertyToNodes ) devicesGroupNode.setProperty( "description" , "Singleton node - a grup for all devices." );
                
            intelliHome.getNode().createRelationshipTo( devicesGroupNode , staticGetMainRelationshipType() );
            
            tx.success();
            
            return new DevicesGroup( devicesGroupNode );
        }
        finally
        {
            tx.finish();
        }
    }
    
    // ================================================
    
    public static RelationshipType staticGetMainRelationshipType()
    {
        return Relations.DevicesGroup.DEVICES_GROUP;
    }
    
    // ================================================
    
    @Override
    public RelationshipType getMainRelationshipType()
    {
        return DevicesGroup.staticGetMainRelationshipType();
    } 
    
    // ================================================

    @Override
    public void addDeviceToGroup( as.intellihome.neo4j.objects.Device device )
    {
        if( !device.getNode().hasRelationship( Direction.INCOMING , Relations.DevicesGroupContains.CONTAINS_DEVICE ) )
        {
            Transaction tx = node.getGraphDatabase().beginTx();
            try
            {
                node.createRelationshipTo( device.getNode() , Relations.DevicesGroupContains.CONTAINS_DEVICE );
                
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