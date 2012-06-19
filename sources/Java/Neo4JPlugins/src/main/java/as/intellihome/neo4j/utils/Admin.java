package as.intellihome.neo4j.utils;

import as.intellihome.neo4j.utils.db.GeneralDbOperations;
import as.intellihome.neo4j.utils.db.IntelliHomeNode;
import as.intellihome.neo4j.utils.db.StartupNode;
import org.neo4j.graphdb.GraphDatabaseService;

// ====================================================

public class Admin
{
    private static boolean isInstalled = false;
    
    // ================================================
    
    public static synchronized void install( GraphDatabaseService graphDb )
    {
        if( !isInstalled )
        {
            //if( !IntelliHomeNode.exists( graphDb ) ) throw new IllegalStateException( "database should contain IntelliHome graph" );
            if( !IntelliHomeNode.exists( graphDb ) ) GeneralDbOperations.createDb( graphDb );
            
            // maybe install graphDb.registerTransactionEventHandler( )
            
            StartupNode.addNewStartupNode( IntelliHomeNode.get( graphDb ) );

            isInstalled = true;
        }
        else
            throw new IllegalStateException( "already installed" );
    }
    
    // ================================================
    
    public static void shutdown( final GraphDatabaseService graphDb )
    {
        try { StartupNode.setShutdownTime( IntelliHomeNode.get( graphDb ) ); } catch (Exception e) { }
        
        Thread t = new Thread()
        {
            @Override
            public void run()
            {
                //try { Thread.sleep( 1000 ); } catch (InterruptedException ie) { }
                
                graphDb.shutdown();
                
                try { Thread.sleep( as.intellihome.neo4j.Config.shutdownWaitTimeBeforeExecutionSystemExit ); } catch (InterruptedException ie) { }
                
                System.exit( 0 );
            }
        };
        
        t.setDaemon( true );
        t.start();
    }    
    
    // ================================================
}

// ====================================================