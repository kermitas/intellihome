package as.logserver.rest.resources;

import as.logserver.Config;
import as.logserver.db.DatabaseGeneralOperationsFactory;
import as.logserver.rest.AdminHtmlUtils;
import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;

// ==================================================

@Path(Config.contextPathForRestAdminService + Config.contextPathForRestAdminDatabaseGeneralService)
public class AdminDatabaseGeneralService
{
    public static final String createDbPath = "/createdb";
    public static final String dropDbPath = "/dropdb";
    
    public static final String createTablesPath = "/createtables";
    public static final String dropTablesPath = "/droptables";
    
    public static final String addInitialDataPath = "/addinitialdata";
    
    private static final String httpMethodForButtonsBasedOnForms = "POST";
    
    // ==============================================
    
    @GET @Path("/") @Produces( MediaType.TEXT_HTML )
    public String renderDatabaseAdministrationPanelInHTML_GET() { return renderDatabaseAdministrationPanelInHTML(); }
    
    // ==============================================
    
    @POST @Path("/") @Produces( MediaType.TEXT_HTML )
    public String renderDatabaseAdministrationPanelInHTML_POST() { return renderDatabaseAdministrationPanelInHTML(); }
    
    // ==============================================
               
    private String renderDatabaseAdministrationPanelInHTML()
    {
        StringBuilder sb = new StringBuilder();
        
        AdminHtmlUtils.renderPageTopForAdmin( sb , getClass().getSimpleName() , AdminService.class.getSimpleName() , Config.contextPathForRestService + Config.contextPathForRestAdminService );
            
        sb.append( "<table style='border-style:none;'>" );
            sb.append( "<tr>" );
                sb.append( "<td>" );   
                    AdminHtmlUtils.renderButtonBasedOnForm( sb , "Create database" , httpMethodForButtonsBasedOnForms , Config.contextPathForRestService + Config.contextPathForRestAdminService + Config.contextPathForRestAdminDatabaseGeneralService + createDbPath );
                sb.append( "</td><td>&nbsp;</td><td>" );  
                    AdminHtmlUtils.renderButtonBasedOnForm( sb , "Drop database" , httpMethodForButtonsBasedOnForms , Config.contextPathForRestService + Config.contextPathForRestAdminService + Config.contextPathForRestAdminDatabaseGeneralService + dropDbPath );
                sb.append( "</td>" );                
            sb.append( "</tr>" );
        sb.append( "</table>" );
            
        sb.append( "<table style='border-style:none;'>" );
            sb.append( "<tr>" );
                sb.append( "<td>" );   
                    AdminHtmlUtils.renderButtonBasedOnForm( sb , "Create tables" , httpMethodForButtonsBasedOnForms , Config.contextPathForRestService + Config.contextPathForRestAdminService + Config.contextPathForRestAdminDatabaseGeneralService + createTablesPath );
                sb.append( "</td><td>&nbsp;</td><td>" );  
                    AdminHtmlUtils.renderButtonBasedOnForm( sb , "Drop tables" , httpMethodForButtonsBasedOnForms , Config.contextPathForRestService + Config.contextPathForRestAdminService + Config.contextPathForRestAdminDatabaseGeneralService + dropTablesPath );
                sb.append( "</td>" );                
            sb.append( "</tr>" );  
        sb.append( "</table>" );
            
        AdminHtmlUtils.renderButtonBasedOnForm( sb , "Add initial data to tables" , httpMethodForButtonsBasedOnForms , Config.contextPathForRestService + Config.contextPathForRestAdminService + Config.contextPathForRestAdminDatabaseGeneralService + addInitialDataPath );
       
        //sb.append( "<br />" );
        
        AdminHtmlUtils.renderPageBottomForAdmin( sb , AdminService.class.getSimpleName() , Config.contextPathForRestService + Config.contextPathForRestAdminService );
            
        return sb.toString();
    }
    
    // ==============================================
    
    @GET @Path(createDbPath) @Produces( MediaType.TEXT_HTML )
    public String renderCreateDatabase_GET() { return renderCreateDatabase(); }
    
    // ==============================================
    
    @POST @Path(createDbPath) @Produces( MediaType.TEXT_HTML )
    public String renderCreateDatabase_POST() { return renderCreateDatabase(); }
    
    // ==============================================
   
    private String renderCreateDatabase()
    {
        return renderExecutedOperation( new Runnable() { @Override public void run() { DatabaseGeneralOperationsFactory.getNewInstance().createDatabase(); } } );
    }
    
    // ==============================================
    
    @GET @Path(dropDbPath) @Produces( MediaType.TEXT_HTML )
    public String renderDropDatabase_GET() { return renderDropDatabase(); }
    
    // ==============================================
    
    @POST @Path(dropDbPath) @Produces( MediaType.TEXT_HTML )
    public String renderDropDatabase_POST() { return renderDropDatabase(); }
    
    // ==============================================
   
    private String renderDropDatabase()
    {
        return renderExecutedOperation( new Runnable() { @Override public void run() { DatabaseGeneralOperationsFactory.getNewInstance().dropDatabase(); } } );
    }    
    
    // ==============================================
    
    @GET @Path(createTablesPath) @Produces( MediaType.TEXT_HTML )
    public String renderCreateTables_GET() { return renderCreateTables(); }
    
    // ==============================================
    
    @POST @Path(createTablesPath) @Produces( MediaType.TEXT_HTML )
    public String renderCreateTables_POST() { return renderCreateTables(); }
    
    // ==============================================
   
    private String renderCreateTables()
    {
        return renderExecutedOperation( new Runnable() { @Override public void run() { DatabaseGeneralOperationsFactory.getNewInstance().createTables(); } } );
    } 
    
    // ==============================================
    
    @GET @Path(dropTablesPath) @Produces( MediaType.TEXT_HTML )
    public String renderDropTables_GET() { return renderDropTables(); }
    
    // ==============================================
    
    @POST @Path(dropTablesPath) @Produces( MediaType.TEXT_HTML )
    public String renderDropTables_POST() { return renderDropTables(); }
    
    // ==============================================
   
    private String renderDropTables()
    {
        return renderExecutedOperation( new Runnable() { @Override public void run() { DatabaseGeneralOperationsFactory.getNewInstance().dropTables(); } } );
    } 
    
    // ==============================================
    
    @GET @Path(addInitialDataPath) @Produces( MediaType.TEXT_HTML )
    public String renderAddStarterData_GET() { return renderAddStarterData(); }
    
    // ==============================================
    
    @POST @Path(addInitialDataPath) @Produces( MediaType.TEXT_HTML )
    public String renderAddStarterData_POST() { return renderAddStarterData(); }
    
    // ==============================================
   
    private String renderAddStarterData()
    {
        return renderExecutedOperation( new Runnable() { @Override public void run() { DatabaseGeneralOperationsFactory.getNewInstance().addInitialData(); } } );
    } 
    
    // ==============================================
   
    private String renderExecutedOperation( Runnable r )
    {
        StringBuilder sb = new StringBuilder();
        
        AdminHtmlUtils.renderPageTopForAdmin( sb , getClass().getSimpleName() , getClass().getSimpleName() , Config.contextPathForRestService + Config.contextPathForRestAdminService + Config.contextPathForRestAdminDatabaseGeneralService );
            
        try
        {
            r.run();
            sb.append( "OK!" );
        }
        catch( Exception e )
        {
            AdminHtmlUtils.renderException( sb , e );
        }
          
        sb.append( "<br />" );
        
        AdminHtmlUtils.renderPageBottomForAdmin( sb , getClass().getSimpleName() , Config.contextPathForRestService + Config.contextPathForRestAdminService + Config.contextPathForRestAdminDatabaseGeneralService );
            
        return sb.toString();
    }    
    
    // ==============================================
}

// ==================================================