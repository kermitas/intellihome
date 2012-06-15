package as.intellihome.neo4j.plugins.unmanaged;

import as.intellihome.Config;
import as.intellihome.neo4j.utils.GeneralAdminHtml;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.Context;
import javax.ws.rs.core.MediaType;
import org.neo4j.graphdb.GraphDatabaseService;

// ====================================================

@Path( Config.pathFor_unmanagedPlugins_generalAdmin )
public class GeneralAdmin
{   
    // ================================================
   
    @GET
    @Path( "/" )
    @Produces( MediaType.TEXT_HTML )
    public String mainPageGET( @Context GraphDatabaseService graphDb ) { return generateMainPage( graphDb ); }    
    
    // ================================================
   
    @POST
    @Path( "/" )
    @Produces( MediaType.TEXT_HTML )
    public String mainPagePOST( @Context GraphDatabaseService graphDb ) { return generateMainPage( graphDb ); }    
    
    // ================================================    
    
    private String generateMainPage( @Context GraphDatabaseService graphDb )
    {
        StringBuilder sb = new StringBuilder();
        
        GeneralAdminHtml.renderPageTop( sb , getClass().getSimpleName() , null , null );
        
        GeneralAdminHtml.renderButtonBasedOnForm( sb , "Install IntelliHome service at Neo4J" , Config.typeOfMethodForButtonsBaseOnForms , Config.pathFor_unmanagedPlugins + Config.pathFor_unmanagedPlugins_generalAdmin + Config.pathFor_unmanagedPlugins_generalAdmin_installService );          
        GeneralAdminHtml.renderButtonBasedOnForm( sb , "Create DB" , Config.typeOfMethodForButtonsBaseOnForms , Config.pathFor_unmanagedPlugins + Config.pathFor_unmanagedPlugins_generalAdmin + Config.pathFor_unmanagedPlugins_generalAdmin_createDb );          
        GeneralAdminHtml.renderButtonBasedOnForm( sb , "Delete DB" , Config.typeOfMethodForButtonsBaseOnForms , Config.pathFor_unmanagedPlugins + Config.pathFor_unmanagedPlugins_generalAdmin + Config.pathFor_unmanagedPlugins_generalAdmin_deleteDb );          
        GeneralAdminHtml.renderButtonBasedOnForm( sb , "Add default data to DB" , Config.typeOfMethodForButtonsBaseOnForms , Config.pathFor_unmanagedPlugins + Config.pathFor_unmanagedPlugins_generalAdmin + Config.pathFor_unmanagedPlugins_generalAdmin_addDefaultDataToDb );          
    
        GeneralAdminHtml.renderPageBottom( sb , null , null );
                  
        return sb.toString();
    }
    
    // ================================================
   
    @GET
    @Path( Config.pathFor_unmanagedPlugins_generalAdmin_installService )
    @Produces( MediaType.TEXT_HTML )
    public String installServiceGET( @Context GraphDatabaseService graphDb ) { return installService( graphDb ); }    
    
    // ================================================
   
    @POST
    @Path( Config.pathFor_unmanagedPlugins_generalAdmin_installService )
    @Produces( MediaType.TEXT_HTML )
    public String installServicePOST( @Context GraphDatabaseService graphDb ) { return installService( graphDb ); }    
    
    // ================================================    
    
    private String installService( @Context GraphDatabaseService graphDb )
    {
        StringBuilder sb = new StringBuilder();
        
        GeneralAdminHtml.renderPageTop( sb , getClass().getSimpleName() , GeneralAdmin.class.getSimpleName() , Config.pathFor_unmanagedPlugins + Config.pathFor_unmanagedPlugins_generalAdmin );
        
        try
        {
            as.intellihome.neo4j.utils.GeneralAdmin.installService( graphDb );
        }
        catch( Exception e )
        {
            GeneralAdminHtml.renderException( sb , e );
        }
        
        GeneralAdminHtml.renderPageBottom( sb , null , null );
                  
        return sb.toString();
    }
    
    // ================================================
    
    @GET
    @Path( Config.pathFor_unmanagedPlugins_generalAdmin_createDb )
    @Produces( MediaType.TEXT_HTML )
    public String createDbGET( @Context GraphDatabaseService graphDb ) { return createDb( graphDb ); }    
    
    // ================================================
   
    @POST
    @Path( Config.pathFor_unmanagedPlugins_generalAdmin_createDb )
    @Produces( MediaType.TEXT_HTML )
    public String createDbPOST( @Context GraphDatabaseService graphDb ) { return createDb( graphDb ); }    
    
    // ================================================    
    
    private String createDb( @Context GraphDatabaseService graphDb )
    {
        StringBuilder sb = new StringBuilder();
        
        GeneralAdminHtml.renderPageTop( sb , getClass().getSimpleName() , GeneralAdmin.class.getSimpleName() , Config.pathFor_unmanagedPlugins + Config.pathFor_unmanagedPlugins_generalAdmin );
        
        try
        {
            as.intellihome.neo4j.utils.GeneralAdmin.createDb( graphDb );
        }
        catch( Exception e )
        {
            GeneralAdminHtml.renderException( sb , e );
        }
        
        GeneralAdminHtml.renderPageBottom( sb , null , null );
                  
        return sb.toString();
    }
    
    // ================================================
       
    @GET
    @Path( Config.pathFor_unmanagedPlugins_generalAdmin_deleteDb )
    @Produces( MediaType.TEXT_HTML )
    public String deleteDbGET( @Context GraphDatabaseService graphDb ) { return deleteDb( graphDb ); }    
    
    // ================================================
   
    @POST
    @Path( Config.pathFor_unmanagedPlugins_generalAdmin_deleteDb )
    @Produces( MediaType.TEXT_HTML )
    public String deleteDbPOST( @Context GraphDatabaseService graphDb ) { return deleteDb( graphDb ); }    
    
    // ================================================    
    
    private String deleteDb( @Context GraphDatabaseService graphDb )
    {
        StringBuilder sb = new StringBuilder();
        
        GeneralAdminHtml.renderPageTop( sb , getClass().getSimpleName() , GeneralAdmin.class.getSimpleName() , Config.pathFor_unmanagedPlugins + Config.pathFor_unmanagedPlugins_generalAdmin );
        
        try
        {
            as.intellihome.neo4j.utils.GeneralAdmin.deleteDb( graphDb );
        }
        catch( Exception e )
        {
            GeneralAdminHtml.renderException( sb , e );
        }
        
        GeneralAdminHtml.renderPageBottom( sb , null , null );
                  
        return sb.toString();
    }
    
    // ================================================
   
    @GET
    @Path( Config.pathFor_unmanagedPlugins_generalAdmin_addDefaultDataToDb )
    @Produces( MediaType.TEXT_HTML )
    public String addDefaultDataToDbGET( @Context GraphDatabaseService graphDb ) { return addDefaultDataToDb( graphDb ); }    
    
    // ================================================
   
    @POST
    @Path( Config.pathFor_unmanagedPlugins_generalAdmin_addDefaultDataToDb )
    @Produces( MediaType.TEXT_HTML )
    public String addDefaultDataToDbPOST( @Context GraphDatabaseService graphDb ) { return addDefaultDataToDb( graphDb ); }    
    
    // ================================================    
    
    private String addDefaultDataToDb( @Context GraphDatabaseService graphDb )
    {
        StringBuilder sb = new StringBuilder();
        
        GeneralAdminHtml.renderPageTop( sb , getClass().getSimpleName() , GeneralAdmin.class.getSimpleName() , Config.pathFor_unmanagedPlugins + Config.pathFor_unmanagedPlugins_generalAdmin );
        
        try
        {
            as.intellihome.neo4j.utils.GeneralAdmin.addDefaultDataToDb( graphDb );
        }
        catch( Exception e )
        {
            GeneralAdminHtml.renderException( sb , e );
        }
        
        GeneralAdminHtml.renderPageBottom( sb , null , null );
                  
        return sb.toString();
    }

    // ================================================      
}
// ====================================================