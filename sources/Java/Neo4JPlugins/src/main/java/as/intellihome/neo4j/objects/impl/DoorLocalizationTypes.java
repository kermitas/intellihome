package as.intellihome.neo4j.objects.impl;

import as.intellihome.neo4j.Config;
import as.intellihome.neo4j.objects.Relations;
import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================

public class DoorLocalizationTypes extends AbstractNodeContainer implements as.intellihome.neo4j.objects.DoorLocalizationTypes
{
    // ================================================
    
    private DoorLocalizationTypes( Node node )
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
    
    public static as.intellihome.neo4j.objects.DoorLocalizationTypes getOrCreate( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        Relationship mainRelation = getRelationTo( intelliHome );
        
        if( mainRelation == null )
        {
            return create( intelliHome );
        }
        else
        {
            return new DoorLocalizationTypes( mainRelation.getEndNode() );
        }
    }
    
    // ================================================
    
    private static DoorLocalizationTypes create( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        Transaction tx = intelliHome.getNode().getGraphDatabase().beginTx();
        try
        {
            Node doorLocalizationTypesNode = intelliHome.getNode().getGraphDatabase().createNode();

            if( Config.addDescriptionPropertyToNodes ) doorLocalizationTypesNode.setProperty( "description" , "Singleton node - a grup of door localization types like INDOOR/OUTDOOR (for sensors)." );
                
            intelliHome.getNode().createRelationshipTo( doorLocalizationTypesNode , staticGetMainRelationshipType() );
            
            tx.success();
            
            return new DoorLocalizationTypes( doorLocalizationTypesNode );
        }
        finally
        {
            tx.finish();
        }
    }
    
    // ================================================
    
    public static RelationshipType staticGetMainRelationshipType()
    {
        return Relations.DoorLocalizationTypes.DOOR_LOCALIZATION_TYPES;
    }
    
    // ================================================
    
    @Override
    public RelationshipType getMainRelationshipType()
    {
        return DoorLocalizationTypes.staticGetMainRelationshipType();
    } 
    
    // ================================================

    @Override
    public void setDoorLocalizationType( as.intellihome.neo4j.objects.Sensor sensor , Relations.DoorLocalizationType doorLocalizationType )
    {
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            Iterator< Relationship > iter = sensor.getNode().getRelationships( Direction.INCOMING , Relations.DoorLocalizationType.values() ).iterator();
            while( iter.hasNext() ) iter.next().delete();

            node.createRelationshipTo( sensor.getNode() , doorLocalizationType );
            
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