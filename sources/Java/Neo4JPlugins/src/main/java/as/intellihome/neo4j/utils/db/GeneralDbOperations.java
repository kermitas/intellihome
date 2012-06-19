package as.intellihome.neo4j.utils.db;

import as.intellihome.neo4j.Config;
import org.neo4j.graphdb.GraphDatabaseService;
import org.neo4j.graphdb.Transaction;

// ====================================================

public class GeneralDbOperations
{
    // ================================================
    
    public static void createDb( GraphDatabaseService graphDb )
    {
        if( IntelliHomeNode.exists( graphDb ) )
        {
            throw new IllegalStateException( "database already contains IntelliHome graph" );
        }   
        else
        {
            Transaction tx = graphDb.beginTx();
            try
            {
                IntelliHomeNode.createDefaultData( graphDb , Config.addDescriptionPropertyToNodes , Config.interlliHomeMajorVersion , Config.interlliHomeMinorVersion );
                
                tx.success();
            }
            finally
            {
                tx.finish();
            }            
        }
    }   
    
    // ================================================
    
    public static void addDefaultDataToDb( GraphDatabaseService graphDb )
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
        // TODO execute some kind of query that deletes all nodes and relations but omit ReferenceNode
        
        Transaction tx = graphDb.beginTx();
        try
        {
            IntelliHomeNode.delete( graphDb );
            
            tx.success();
        }
        finally
        {
            tx.finish();
        }         
    }
    
    // ================================================
}

// ====================================================