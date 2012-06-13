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
            if( doDbContainsIntelliHomeGraph( graphDb ) )
            {
                addNewIntelliHomeSystemStartupTime( graphDb );
            }

            // maybe install graphDb.registerTransactionEventHandler( )

            isInstalled = true;
            
        }
        else
            throw new IllegalStateException( "already installed" );
    }
    
    // ================================================
    
    public static synchronized void createInitialDatabaseGraph( GraphDatabaseService graphDb )
    {
        if( doDbContainsIntelliHomeGraph( graphDb ) )
        {
            throw new IllegalStateException( "database already contains IntelliHome graph" );
        }   
        else
        {
            // TODO create new
        }
    }   
    
    // ================================================
    
    public static synchronized boolean doDbContainsIntelliHomeGraph( GraphDatabaseService graphDb )
    {
        throw new UnsupportedOperationException( "not implemented yet" );
    }
    
    // ================================================
    
    public static synchronized void addNewIntelliHomeSystemStartupTime( GraphDatabaseService graphDb )
    {
        // TODO add new node to linked list
        
        throw new UnsupportedOperationException( "not implemented yet" );
    }
    
    // ================================================
}

// ====================================================