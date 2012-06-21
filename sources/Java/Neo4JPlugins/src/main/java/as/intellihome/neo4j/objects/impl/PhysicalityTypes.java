package as.intellihome.neo4j.objects.impl;

import as.intellihome.neo4j.Config;
import as.intellihome.neo4j.objects.Relations;
import as.intellihome.neo4j.objects.Relations.PhysicalityType;
import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================

public class PhysicalityTypes extends AbstractNodeContainer implements as.intellihome.neo4j.objects.PhysicalityTypes
{
    // ================================================
    
    private PhysicalityTypes( Node node )
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
    
    public static as.intellihome.neo4j.objects.PhysicalityTypes getOrCreate( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        Relationship mainRelation = getRelationTo( intelliHome );
        
        if( mainRelation == null )
        {
            return create( intelliHome );
        }
        else
        {
            return new PhysicalityTypes( mainRelation.getEndNode() );
        }
    }
    
    // ================================================
    
    private static PhysicalityTypes create( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        Transaction tx = intelliHome.getNode().getGraphDatabase().beginTx();
        try
        {
            Node physicalityTypesNode = intelliHome.getNode().getGraphDatabase().createNode();

            if( Config.addDescriptionPropertyToNodes ) physicalityTypesNode.setProperty( "description" , "Singleton node - a grup of physicality types like REAL/VIRTUAL (for devices and sensors)." );
                
            intelliHome.getNode().createRelationshipTo( physicalityTypesNode , staticGetMainRelationshipType() );
            
            tx.success();
            
            return new PhysicalityTypes( physicalityTypesNode );
        }
        finally
        {
            tx.finish();
        }
    }
    
    // ================================================
    
    public static RelationshipType staticGetMainRelationshipType()
    {
        return Relations.PhysicalityTypes.PHYSICALITY_TYPES;
    }
    
    // ================================================
    
    @Override
    public RelationshipType getMainRelationshipType()
    {
        return PhysicalityTypes.staticGetMainRelationshipType();
    } 
    
    // ================================================

    @Override
    public void setPhysicalityType( as.intellihome.neo4j.objects.Device device , PhysicalityType physicalityType )
    {
        setPhysicalityTypeForAbstractNodeContainer( device.getNode() , physicalityType );
    }
    
    // ================================================

    @Override
    public void setPhysicalityType( as.intellihome.neo4j.objects.Sensor sensor , PhysicalityType physicalityType )
    {
        setPhysicalityTypeForAbstractNodeContainer( sensor.getNode() , physicalityType );
    }     
    
    // ================================================

    private void setPhysicalityTypeForAbstractNodeContainer( Node deviceOrSensorNode , PhysicalityType physicalityType )
    {
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            Iterator< Relationship > iter = deviceOrSensorNode.getRelationships( Direction.INCOMING , Relations.PhysicalityType.values() ).iterator();
            while( iter.hasNext() ) iter.next().delete();

            node.createRelationshipTo( deviceOrSensorNode , physicalityType );
            
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