package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================

enum DoorLocalizationTypesRelationships implements RelationshipType
{
    DOOR_LOCALIZATION_TYPES
}

// ====================================================

public class DoorLocalizationTypesNode
{
    // ================================================
    
    // creates relation DOOR_LOCALIZATION_TYPES and empty node (as a group of phisicality types)
    // should be executed under active transaction
    public static void createDefaultData( Node intelliHomeNode , boolean addDescriptionProperty )
    {
        Node phisicalityTypesNode = intelliHomeNode.getGraphDatabase().createNode();
        if( addDescriptionProperty ) phisicalityTypesNode.setProperty( "description" , "Singleton node - group of door localization types like indoor/outdoor (for sensor)." );
        intelliHomeNode.createRelationshipTo( phisicalityTypesNode , DoorLocalizationTypesRelationships.DOOR_LOCALIZATION_TYPES );
    }
    
    // ================================================
    
    // return DOOR_LOCALIZATION_TYPES relation (outgoing form IntelliHome) or null (or throws exception if there is more than one)
    public static Relationship getRelationTo( Node intelliHomeNode )
    {
        return intelliHomeNode.getSingleRelationship( DoorLocalizationTypesRelationships.DOOR_LOCALIZATION_TYPES , Direction.OUTGOING );
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
    public static void setDoorLocalizationTypeForSensor( Node sensorNode , DoorLocalizationTypes doorLocalizationType )
    {
        Iterator< Relationship > iter = sensorNode.getRelationships( Direction.OUTGOING , DoorLocalizationTypesRelationships.values() ).iterator();
        while( iter.hasNext() ) iter.next().delete();
            
        sensorNode.createRelationshipTo( get( sensorNode.getGraphDatabase() ) , doorLocalizationType );
    }
    
    // ================================================
    
    // delete main incomming relation, this node
    // should be executed under active transaction
    public static void delete( Node intelliHomeNode )
    {   
        Relationship doorLocalizationTypesRelationship = getRelationTo( intelliHomeNode );

        if( doorLocalizationTypesRelationship != null )
        {
            Node doorLocalizationTypesNode = doorLocalizationTypesRelationship.getEndNode();

            doorLocalizationTypesRelationship.delete();
            doorLocalizationTypesNode.delete();
        }  
    }
    
    // ================================================
}

// ====================================================