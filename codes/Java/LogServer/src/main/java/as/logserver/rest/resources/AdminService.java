package as.logserver.rest.resources;

import as.logserver.Config;
import as.logserver.rest.AdminHtmlUtils;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;

// ==================================================

@Path(Config.contextPathForRestAdminService)
public class AdminService
{
    // ==============================================
    
    @GET
    @Path("/")
    @Produces( MediaType.TEXT_HTML )
    public String renderAdminPanelInHTML()
    {
        StringBuilder sb = new StringBuilder();
        
        AdminHtmlUtils.renderPageTopForAdmin( sb , getClass().getSimpleName() , null , null );
        
        AdminHtmlUtils.renderButtonBasedOnForm( sb , "Go to database general operations" , "POST" , Config.contextPathForRestService + Config.contextPathForRestAdminService + Config.contextPathForRestAdminDatabaseGeneralService );          
    
        AdminHtmlUtils.renderPageBottomForAdmin( sb , null , null );
                  
        return sb.toString();
    }
      
    // ==============================================
    
    /*
    @GET
    @Path("/xml")
    @Produces( MediaType.APPLICATION_XML )
    public TestPOJO getXMLMessage()
    {
        TestPOJO r = new TestPOJO();
        r.setName( "Artur XML" );
        return r;
    }  
    
    @GET
    @Path("/json")
    @Produces( MediaType.APPLICATION_JSON )
    public TestPOJO getJSONMessage()
    {
        TestPOJO r = new TestPOJO();
        r.setName( "Artur JSON" );
        return r;
    }*/
}

// ==================================================