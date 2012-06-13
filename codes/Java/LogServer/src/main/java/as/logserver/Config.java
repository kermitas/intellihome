package as.logserver;

public class Config
{
    public static final String host = "localhost";
    public static final int port = 8080;
    public static final int connectionMaxIdleTimeInMs = 30*1000;
    public static final int gracefulShutdownTimeInMs = 2*1000;
    public static final int threadsCountInThreadPool = 3;

    public static final String packageWithRestResources = as.logserver.rest.resources.AdminService.class.getPackage().getName();
        
    public static final String contextPathForMainServlet = "/";
    public static final String contextPathForRestService = "/rest";
    public static final String contextPathForRestAdminService = "/admin";
    public static final String contextPathForRestAdminDatabaseGeneralService = "/databasegeneral";
}
 