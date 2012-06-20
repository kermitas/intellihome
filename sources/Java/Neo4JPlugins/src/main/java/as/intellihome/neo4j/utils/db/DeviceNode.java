package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.Direction;
import org.neo4j.graphdb.Node;
import org.neo4j.graphdb.Relationship;
import org.neo4j.graphdb.RelationshipType;

// ====================================================

enum DeviceContainsSensorRelationship implements RelationshipType
{
    CONTAINS_SENSOR
}

// ====================================================

public class DeviceNode
{
    // ================================================
    
    // should be executed under active transaction
    public static synchronized Node create( Node devicesGroupNode , Node ownerUserNode , String name , String description , boolean enabled , PhysicalityTypes physicalityType , DataIncomeTypes dataIncomeType , InSystemLocalizationTypes inSystemLocalizationType , String locationName , String locationDescription , Double locationX , Double locationY , Double locationZ )
    {   
        Node deviceNode = devicesGroupNode.getGraphDatabase().createNode();
        
        deviceNode.setProperty( "name" , name );
        deviceNode.setProperty( "enabled" , enabled );
        deviceNode.setProperty( "creationTime" , System.currentTimeMillis() );
        deviceNode.setProperty( "description" ,  description );
        
        DevicesGroupNode.addDeviceToDevicesGroup( deviceNode );

        UserNode.attachDeviceToUser( ownerUserNode , deviceNode );
        
        PhysicalityTypesNode.setPhisicalityTypeForDeviceOrSensor( deviceNode , physicalityType );
        
        if( DataIncomeTypes.DEVICE_PUSH.equals( dataIncomeType ) )
            DataIncomeTypesNode.setDevicePushDataIncomeTypeForDevice( deviceNode );
        else
        {
            // TODO
            // how to pass ip and port in rest if it is SERVER_TCPIP_PULL ?
            throw new UnsupportedOperationException( "Method " + DataIncomeTypes.SERVER_TCPIP_PULL + " is not implemented yet." );
        }
        
        InSystemLocalizationTypesNode.setInSystemLocalizationForDevice( deviceNode , inSystemLocalizationType );
        
        LocationNode.create( deviceNode , locationName , locationDescription , locationX , locationY , locationZ );
        
        return deviceNode;
    }
    
    // ================================================
    
    public static void attachSensorToDevice( Node deviceNode , Node sensorNode )
    {
        Iterator< Relationship > iter = sensorNode.getRelationships( Direction.OUTGOING , UserContainsDeviceRelationship.values() ).iterator();
        while( iter.hasNext() ) iter.next().delete();
            
        deviceNode.createRelationshipTo( sensorNode , DeviceContainsSensorRelationship.CONTAINS_SENSOR );
    }
    
    /*
    // ================================================
    
    private static int generateUniqueUserId( Node devicesGroupNode )
    {
        Random r = new Random();
        
        int id = r.nextInt( Integer.MAX_VALUE );
        
        while( !isUniqueDeviceId( id , devicesGroupNode ) ) id = r.nextInt( Integer.MAX_VALUE );
        
        return id;
    }
    
    // ================================================
    
    private static boolean isUniqueDeviceId( int id , Node devicesGroupNode )
    {
        Iterator< Relationship > iter = devicesGroupNode.getRelationships( Direction.INCOMING , DevicesGroup.MEMBER_OF_DEVICES_GROUP ).iterator();
        
        while( iter.hasNext() )
        {
            Relationship r = iter.next();
            Node n = r.getStartNode();
            
            if( n.getProperty( "id" ).equals( id ) ) return false;
        }
        
        return true;
    } */
    
    // ================================================
    
    // should be executed under active transaction
    public static void delete( Node deviceNode )
    {   
        Iterator< Relationship > iter = deviceNode.getRelationships( Direction.INCOMING , UserContainsDeviceRelationship.CONTAINS_DEVICE ).iterator();
        while( iter.hasNext() ) iter.next().delete();
        
        iter = deviceNode.getRelationships( Direction.OUTGOING , DevicesGroup.MEMBER_OF_DEVICES_GROUP ).iterator();
        while( iter.hasNext() ) iter.next().delete();
        
        iter = deviceNode.getRelationships( Direction.OUTGOING , PhysicalityTypes.values() ).iterator();
        while( iter.hasNext() ) iter.next().delete();
        
        iter = deviceNode.getRelationships( Direction.OUTGOING , DataIncomeTypes.values() ).iterator();
        while( iter.hasNext() ) iter.next().delete();
        
        iter = deviceNode.getRelationships( Direction.OUTGOING , InSystemLocalizationTypes.values() ).iterator();
        while( iter.hasNext() ) iter.next().delete();
        
        LocationNode.delete( deviceNode );
        
        iter = deviceNode.getRelationships( Direction.OUTGOING , DeviceContainsSensorRelationship.CONTAINS_SENSOR ).iterator();
        while( iter.hasNext() ) SensorNode.delete( iter.next().getEndNode() );
        
        // TODO delete all other outgoing relations (and dedicated nodes)
        
        deviceNode.delete();
    }
    
    // ================================================
}

// ====================================================