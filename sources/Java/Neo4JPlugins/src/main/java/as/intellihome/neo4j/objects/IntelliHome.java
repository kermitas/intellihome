package as.intellihome.neo4j.objects;

// ====================================================

public interface IntelliHome extends NodeContainer
{
    // ================================================
    
    public User createUser( String login , String password , String name , String description , boolean enabled , Relations.UserRight ... userRights );
    
    // ================================================
    
    public PhysicalityTypes getPysicalityTypes();
    
    // ================================================
    
    public InSystemLocalizationTypes getInSystemLocalizationTypes();    
    
    // ================================================
    
    public DataCollectingTypes getDataCollectingTypes();    

    // ================================================
    
    public DoorLocalizationTypes getDoorLocalizationTypes(); 
    
    // ================================================
    
    public DataIncomeTypes getDataIncomeTypes(); 
    
    // ================================================
    
    public SensorDataTypes getSensorDataTypes();     
        
    // ================================================
    
    public UserRightsGroup getUserRightsGroup();         
    
    // ================================================
    
    public UsersGroup getUsersGroup();      
    
    // ================================================
    
    public DevicesGroup getDevicesGroup();
    
    // ================================================
    
    public SensorsGroup getSensorsGroup();
    
    // ================================================
    
    public StartupTime addNewStartupTime();
    
    // ================================================
    
    public void setShutdownTime();    
    
    // ================================================
}

// ====================================================