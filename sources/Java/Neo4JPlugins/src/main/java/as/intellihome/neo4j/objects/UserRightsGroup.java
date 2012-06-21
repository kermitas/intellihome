package as.intellihome.neo4j.objects;

// ====================================================

public interface UserRightsGroup extends NodeContainer
{
    // ================================================
    
    public void addRightToUser( User user , Relations.UserRight userRight );

    // ================================================
    
    public void addRightToUser( User user , Relations.UserRight ... userRights );
    
    // ================================================
}

// ====================================================