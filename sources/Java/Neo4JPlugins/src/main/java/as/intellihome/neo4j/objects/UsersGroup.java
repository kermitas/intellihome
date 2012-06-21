package as.intellihome.neo4j.objects;

// ====================================================

public interface UsersGroup extends NodeContainer
{
    // ================================================
    
    public boolean containsUserByLogin( String login );
    
    // ================================================
    
    public void addUserToGroup( User user );

    // ================================================
    
    public User createUser( String login , String password , String name , String description , boolean enabled );
    
    // ================================================
}

// ====================================================