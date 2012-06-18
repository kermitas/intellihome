package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.Direction;
import org.neo4j.graphdb.Node;
import org.neo4j.graphdb.Relationship;
import org.neo4j.graphdb.RelationshipType;

// ====================================================

enum InSystemLocalizationTypesRelationships implements RelationshipType
{
    IN_SYSTEM_LOCALIZATION_TYPES
}

// ====================================================

public class InSystemLocalizationTypesNode
{
    // ================================================
    
    // creates relation IN_SYSTEM_LOCALIZATION_TYPES and empty node (as a group of types), then creates all outgoing relations and nodes
    // should be executed under active transaction
    public static void createDefaultData( Node intelliHomeNode )
    {
        Node inSystemLocalizationTypesNode = intelliHomeNode.getGraphDatabase().createNode();
        intelliHomeNode.createRelationshipTo( inSystemLocalizationTypesNode , InSystemLocalizationTypesRelationships.IN_SYSTEM_LOCALIZATION_TYPES );
        
        InSystemLocalizationTypeNode.createDefaultData( inSystemLocalizationTypesNode );
    }
    
    // ================================================
    
    // return IN_SYSTEM_LOCALIZATION_TYPES relation (outgoing form IntelliHome) or null (or throws exception if there is more than one)
    public static Relationship getRelationTo( Node intelliHomeNode )
    {
        return intelliHomeNode.getSingleRelationship( InSystemLocalizationTypesRelationships.IN_SYSTEM_LOCALIZATION_TYPES , Direction.OUTGOING );
    }   
    
    // ================================================
    
    // delete main incomming relation, this node, all outgoing relations and it's nodes
    // should be executed under active transaction
    public static void delete( Node intelliHomeNode )
    {   
        Relationship inSystemLocalizationTypesReference = getRelationTo( intelliHomeNode );

        if( inSystemLocalizationTypesReference != null )
        {
            //System.out.println( InSystemLocalizationTypesNode.class.getName() + ": trying to delete child nodes..." );
            
            Node inSystemLocalizationTypesNode = inSystemLocalizationTypesReference.getEndNode();

            Iterator< Relationship > iter = inSystemLocalizationTypesNode.getRelationships( Direction.OUTGOING , InSystemLocalizationTypeRelationships.values() ).iterator();

            while( iter.hasNext() ) InSystemLocalizationTypeNode.delete( iter.next().getEndNode() );
            
            //System.out.println( InSystemLocalizationTypesNode.class.getName() + ": deleting node " + inSystemLocalizationTypesNode.getId() );
            //System.out.println( InSystemLocalizationTypesNode.class.getName() + ": deleting reference " + inSystemLocalizationTypesReference.getId() );
            
            inSystemLocalizationTypesReference.delete();
            inSystemLocalizationTypesNode.delete();
        }  
        else
        {
            //System.out.println( InSystemLocalizationTypesNode.class.getName() + ": could not find inSystemLocalizationTypesReference" );
        }        
    }
    
    // ================================================
}

// ====================================================