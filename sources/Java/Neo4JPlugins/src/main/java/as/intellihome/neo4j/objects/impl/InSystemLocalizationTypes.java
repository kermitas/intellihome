package as.intellihome.neo4j.objects.impl;

import as.intellihome.neo4j.Config;
import as.intellihome.neo4j.objects.Relations;
import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================

public class InSystemLocalizationTypes extends AbstractNodeContainer implements as.intellihome.neo4j.objects.InSystemLocalizationTypes
{
    // ================================================
    
    private InSystemLocalizationTypes( Node node )
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
    
    public static as.intellihome.neo4j.objects.InSystemLocalizationTypes getOrCreate( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        Relationship mainRelation = getRelationTo( intelliHome );
        
        if( mainRelation == null )
        {
            return create( intelliHome );
        }
        else
        {
            return new InSystemLocalizationTypes( mainRelation.getEndNode() );
        }
    }
    
    // ================================================
    
    private static InSystemLocalizationTypes create( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        Transaction tx = intelliHome.getNode().getGraphDatabase().beginTx();
        try
        {
            Node inSystemLocalizationTypesNode = intelliHome.getNode().getGraphDatabase().createNode();

            if( Config.addDescriptionPropertyToNodes ) inSystemLocalizationTypesNode.setProperty( "description" , "Singleton node - a grup of in system localization types like HEAD/PASS_THROUGH/END_POINT (for devices)." );
                
            intelliHome.getNode().createRelationshipTo( inSystemLocalizationTypesNode , staticGetMainRelationshipType() );
            
            tx.success();
            
            return new InSystemLocalizationTypes( inSystemLocalizationTypesNode );
        }
        finally
        {
            tx.finish();
        }
    }
    
    // ================================================
    
    public static RelationshipType staticGetMainRelationshipType()
    {
        return Relations.InSystemLocalizationTypes.IN_SYSTEM_LOCALIZATION_TYPES;
    }
    
    // ================================================
    
    @Override
    public RelationshipType getMainRelationshipType()
    {
        return InSystemLocalizationTypes.staticGetMainRelationshipType();
    } 
    
    // ================================================

    @Override
    public void setInSystemLocalizationType( as.intellihome.neo4j.objects.Device device , Relations.InSystemLocalizationType inSystemLocalizationType )
    {     
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            Iterator< Relationship > iter = device.getNode().getRelationships( Direction.INCOMING , Relations.InSystemLocalizationType.values() ).iterator();
            while( iter.hasNext() ) iter.next().delete();

            node.createRelationshipTo( device.getNode() , inSystemLocalizationType );
            
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