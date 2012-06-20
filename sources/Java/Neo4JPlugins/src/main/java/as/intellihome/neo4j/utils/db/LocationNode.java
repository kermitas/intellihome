package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================

public class LocationNode
{
    // ================================================
    
    // creates relation LOCATION and node
    // should be executed under active transaction
    public static void create( Node deviceNode , String name , String description , Double x , Double y , Double z )
    {
        Node locationNode = deviceNode.getGraphDatabase().createNode();
        
        locationNode.setProperty( "name" , name );
        locationNode.setProperty( "description" , name );
        locationNode.setProperty( "x" , x );
        locationNode.setProperty( "y" , y );
        locationNode.setProperty( "z" , z );
        
        deviceNode.createRelationshipTo( locationNode , Location.LOCATION );
    }
   
    // ================================================
    
    // should be executed under active transaction
    public static void delete( Node ownerDeviceOrSensorNode )
    {   
        Iterator< Relationship > iter = ownerDeviceOrSensorNode.getRelationships( Direction.OUTGOING , Location.LOCATION ).iterator();
        while( iter.hasNext() )
        {
            Relationship r = iter.next();
            
            r.getEndNode().delete();
            r.delete();
        }
    }
    
    // ================================================
}

// ====================================================