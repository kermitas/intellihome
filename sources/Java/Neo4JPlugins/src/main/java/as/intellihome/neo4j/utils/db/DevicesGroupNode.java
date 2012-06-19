package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================


// ====================================================

enum DevicesGroupRelationship implements RelationshipType
{
    DEVICES_GROUP
}

// ====================================================

public class DevicesGroupNode
{
    // ================================================
    
    // creates relation DEVICES_GROUP and empty node (as a group of sensor data types)
    // should be executed under active transaction
    public static void createDefaultData( Node intelliHomeNode , boolean addDescriptionProperty )
    {
        Node devicesGroupNode = intelliHomeNode.getGraphDatabase().createNode();
        if( addDescriptionProperty ) devicesGroupNode.setProperty( "description" , "Singleton node - group for all devices." );
        intelliHomeNode.createRelationshipTo( devicesGroupNode , DevicesGroupRelationship.DEVICES_GROUP );
    }
    
    // ================================================
    
    // return DEVICES_GROUP relation (outgoing form IntelliHome) or null (or throws exception if there is more than one)
    public static Relationship getRelationTo( Node intelliHomeNode )
    {
        return intelliHomeNode.getSingleRelationship( DevicesGroupRelationship.DEVICES_GROUP , Direction.OUTGOING );
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
    public static void addDeviceToDevicesGroup( Node deviceNode )
    {
        if( !isDeviceInDevicesGroup( deviceNode ) )
        {   
            deviceNode.createRelationshipTo( get( deviceNode.getGraphDatabase() ) , MemberOfRelationship.MEMBER_OF );
        }
    }
    
    // ================================================
    
    public static boolean isDeviceInDevicesGroup( Node deviceNode )
    {
        Node devicesGroupNode = get( deviceNode );
        
        Iterator< Relationship > iter = deviceNode.getRelationships( Direction.OUTGOING , MemberOfRelationship.MEMBER_OF ).iterator();
        
        while( iter.hasNext() )
        {
            Relationship r = iter.next();
            if( r.getEndNode().getId() == devicesGroupNode.getId() ) return true;
        }
        
        return false;
    } 
    
    // ================================================
    
    // delete main incomming relation, this node
    // should be executed under active transaction
    public static void delete( Node intelliHomeNode )
    {   
        Relationship devicesGroupReference = getRelationTo( intelliHomeNode );

        if( devicesGroupReference != null )
        {
            Node devicesGroupNode = devicesGroupReference.getEndNode();

            devicesGroupReference.delete();
            devicesGroupNode.delete();
        }  
    }
    
    // ================================================
}

// ====================================================