package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.Direction;
import org.neo4j.graphdb.Node;
import org.neo4j.graphdb.Relationship;
import org.neo4j.graphdb.RelationshipType;

// ====================================================

enum DataIncomeServerPullTypeRelationships implements RelationshipType
{
    SERVER_TCPIP_PULL
}

// ====================================================

// SERVER_PULL_TYPES node is a group for many kinds of server pull
// for example, in future there can be outgoint relation SERVER_TCPIP_PULL to node with properties like ip : String, port : int

// ====================================================

public class DataIncomeServerPullTypeNode
{
    // ================================================
    
    // creates relation like SERVER_TCPIP_PULL and empty nodes at the end of each relation
    // should be executed under active transaction
    public static void add( Node serverPullTypesNode , boolean addDecriptionProperty , String ip , int port )
    {
        Node serverTcpIpPullNode = serverPullTypesNode.getGraphDatabase().createNode();
        
        if( addDecriptionProperty ) serverTcpIpPullNode.setProperty( "description" , "Server will use this ip and port to pull data from device." );
        serverTcpIpPullNode.setProperty( "ip" , ip );
        serverTcpIpPullNode.setProperty( "port" , port );
        
        serverPullTypesNode.createRelationshipTo( serverTcpIpPullNode , DataIncomeServerPullTypeRelationships.SERVER_TCPIP_PULL );
    }
    
    // ================================================
    
    // delete main incomming relation and node
    // should be executed under active transaction
    public static void delete( Node dataIncomeServerPullTypeNode )
    {   
        //System.out.println( "!!! deleting dataIncomeServerPullTypeNode = " + dataIncomeServerPullTypeNode.getId() );
        
        Iterator< Relationship > iter = dataIncomeServerPullTypeNode.getRelationships( Direction.INCOMING , DataIncomeServerPullTypeRelationships.values() ).iterator();

        while( iter.hasNext() )
        {
            Relationship r = iter.next();
            r.delete();
        }
        
        dataIncomeServerPullTypeNode.delete();
    }
    
    // ================================================
}

// ====================================================