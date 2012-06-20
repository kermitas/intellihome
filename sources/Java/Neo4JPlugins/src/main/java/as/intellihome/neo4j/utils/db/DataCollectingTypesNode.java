package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================

enum DataCollectingTypesRelationships implements RelationshipType
{
    DATA_COLLECTING_TYPES
}

// ====================================================

public class DataCollectingTypesNode
{
    // ================================================
    
    // creates relation DATA_COLLECTING_TYPES and empty node (as a group of phisicality types)
    // should be executed under active transaction
    public static void createDefaultData( Node intelliHomeNode , boolean addDescriptionProperty )
    {
        Node dataCollectingTypesNode = intelliHomeNode.getGraphDatabase().createNode();
        if( addDescriptionProperty ) dataCollectingTypesNode.setProperty( "description" , "This is a singleton node - group of data collecting types." );
        intelliHomeNode.createRelationshipTo( dataCollectingTypesNode , DataCollectingTypesRelationships.DATA_COLLECTING_TYPES );
    }
    
    // ================================================
    
    // return DATA_COLLECTING_TYPES relation (outgoing form IntelliHome) or null (or throws exception if there is more than one)
    public static Relationship getRelationTo( Node intelliHomeNode )
    {
        return intelliHomeNode.getSingleRelationship( DataCollectingTypesRelationships.DATA_COLLECTING_TYPES , Direction.OUTGOING );
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
    public static void setOverrideDataCollectingTypeForSensor( Node sensorNode )
    {
        removeDataCollectingTypeFromSensor( sensorNode );
            
        sensorNode.createRelationshipTo( get( sensorNode.getGraphDatabase() ) , DataCollectingTypes.OVERRIDE );
    } 
    
    // ================================================
    
    // should be executed under active transaction
    public static void setUnlimitedAppendDataCollectingTypeForSensor( Node sensorNode )
    {
        removeDataCollectingTypeFromSensor( sensorNode );
            
        sensorNode.createRelationshipTo( get( sensorNode.getGraphDatabase() ) , DataCollectingTypes.UNLIMITED_APPEND );
    } 
    
    // ================================================
    
    // will add 'expirationTime' property to relation which means that sensor samples should NOT be be keep in system longer than this time
    // should be executed under active transaction
    public static void setTimeLimitedAppendDataCollectingTypeForSensor( Node sensorNode , long expirationTime )
    {
        removeDataCollectingTypeFromSensor( sensorNode );
            
        Relationship r = sensorNode.createRelationshipTo( get( sensorNode.getGraphDatabase() ) , DataCollectingTypes.TIME_LIMITED_APPEND );
        r.setProperty( "expirationTime" , expirationTime );
    } 
    
    // ================================================
    
    // will add 'expirationTime' property to relation which means that sensor samples should NOT be be keep in system longer than this time
    // should be executed under active transaction
    public static void setSamplesCountLimitedAppendDataCollectingTypeForSensor( Node sensorNode , int maxSamplesCountLimit )
    {
        removeDataCollectingTypeFromSensor( sensorNode );
            
        Relationship r = sensorNode.createRelationshipTo( get( sensorNode.getGraphDatabase() ) , DataCollectingTypes.SAMPLES_COUNT_LIMITED_APPEND );
        r.setProperty( "samplesCountLimit" , maxSamplesCountLimit );
    }     
    
    // ================================================
    
    private static void removeDataCollectingTypeFromSensor( Node sensorNode )
    {
        Iterator< Relationship > iter = sensorNode.getRelationships( Direction.OUTGOING , DataCollectingTypes.values() ).iterator();
        while( iter.hasNext() ) iter.next().delete();
    } 
    
    // ================================================
    
    // delete main incomming relation, this node
    // should be executed under active transaction
    public static void delete( Node intelliHomeNode )
    {   
        Relationship dataCollectingTypesRelationship = getRelationTo( intelliHomeNode );

        if( dataCollectingTypesRelationship != null )
        {
            Node dataCollectingTypesNode = dataCollectingTypesRelationship.getEndNode();

            dataCollectingTypesRelationship.delete();
            dataCollectingTypesNode.delete();
        }  
    }
    
    // ================================================
}

// ====================================================