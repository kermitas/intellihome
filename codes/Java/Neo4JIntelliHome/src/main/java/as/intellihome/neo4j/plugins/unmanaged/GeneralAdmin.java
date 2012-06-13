package as.intellihome.neo4j.plugins.unmanaged;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.Context;
import javax.ws.rs.core.MediaType;
import org.neo4j.graphdb.GraphDatabaseService;

// ====================================================

@Path( "/generalAdmin" )
public class GeneralAdmin
{
    // ================================================
    
    //public GeneralAdmin( @Context GraphDatabaseService graphDb )
    //{
        
    //}
    
    // ================================================
   
    @GET
    @Path("/")
    @Produces( MediaType.TEXT_HTML )
    public String unmanagedTest( @Context GraphDatabaseService graphDb )
    {
        StringBuilder sb = new StringBuilder();
        
        try
        {
            
            sb.append( "OK! " ).append( System.currentTimeMillis() );
        }
        catch( Exception e )
        {
            sb.append( e.toString() );
        }
        
        return sb.toString();
    }  
    
    // ================================================    
}
// ====================================================