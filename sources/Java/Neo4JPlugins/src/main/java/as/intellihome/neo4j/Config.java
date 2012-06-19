package as.intellihome.neo4j;

// ====================================================

public class Config
{

    // ---
    
    public static final int interlliHomeMajorVersion = 0;
    public static final int interlliHomeMinorVersion = 1;
    
    // ---
    
    public static final int shutdownWaitTimeBeforeExecutionSystemExit = 5 * 1000;
    
    // ---
    
    public static final String pathFor_managedPlugin_sensorSamplesCollector_collectInteger = "i";
    public static final String pathFor_managedPlugin_sensorSamplesCollector_collectFloat = "f";
    public static final String pathFor_managedPlugin_sensorSamplesCollector_collectBoolean = "b";
    public static final String pathFor_managedPlugin_sensorSamplesCollector_collectString = "s";
    
    // ---
    
    public static final String restParameterNameFor_sensorSamplesCollector_sensorId = "s";
    public static final String restParameterNameFor_sensorSamplesCollector_sensorValue = "v";
            
    // ---
    
    public static final String pathFor_managedPlugin_admin_install = "install";
    public static final String descriptionFor_managedPlugin_admin_install = "Install IntelliHome service (one time action should be executed just after startup).";
    
    public static final String pathFor_managedPlugin_admin_createDb = "createDb";
    public static final String descriptionFor_managedPlugin_admin_createDb = "Create database.";
    
    public static final String pathFor_managedPlugin_admin_deleteDb = "deleteDb";
    public static final String descriptionFor_managedPlugin_admin_deleteDb = "Delete database.";
    
    public static final String pathFor_managedPlugin_admin_addDefaultDataToDb = "addDefaultDataToDb";
    public static final String descriptionFor_managedPlugin_admin_addDefaultDataToDb = "Add default data to DB.";
    
    public static final String pathFor_managedPlugin_admin_shutdown = "shutdown";
    public static final String descriptionFor_managedPlugin_admin_shutdown = "Shutdown IntelliHome (will terminat JVM in about " + shutdownWaitTimeBeforeExecutionSystemExit + " ms).";
    
    // ---
    
    public static final String pathFor_unmanagedPlugins = "/plugins";
    public static final String pathFor_unmanagedPlugins_admin = "/Admin";
    public static final String pathFor_unmanagedPlugins_admin_install = "/" + pathFor_managedPlugin_admin_install;
    public static final String pathFor_unmanagedPlugins_admin_createDb = "/" + pathFor_managedPlugin_admin_createDb;
    public static final String pathFor_unmanagedPlugins_admin_deleteDb = "/" + pathFor_managedPlugin_admin_deleteDb;
    public static final String pathFor_unmanagedPlugins_admin_addDefaultDataToDb = "/" + pathFor_managedPlugin_admin_addDefaultDataToDb;
    public static final String pathFor_unmanagedPlugins_admin_shutdown = "/" + pathFor_managedPlugin_admin_shutdown;
   
    // ---
    
    public static final String typeOfMethodForButtonsBaseOnForms = "POST";
    
    // ---
    
}

// ====================================================