package as.intellihome.neo4j.objects;

// ====================================================

public interface User extends NodeContainer
{
    // ================================================

    public Device createDevice( String name , String description , boolean enabled , as.intellihome.neo4j.objects.Relations.PhysicalityType physicalityType , as.intellihome.neo4j.objects.Relations.DataIncomeType dataIncomeType , as.intellihome.neo4j.objects.Relations.InSystemLocalizationType inSystemLocalizationType , String locationName , String locationDescription , double locationX , double locationY , double locationZ );
    
    // ================================================
}

// ====================================================