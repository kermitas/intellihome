package as.intellihome.neo4j.objects;

// ====================================================

public interface LocationManager
{
    // ================================================
    
    public Location setLocation( Device device , String name , String description , double x , double y , double z );
    
    // ================================================
   
    public Location setLocation( Sensor sensor , String name , String description , double x , double y , double z );  
    
    // ================================================
    
    public boolean containsLocation( Device device );
    
    // ================================================
    
    public boolean containsLocation( Sensor sensor );
    
    // ================================================
    
    public Location getLocation( Device device );
    
    // ================================================
    
    public Location getLocation( Sensor sensor );
    
    // ================================================
}

// ====================================================