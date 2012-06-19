package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================

enum InSystemLocalizationTypesRelationships implements RelationshipType
{
    IN_SYSTEM_LOCALIZATION_TYPES
}

// ====================================================

public class InSystemLocalizationTypesNode
{
    // ================================================
    
    // creates relation IN_SYSTEM_LOCALIZATION_TYPES and empty node (as a group of types)
    // should be executed under active transaction
    public static void createDefaultData( Node intelliHomeNode , boolean addDescriptionProperty )
    {
        Node inSystemLocalizationTypesNode = intelliHomeNode.getGraphDatabase().createNode();
        if( addDescriptionProperty ) inSystemLocalizationTypesNode.setProperty( "description" , "Singleton node - group of device localization in out system (like head, pass-through or end-point)." );
        intelliHomeNode.createRelationshipTo( inSystemLocalizationTypesNode , InSystemLocalizationTypesRelationships.IN_SYSTEM_LOCALIZATION_TYPES );
    }
    
    // ================================================
    
    // return IN_SYSTEM_LOCALIZATION_TYPES relation (outgoing form IntelliHome) or null (or throws exception if there is more than one)
    public static Relationship getRelationTo( Node intelliHomeNode )
    {
        return intelliHomeNode.getSingleRelationship( InSystemLocalizationTypesRelationships.IN_SYSTEM_LOCALIZATION_TYPES , Direction.OUTGOING );
    }   
    
    // ================================================
    
    public static Node get( GraphDatabaseService graphDb )
    {
        return get( IntelliHomeNode.get( graphDb ) );
    }  
    
    // ================================================
    
    public static Node get( Node intelliHomeNode )
    {
        return getRelationTo( intelliHomeNode ).getEndNode();
    }      
    
    // ================================================
    
    // should be executed under active transaction
    public static void setInSystemLocalizationForDevice( Node deviceNode , InSystemLocalizationTypes inSystemLocalizationType )
    {
        Iterator< Relationship > iter = deviceNode.getRelationships( Direction.OUTGOING , InSystemLocalizationTypes.values() ).iterator();
        while( iter.hasNext() ) iter.next().delete();
            
        deviceNode.createRelationshipTo( get( deviceNode.getGraphDatabase() ) , inSystemLocalizationType );
    }    
    
    // ================================================
    
    // delete main incomming relation, this node
    // should be executed under active transaction
    public static void delete( Node intelliHomeNode )
    {   
        Relationship inSystemLocalizationTypesRelationship = getRelationTo( intelliHomeNode );

        if( inSystemLocalizationTypesRelationship != null )
        {
            Node inSystemLocalizationTypesNode = inSystemLocalizationTypesRelationship.getEndNode();

            inSystemLocalizationTypesRelationship.delete();
            inSystemLocalizationTypesNode.delete();
        }        
    }
    
    // ================================================
}

// ====================================================