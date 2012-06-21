package as.intellihome.neo4j.objects;

// ====================================================

public interface Device extends NodeContainer
{
    // ================================================
    
    public Sensor createSensor( String name , String description , boolean enabled , as.intellihome.neo4j.objects.Relations.PhysicalityType physicalityType ,  as.intellihome.neo4j.objects.Relations.DataCollectingType dataCollectingType , as.intellihome.neo4j.objects.Relations.DoorLocalizationType doorLocalizationType , as.intellihome.neo4j.objects.Relations.SensorDataType sensorDataType , String locationName , String locationDescription , double locationX , double locationY , double locationZ );
    
    // ================================================
}

// ====================================================