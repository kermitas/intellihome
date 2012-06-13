package as.logserver;

import as.logserver.servlets.MainServlet;
import com.sun.jersey.api.core.PackagesResourceConfig;
import com.sun.jersey.api.json.JSONConfiguration;
import org.eclipse.jetty.server.Connector;
import org.eclipse.jetty.server.Handler;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.handler.ContextHandlerCollection;
import org.eclipse.jetty.server.nio.SelectChannelConnector;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;
import org.eclipse.jetty.util.thread.QueuedThreadPool;

public class Main
{
    
    public static void main(String[] args) throws Exception
    {
        // -----
        
        Server server = new Server();
        
        server.setGracefulShutdown(Config.gracefulShutdownTimeInMs);
        server.setStopAtShutdown(true);
        
        // -----
        
        QueuedThreadPool threadPool = new QueuedThreadPool();
        threadPool.setMaxThreads(Config.threadsCountInThreadPool);
        server.setThreadPool(threadPool);
        
        // -----
        
        Connector connector = new SelectChannelConnector();
        //connector.setHost(Config.host);
        connector.setPort(Config.port);
        connector.setMaxIdleTime(Config.connectionMaxIdleTimeInMs);
        server.setConnectors(new Connector[]{connector});

        // -----
        
        ServletContextHandler context0 = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context0.setContextPath(Config.contextPathForMainServlet);
        context0.addServlet(new ServletHolder(new MainServlet("Welcome from main servlet!")),"/*");
 
        // -----
        
        ServletContextHandler context1 = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context1.setContextPath(Config.contextPathForRestService);
        
        com.sun.jersey.spi.container.servlet.ServletContainer jerseyServletContainter = new com.sun.jersey.spi.container.servlet.ServletContainer();
        
        
        ServletHolder sh = new ServletHolder( jerseyServletContainter );
        //sh.setInitParameter("com.sun.jersey.config.property.resourceConfigClass", "com.sun.jersey.api.core.PackagesResourceConfig");
        sh.setInitParameter(JSONConfiguration.FEATURE_POJO_MAPPING, "true");
        sh.setInitParameter(PackagesResourceConfig.PROPERTY_PACKAGES, Config.packageWithRestResources);
        //context1.addServlet(new ServletHolder(new ServletContainer(new PackagesResourceConfig("com.sun.jersey.samples.helloworld"))), "/");
        context1.addServlet(sh,"/*");
 
        // -----
        
        ContextHandlerCollection contexts = new ContextHandlerCollection();
        contexts.setHandlers(new Handler[] { context0 , context1 });
 
        server.setHandler(contexts);
        
        server.start();
        server.join(); 
        
        /*
        String webappDirLocation = "src/main/webapp/";
        
        //The port that we should run on can be set into an environment variable
        //Look for that variable and default to 8080 if it isn't there.
        String webPort = System.getenv("PORT");
        if(webPort == null || webPort.isEmpty()) {
            webPort = "8080";
        }

        Server server = new Server(Integer.valueOf(webPort));
        WebAppContext root = new WebAppContext();

        root.setContextPath("/");
        root.setDescriptor(webappDirLocation+"/WEB-INF/web.xml");
        root.setResourceBase(webappDirLocation);
        
        //Parent loader priority is a class loader setting that Jetty accepts.
        //By default Jetty will behave like most web containers in that it will
        //allow your application to replace non-server libraries that are part of the
        //container. Setting parent loader priority to true changes this behavior.
        //Read more here: http://wiki.eclipse.org/Jetty/Reference/Jetty_Classloading
        root.setParentLoaderPriority(true);
        
        server.setHandler(root);
        
        server.start();
        server.join();   
        */
    }

}
