package as.intellihome.neo4j.objects;

// ====================================================

public interface DataCollectingTypes extends NodeContainer
{
    // ================================================
    
    public void setDataCollectingType( Sensor sensor , Relations.DataCollectingType dataCollectingType );
    
    /*
    // ================================================
    
    public void setOverrideDataCollectingType( Sensor sensor );

    // ================================================
    
    public void setUnlimitedAppendDataCollectingType( Sensor sensor );
    
    // ================================================
    
    public void setAppendLimitedByTimeDataCollectingType( Sensor sensor , long expirationTime );
    
    // ================================================
    
    public void setAppendLimitedBySamplesCountDataCollectingType( Sensor sensor , int maxSamplesCount );
    */
    // ================================================
}

// ====================================================