package as.intellihome.neo4j.objects;

// ====================================================

public interface Sensor extends NodeContainer
{
    // ================================================
    
    public SensorSample createSensorSample( Object sample );
    
    // ================================================
    
    public boolean containsSensorSample();
    
    // ================================================
    
    public SensorSample getLatestSensorSample();
    
    // ================================================
    
    public Relations.DataCollectingType getDataCollectingType();
    
    // ================================================
}

// ====================================================