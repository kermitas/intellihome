package as.intellihome.neo4j.plugins.unmanaged;

import as.intellihome.neo4j.Config;
import as.intellihome.neo4j.utils.AdminHtml;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.Context;
import javax.ws.rs.core.MediaType;
import org.neo4j.graphdb.GraphDatabaseService;

// ====================================================

@Path( Config.pathFor_unmanagedPlugins_admin )
public class Admin
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
        
        AdminHtml.renderPageTop( sb , getClass().getSimpleName() , null , null );
        
        AdminHtml.renderButtonBasedOnForm( sb , Config.descriptionFor_managedPlugin_admin_install , Config.typeOfMethodForButtonsBaseOnForms , Config.pathFor_unmanagedPlugins + Config.pathFor_unmanagedPlugins_admin + Config.pathFor_unmanagedPlugins_admin_install );          
        AdminHtml.renderButtonBasedOnForm( sb , Config.descriptionFor_managedPlugin_admin_shutdown , Config.typeOfMethodForButtonsBaseOnForms , Config.pathFor_unmanagedPlugins + Config.pathFor_unmanagedPlugins_admin + Config.pathFor_unmanagedPlugins_admin_shutdown );          
        AdminHtml.renderButtonBasedOnForm( sb , Config.descriptionFor_managedPlugin_admin_createDb , Config.typeOfMethodForButtonsBaseOnForms , Config.pathFor_unmanagedPlugins + Config.pathFor_unmanagedPlugins_admin + Config.pathFor_unmanagedPlugins_admin_createDb );          
        AdminHtml.renderButtonBasedOnForm( sb , Config.descriptionFor_managedPlugin_admin_deleteDb , Config.typeOfMethodForButtonsBaseOnForms , Config.pathFor_unmanagedPlugins + Config.pathFor_unmanagedPlugins_admin + Config.pathFor_unmanagedPlugins_admin_deleteDb );          
        AdminHtml.renderButtonBasedOnForm( sb , Config.descriptionFor_managedPlugin_admin_addDefaultDataToDb , Config.typeOfMethodForButtonsBaseOnForms , Config.pathFor_unmanagedPlugins + Config.pathFor_unmanagedPlugins_admin + Config.pathFor_unmanagedPlugins_admin_addDefaultDataToDb );          
    
        AdminHtml.renderPageBottom( sb , null , null );
                  
        return sb.toString();
    }
    
    // ================================================
   
    @GET
    @Path( Config.pathFor_unmanagedPlugins_admin_install )
    @Produces( MediaType.TEXT_HTML )
    public String installServiceGET( @Context GraphDatabaseService graphDb ) { return installService( graphDb ); }    
    
    // ================================================
   
    @POST
    @Path( Config.pathFor_unmanagedPlugins_admin_install )
    @Produces( MediaType.TEXT_HTML )
    public String installServicePOST( @Context GraphDatabaseService graphDb ) { return installService( graphDb ); }    
    
    // ================================================    
    
    private String installService( @Context GraphDatabaseService graphDb )
    {
        StringBuilder sb = new StringBuilder();
        
        AdminHtml.renderPageTop( sb , getClass().getSimpleName() , Admin.class.getSimpleName() , Config.pathFor_unmanagedPlugins + Config.pathFor_unmanagedPlugins_admin );
        
        try
        {
            as.intellihome.neo4j.utils.Admin.install( graphDb );
            sb.append( "OK!" );
        }
        catch( Exception e )
        {
            AdminHtml.renderException( sb , e );
        }
        
        AdminHtml.renderPageBottom( sb , null , null );
                  
        return sb.toString();
    }
    
    // ================================================
    
    @GET
    @Path( Config.pathFor_unmanagedPlugins_admin_createDb )
    @Produces( MediaType.TEXT_HTML )
    public String createDbGET( @Context GraphDatabaseService graphDb ) { return createDb( graphDb ); }    
    
    // ================================================
   
    @POST
    @Path( Config.pathFor_unmanagedPlugins_admin_createDb )
    @Produces( MediaType.TEXT_HTML )
    public String createDbPOST( @Context GraphDatabaseService graphDb ) { return createDb( graphDb ); }    
    
    // ================================================    
    
    private String createDb( @Context GraphDatabaseService graphDb )
    {
        StringBuilder sb = new StringBuilder();
        
        AdminHtml.renderPageTop( sb , getClass().getSimpleName() , Admin.class.getSimpleName() , Config.pathFor_unmanagedPlugins + Config.pathFor_unmanagedPlugins_admin );
        
        try
        {
            as.intellihome.neo4j.utils.db.GeneralDbOperations.createDb( graphDb );
            sb.append( "OK!" );
        }
        catch( Exception e )
        {
            AdminHtml.renderException( sb , e );
        }
        
        AdminHtml.renderPageBottom( sb , null , null );
                  
        return sb.toString();
    }
    
    // ================================================
       
    @GET
    @Path( Config.pathFor_unmanagedPlugins_admin_deleteDb )
    @Produces( MediaType.TEXT_HTML )
    public String deleteDbGET( @Context GraphDatabaseService graphDb ) { return deleteDb( graphDb ); }    
    
    // ================================================
   
    @POST
    @Path( Config.pathFor_unmanagedPlugins_admin_deleteDb )
    @Produces( MediaType.TEXT_HTML )
    public String deleteDbPOST( @Context GraphDatabaseService graphDb ) { return deleteDb( graphDb ); }    
    
    // ================================================    
    
    private String deleteDb( @Context GraphDatabaseService graphDb )
    {
        StringBuilder sb = new StringBuilder();
        
        AdminHtml.renderPageTop( sb , getClass().getSimpleName() , Admin.class.getSimpleName() , Config.pathFor_unmanagedPlugins + Config.pathFor_unmanagedPlugins_admin );
        
        try
        {
            as.intellihome.neo4j.utils.db.GeneralDbOperations.deleteDb( graphDb );
            sb.append( "OK!" );
        }
        catch( Exception e )
        {
            AdminHtml.renderException( sb , e );
        }
        
        AdminHtml.renderPageBottom( sb , null , null );
                  
        return sb.toString();
    }
    
    // ================================================
   
    @GET
    @Path( Config.pathFor_unmanagedPlugins_admin_addDefaultDataToDb )
    @Produces( MediaType.TEXT_HTML )
    public String addDefaultDataToDbGET( @Context GraphDatabaseService graphDb ) { return addDefaultDataToDb( graphDb ); }    
    
    // ================================================
   
    @POST
    @Path( Config.pathFor_unmanagedPlugins_admin_addDefaultDataToDb )
    @Produces( MediaType.TEXT_HTML )
    public String addDefaultDataToDbPOST( @Context GraphDatabaseService graphDb ) { return addDefaultDataToDb( graphDb ); }    
    
    // ================================================    
    
    private String addDefaultDataToDb( @Context GraphDatabaseService graphDb )
    {
        StringBuilder sb = new StringBuilder();
        
        AdminHtml.renderPageTop( sb , getClass().getSimpleName() , Admin.class.getSimpleName() , Config.pathFor_unmanagedPlugins + Config.pathFor_unmanagedPlugins_admin );
        
        try
        {
            as.intellihome.neo4j.utils.db.GeneralDbOperations.addDefaultDataToDb( graphDb );
            sb.append( "OK!" );
        }
        catch( Exception e )
        {
            AdminHtml.renderException( sb , e );
        }
        
        AdminHtml.renderPageBottom( sb , null , null );
                  
        return sb.toString();
    }

    // ================================================
   
    @GET
    @Path( Config.pathFor_unmanagedPlugins_admin_shutdown )
    @Produces( MediaType.TEXT_HTML )
    public String shutdownDbGET( @Context GraphDatabaseService graphDb ) { return shutdownDb( graphDb ); }    
    
    // ================================================
   
    @POST
    @Path( Config.pathFor_unmanagedPlugins_admin_shutdown )
    @Produces( MediaType.TEXT_HTML )
    public String shutdownDbPOST( @Context GraphDatabaseService graphDb ) { return shutdownDb( graphDb ); }    
    
    // ================================================    
    
    private String shutdownDb( @Context GraphDatabaseService graphDb )
    {
        StringBuilder sb = new StringBuilder();
        
        AdminHtml.renderPageTop( sb , getClass().getSimpleName() , Admin.class.getSimpleName() , Config.pathFor_unmanagedPlugins + Config.pathFor_unmanagedPlugins_admin );
        
        try
        {
            as.intellihome.neo4j.utils.Admin.shutdown( graphDb );
            sb.append( "OK!" );
        }
        catch( Exception e )
        {
            AdminHtml.renderException( sb , e );
        }
        
        AdminHtml.renderPageBottom( sb , null , null );
                  
        return sb.toString();
    }
    
    // ================================================      
}
// ====================================================