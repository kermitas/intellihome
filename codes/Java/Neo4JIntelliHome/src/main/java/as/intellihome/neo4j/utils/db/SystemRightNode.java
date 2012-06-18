package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.Direction;
import org.neo4j.graphdb.Node;
import org.neo4j.graphdb.Relationship;
import org.neo4j.graphdb.RelationshipType;

// ====================================================

enum SystemRightRelationships implements RelationshipType
{
    ADMIN_LOGIN , DEVICE_CREATOR , SENSOR_CREATOR
}

// ====================================================

public class SystemRightNode
{
    // ================================================
    
    // creates relation like ADMIN_LOGIN, DEVICE_CREATOR, SENSOR_CREATOR and empty nodes at the end of each relation
    // should be executed under active transaction
    public static void createDefaultData( Node systemRightsNode )
    {
        Node adminLoginNode = systemRightsNode.getGraphDatabase().createNode();
        systemRightsNode.createRelationshipTo( adminLoginNode , SystemRightRelationships.ADMIN_LOGIN );

        Node deviceCreatorNode = systemRightsNode.getGraphDatabase().createNode();
        systemRightsNode.createRelationshipTo( deviceCreatorNode , SystemRightRelationships.DEVICE_CREATOR );

        Node sensorCreatorNode = systemRightsNode.getGraphDatabase().createNode();
        systemRightsNode.createRelationshipTo( sensorCreatorNode , SystemRightRelationships.SENSOR_CREATOR );       
    }
    
    // ================================================
    
    // delete main incomming relation and node
    // should be executed under active transaction
    public static void delete( Node systemRightNode )
    {   
        Iterator< Relationship > iter = systemRightNode.getRelationships( Direction.INCOMING , SystemRightRelationships.values() ).iterator();

        while( iter.hasNext() )
        {
            Relationship r = iter.next();
            //System.out.println( SystemRightNode.class.getName() + ": deleting relation " + r.getId() );
            r.delete();
        }
        
        //System.out.println( SystemRightNode.class.getName() + ": deleting node " + systemRightNode.getId() );
        systemRightNode.delete();
    }
    
    // ================================================
}

// ====================================================