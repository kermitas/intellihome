package as.logserver.db;

import java.sql.Statement;
import java.sql.Connection;
import java.sql.DriverManager;

public class DatabaseGeneralOperationsOnEmbeddedApacheDerby implements DatabaseGeneralOperations
{
    public static final String protocol = "jdbc:derby:";
    public static final String databaseName = "LogServerDB";
    
    // ==============================================
    
    static
    {
        try
        {
            new org.apache.derby.jdbc.EmbeddedDriver();
        }
        catch( Exception ex )
        {
            throw new RuntimeException( ex );
        } 
    }
    
    // ==============================================
    
    @Override
    public void createDatabase()
    {
        Connection connection = null;
        
        try
        {
            connection = DriverManager.getConnection( protocol + databaseName + ";create=true");
            
            Statement statement = null;
            try
            {            
                statement = connection.createStatement();
            }
            catch( Exception ex )
            {
                throw new RuntimeException( ex );
            }         
            finally
            {
                try{ statement.close(); }catch(Exception e){}
            }
        }
        catch( Exception ex )
        {
            throw new RuntimeException( ex );
        }         
        finally
        {
            try{ connection.close(); }catch(Exception e){}
        }
    }

    // ==============================================
    
    @Override
    public void dropDatabase()
    {
        throw new UnsupportedOperationException("ApacheDerby does not support dropping database - please delete directory on your drive.");
    }

    // ==============================================
    
    @Override
    public void createTables()
    {
        Connection connection = null;
        
        try
        {
            connection = DriverManager.getConnection( protocol + databaseName );
            connection.setAutoCommit( false );
     
            Statement statement = null;
            try
            {            
                statement = connection.createStatement();
                
                StringBuilder sb = new StringBuilder();
                
                // ---
                
                sb.append( "CREATE TABLE tabelka1(" );
                    sb.append( "C1 VARCHAR(6)" );
                sb.append( ")" );
                
                statement.executeUpdate( sb.toString() );  
                
                // ---
                
                sb.setLength(0);
                
                sb.append( "CREATE TABLE tabelka2(" );
                    sb.append( "C1 VARCHAR(6)" );
                sb.append( ")" );
                
                statement.executeUpdate( sb.toString() );  
                
                // ---
                
                connection.commit();
            }
            catch( Exception ex )
            {
                try{ connection.rollback(); }catch(Exception e){}
                throw new RuntimeException( ex );
            }         
            finally
            {
                try{ statement.close(); }catch(Exception e){}
            }
        }
        catch( Exception ex )
        {
            throw new RuntimeException( ex );
        }         
        finally
        {
            try{ connection.close(); }catch(Exception e){}
        }
    }

    // ==============================================
    
    @Override
    public void dropTables()
    {
        Connection connection = null;
        
        try
        {
            connection = DriverManager.getConnection( protocol + databaseName );
            connection.setAutoCommit( false );
     
            Statement statement = null;
            try
            {            
                statement = connection.createStatement();
                statement.executeUpdate( "DROP TABLE tabelka1" ); 
                statement.executeUpdate( "DROP TABLE tabelka2" ); 
                
                connection.commit();
            }
            catch( Exception ex )
            {
                try{ connection.rollback(); }catch(Exception e){}
                throw new RuntimeException( ex );
            }         
            finally
            {
                try{ statement.close(); }catch(Exception e){}
            }
        }
        catch( Exception ex )
        {
            throw new RuntimeException( ex );
        }         
        finally
        {
            try{ connection.close(); }catch(Exception e){}
        }
    }

    // ==============================================
    
    @Override
    public void addInitialData()
    {
        throw new UnsupportedOperationException("Not supported yet.");
    }
    
    // ==============================================
}
