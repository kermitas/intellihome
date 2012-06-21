package as.intellihome.neo4j.objects.impl;

import as.intellihome.neo4j.objects.Relations;
import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================

public class LocationManager implements as.intellihome.neo4j.objects.LocationManager
{
    private final GraphDatabaseService graphDb;
    
    // ================================================
    
    public LocationManager( GraphDatabaseService graphDb )
    {
        this.graphDb = graphDb;
    }
    
    // ================================================
    
    public static LocationManager get( GraphDatabaseService graphDb )
    {
        return new LocationManager( graphDb );
    }   
    
    // ================================================
    
    @Override
    public as.intellihome.neo4j.objects.Location setLocation( as.intellihome.neo4j.objects.Device device , String name , String description , double x , double y , double z )
    {
        return setLocation( device.getNode() , name , description , x , y , z );
    }   
    
    // ================================================
    
    @Override
    public as.intellihome.neo4j.objects.Location setLocation( as.intellihome.neo4j.objects.Sensor sensor , String name , String description , double x , double y , double z )
    {
        return setLocation( sensor.getNode() , name , description , x , y , z );
    }   
    
    // ================================================
    
    private as.intellihome.neo4j.objects.Location setLocation( Node deviceOrSensorNode , String name , String description , double x , double y , double z )
    {
        Transaction tx = deviceOrSensorNode.getGraphDatabase().beginTx();
        try
        {
            Iterator< Relationship > iter = deviceOrSensorNode.getRelationships( Direction.OUTGOING , Relations.Location.HAS_LOCATION ).iterator();
            while( iter.hasNext() )
            {
                Relationship r = iter.next();
                
                r.getEndNode().delete();
                r.delete();
            }            
            
            Node locationNode = deviceOrSensorNode.getGraphDatabase().createNode();

            locationNode.setProperty( "name" , name );
            locationNode.setProperty( "description" , description );
            locationNode.setProperty( "x" , x );
            locationNode.setProperty( "y" , y );
            locationNode.setProperty( "z" , z );
                
            deviceOrSensorNode.createRelationshipTo( locationNode , Relations.Location.HAS_LOCATION );
            
            tx.success();
            
            return new Location( locationNode );
        }
        finally
        {
            tx.finish();
        }
    }
 
    // ================================================
    
    @Override
    public boolean containsLocation( as.intellihome.neo4j.objects.Device device )
    {
        return containsLocation( device.getNode() );
    }
    
    // ================================================
    
    @Override
    public boolean containsLocation( as.intellihome.neo4j.objects.Sensor sensor )
    {
        return containsLocation( sensor.getNode() );
    }
    
    // ================================================
    
    private boolean containsLocation( Node deviceOrSensorNode )
    {
        return deviceOrSensorNode.hasRelationship( Direction.OUTGOING , Relations.Location.HAS_LOCATION );
    }
        
    // ================================================
    
    @Override
    public as.intellihome.neo4j.objects.Location getLocation( as.intellihome.neo4j.objects.Device device )
    {
        return getLocation( device.getNode() );
    }
    
    // ================================================
    
    @Override
    public as.intellihome.neo4j.objects.Location getLocation( as.intellihome.neo4j.objects.Sensor sensor )
    {
        return getLocation( sensor.getNode() );
    }
    
    // ================================================
    
    private as.intellihome.neo4j.objects.Location getLocation( Node deviceOrSensorNode )
    {
        Relationship r = deviceOrSensorNode.getSingleRelationship( Relations.Location.HAS_LOCATION , Direction.OUTGOING );
        return new Location( r.getEndNode() );
    }    
    
    // ================================================
}

// ====================================================