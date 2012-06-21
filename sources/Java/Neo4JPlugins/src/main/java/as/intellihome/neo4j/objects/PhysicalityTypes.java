package as.intellihome.neo4j.objects;

public interface PhysicalityTypes extends NodeContainer
{
    // ================================================
    
    public void setPhysicalityType( Device device , Relations.PhysicalityType physicalityType );

    // ================================================
    
    public void setPhysicalityType( Sensor sensor , Relations.PhysicalityType physicalityType );
    
    // ================================================
}

// ====================================================