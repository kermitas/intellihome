package as.intellihome.neo4j.objects;

// ====================================================

public interface StartupTimeManager
{
    // ================================================
    
    public StartupTime addNewStartupTime();
    
    // ================================================
    
    public boolean containsStartupTime();

    // ================================================
    
    public StartupTime getLatestStartupTime();
    
    // ================================================
}

// ====================================================