package as.intellihome.neo4j.utils;

import org.neo4j.graphdb.GraphDatabaseService;

// ====================================================

public class GeneralAdmin
{
    private static boolean isInstalled = false;
    
    // ================================================
    
    public static synchronized void installIntelliHomeOnNeo4J( GraphDatabaseService graphDb )
    {
        if( !isInstalled )
        {
            if( !doDbContainsIntelliHomeGraph( graphDb ) ) createInitialIntelliHomeDbGraph( graphDb );
                
            addNewIntelliHomeSystemStartupTime( graphDb );

            // maybe install graphDb.registerTransactionEventHandler( )

            isInstalled = true;
            
        }
        else
            throw new IllegalStateException( "already installed" );
    }
    
    // ================================================
    
    private static void createInitialIntelliHomeDbGraph( GraphDatabaseService graphDb )
    {
        if( doDbContainsIntelliHomeGraph( graphDb ) )
        {
            throw new IllegalStateException( "database already contains IntelliHome graph" );
        }   
        else
        {
            // TODO create new
            
            throw new UnsupportedOperationException( "not implemented yet" );
        }
    }   
    
    // ================================================
    
    private static boolean doDbContainsIntelliHomeGraph( GraphDatabaseService graphDb )
    {
        // TODO
        
        throw new UnsupportedOperationException( "not implemented yet" );
    }
    
    // ================================================
    
    private static void addNewIntelliHomeSystemStartupTime( GraphDatabaseService graphDb )
    {
        // TODO add new node to linked list
        
        throw new UnsupportedOperationException( "not implemented yet" );
    }
    
// ================================================
    
    public static void addDefaultData( GraphDatabaseService graphDb )
    {
        // TODO
        
        // check somehow if default data is already added? how? for example check if user with login "DefaultUser" exists
        
        // add user 'DefaultUser'
        // add device to this users
        // add temperature sensor to this device
        // add few temperature samples
        
        throw new UnsupportedOperationException( "not implemented yet" );
    }
    
// ================================================
    
    public static void deleteDb( GraphDatabaseService graphDb )
    {
        // TODO
        
        throw new UnsupportedOperationException( "not implemented yet" );
    }
    
    // ================================================
}

// ====================================================