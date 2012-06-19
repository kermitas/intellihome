package as.logserver.db;

public class DatabaseGeneralOperationsFactory
{
    // ==============================================
    
    public static DatabaseGeneralOperations getNewInstance()
    {
        return new DatabaseGeneralOperationsOnEmbeddedApacheDerby();
    }
    
    // ==============================================
}
