package as.intellihome;

// ====================================================

public class Config
{

    // ---
    
    public static final String pathFor_managedPlugin_sensorSamplesCollector_collectInteger = "i";
    public static final String pathFor_managedPlugin_sensorSamplesCollector_collectFloat = "f";
    public static final String pathFor_managedPlugin_sensorSamplesCollector_collectBoolean = "b";
    public static final String pathFor_managedPlugin_sensorSamplesCollector_collectString = "s";
    
    // ---
    
    public static final String restParameterNameFor_sensorSamplesCollector_sensorId = "s";
    public static final String restParameterNameFor_sensorSamplesCollector_sensorValue = "v";
            
    // ---
    
    public static final String pathFor_managedPlugin_generalAdmin_installService = "installService";
    public static final String pathFor_managedPlugin_generalAdmin_createDb = "createDb";
    public static final String pathFor_managedPlugin_generalAdmin_deleteDb = "deleteDb";
    public static final String pathFor_managedPlugin_generalAdmin_addDefaultDataToDb = "addDefaultDataToDb";
    
    // ---
    
    public static final String pathFor_unmanagedPlugins = "/plugins";
    public static final String pathFor_unmanagedPlugins_generalAdmin = "/GeneralAdmin";
    public static final String pathFor_unmanagedPlugins_generalAdmin_installService = "/" + pathFor_managedPlugin_generalAdmin_installService;
    public static final String pathFor_unmanagedPlugins_generalAdmin_createDb = "/" + pathFor_managedPlugin_generalAdmin_createDb;
    public static final String pathFor_unmanagedPlugins_generalAdmin_deleteDb = "/" + pathFor_managedPlugin_generalAdmin_deleteDb;
    public static final String pathFor_unmanagedPlugins_generalAdmin_addDefaultDataToDb = "/" + pathFor_managedPlugin_generalAdmin_addDefaultDataToDb;
   
    // ---
    
    public static final String typeOfMethodForButtonsBaseOnForms = "POST";
    
    // ---
    
}

// ====================================================