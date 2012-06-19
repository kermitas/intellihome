package as.logserver.servlets;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MainServlet extends HttpServlet
{
    private final String txt;
    
    // ==============================================
    
    public MainServlet( String txt )
    {
        this.txt = txt;
    }
    
    // ==============================================
    
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException
    {
        sendResponse( resp.getWriter() );
    }

    // ==============================================
    
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException
    {
        sendResponse( resp.getWriter() );
    }
    
    // ==============================================
    
    private void sendResponse( PrintWriter out )
    {
        out.println("<html>");
        out.println("<body>");
        out.println("<h1>" + txt + "</h1>");
        out.println("</body>");
        out.println("</html>");
    }
    
    // ==============================================
}
