package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================

enum DataIncomeTypesRelationships implements RelationshipType
{
    DATA_INCOME_TYPES
}

// ====================================================

public class DataIncomeTypesNode
{
    // ================================================
    
    // creates relation DATA_INCOME_TYPES and empty node (as a group of phisicality types)
    // should be executed under active transaction
    public static void createDefaultData( Node intelliHomeNode , boolean addDescriptionProperty )
    {
        Node dataIncomeTypesNode = intelliHomeNode.getGraphDatabase().createNode();
        if( addDescriptionProperty ) dataIncomeTypesNode.setProperty( "description" , "Singleton node - group of data income types (like deivce-push or server-pull)." );
        intelliHomeNode.createRelationshipTo( dataIncomeTypesNode , DataIncomeTypesRelationships.DATA_INCOME_TYPES );
    }
    
    // ================================================
    
    // return DATA_INCOME_TYPES relation (outgoing form IntelliHome) or null (or throws exception if there is more than one)
    public static Relationship getRelationTo( Node intelliHomeNode )
    {
        return intelliHomeNode.getSingleRelationship( DataIncomeTypesRelationships.DATA_INCOME_TYPES , Direction.OUTGOING );
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
    public static void setDevicePushDataIncomeTypeForDevice( Node deviceNode )
    {
        removeDataIncomeTypeFromDevice( deviceNode );
            
        deviceNode.createRelationshipTo( get( deviceNode.getGraphDatabase() ) , DataIncomeTypes.DEVICE_PUSH );
    } 
    
    // ================================================
    
    // should be executed under active transaction
    public static void setServerTcpIpPullDataIncomeTypeForDevice( Node deviceNode , String ip , int port )
    {
        removeDataIncomeTypeFromDevice( deviceNode );
            
        Relationship r = deviceNode.createRelationshipTo( get( deviceNode.getGraphDatabase() ) , DataIncomeTypes.SERVER_TCPIP_PULL );
        r.setProperty( "ip" , ip );
        r.setProperty( "port" , port );
    } 
    
    // ================================================
    
    private static void removeDataIncomeTypeFromDevice( Node deviceNode )
    {
        Iterator< Relationship > iter = deviceNode.getRelationships( Direction.OUTGOING , DataIncomeTypes.values() ).iterator();
        while( iter.hasNext() ) iter.next().delete();
    } 
    
    // ================================================
    
    // delete main incomming relation, this node,
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