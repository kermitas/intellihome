package as.intellihome.neo4j.utils;

import java.util.logging.Level;
import java.util.logging.Logger;
import org.neo4j.graphdb.GraphDatabaseService;

// ====================================================

public class Admin
{
    private static boolean isInstalled = false;
    
    // ================================================
    
    public static synchronized void installService( GraphDatabaseService graphDb )
    {
        if( !isInstalled )
        {
            if( !DatabaseAdmin.doDbContainsIntelliHomeGraph( graphDb ) ) throw new IllegalStateException( "database should contain IntelliHome graph" );
                
            // maybe install graphDb.registerTransactionEventHandler( )
            
            DatabaseAdmin.addNewIntelliHomeSystemStartupTime( graphDb );

            isInstalled = true;
        }
        else
            throw new IllegalStateException( "already installed" );
    }
    
    // ================================================
    
    public static void shutdownIntelliHome( final GraphDatabaseService graphDb )
    {
        try { DatabaseAdmin.addNewIntelliHomeSystemShutdownTime( graphDb ); } catch (Exception e) { }
        
        Thread t = new Thread()
        {
            @Override
            public void run()
            {
                //try { Thread.sleep( 1000 ); } catch (InterruptedException ie) { }
                
                graphDb.shutdown();
                
                try { Thread.sleep( as.intellihome.Config.shutdownWaitTimeBeforeExecutionSystemExit ); } catch (InterruptedException ie) { }
                
                System.exit( 0 );
            }
        };
        
        t.setDaemon( true );
        t.start();
    }    
    
    // ================================================
}

// ====================================================