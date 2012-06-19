package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.Direction;
import org.neo4j.graphdb.Node;
import org.neo4j.graphdb.Relationship;
import org.neo4j.graphdb.RelationshipType;

// ====================================================

enum DataIncomeTypeRelationships implements RelationshipType
{
    DEVICE_PUSH , SERVER_PULL_TYPES
}

// ====================================================

// SERVER_PULL_TYPES node is a group for many kinds of server pull
// for example, in future there can be outgoint relation SERVER_TCPIP_PULL to node with properties like ip : String, port : int

// ====================================================

public class DataIncomeTypeNode
{
    // ================================================
    
    // creates relation like DEVICE_PUSH , SERVER_PULL_TYPES and empty nodes at the end of each relation
    // should be executed under active transaction
    public static void createDefaultData( Node dataIncomeTypesNode , boolean addDecriptionProperty )
    {
        Node devicePushNode = dataIncomeTypesNode.getGraphDatabase().createNode();
        if( addDecriptionProperty ) devicePushNode.setProperty( "description" , "Singleton node - it is device's business to push data to server." );
        dataIncomeTypesNode.createRelationshipTo( devicePushNode , DataIncomeTypeRelationships.DEVICE_PUSH );

        Node serverPullTypesNode = dataIncomeTypesNode.getGraphDatabase().createNode();
        if( addDecriptionProperty ) serverPullTypesNode.setProperty( "description" , "Singleton node - a group of server pull types (for example - tcp/ip pull)." );
        dataIncomeTypesNode.createRelationshipTo( serverPullTypesNode , DataIncomeTypeRelationships.SERVER_PULL_TYPES );    
        
        DataIncomeServerPullTypeNode.add( serverPullTypesNode , addDecriptionProperty , "192.168.te.st" , 12345 );
    }
    
    // ================================================
    
    // delete main incomming relation and node
    // should be executed under active transaction
    public static void delete( Node dataIncomeTypeNode )
    {   
        //System.out.println( "!!! deleting dataIncomeTypeNode = " + dataIncomeTypeNode.getId() );
        
        if( dataIncomeTypeNode.hasRelationship( DataIncomeTypeRelationships.SERVER_PULL_TYPES , Direction.INCOMING ) )
        {            
            //System.out.println( "!!! found SERVER_PULL_TYPES !! in dataIncomeTypeNode " + dataIncomeTypeNode.getId() );
            
            Iterator< Relationship > iter1 = dataIncomeTypeNode.getRelationships( Direction.OUTGOING , DataIncomeServerPullTypeRelationships.values() ).iterator();

            while( iter1.hasNext() ) DataIncomeServerPullTypeNode.delete( iter1.next().getEndNode() );            
        }
        
        Iterator< Relationship > iter = dataIncomeTypeNode.getRelationships( Direction.INCOMING , DataIncomeTypeRelationships.values() ).iterator();

        while( iter.hasNext() )
        {
            Relationship r = iter.next();
            r.delete();
        }
        
        dataIncomeTypeNode.delete();
    }
    
    // ================================================
}

// ====================================================