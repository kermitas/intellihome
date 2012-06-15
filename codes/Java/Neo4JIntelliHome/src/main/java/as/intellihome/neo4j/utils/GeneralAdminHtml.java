package as.intellihome.neo4j.utils;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

// ====================================================

public class GeneralAdminHtml
{
    // ================================================

    public static void renderButtonBasedOnForm( StringBuilder sb , String text , String formMethod , String formPath )
    {
        sb.append( "<form method='").append( formMethod ).append("' action='").append( formPath ).append("'>" );
            sb.append( "<input type='submit' value='").append( text ).append("'>" );
        sb.append( "</form>" );    
    }
    
    // ================================================
    
    public static void renderPageTop( StringBuilder sb , String localization , String goBackDescription , String pathForBackButton )
    {
        sb.append( "<html>" );
            sb.append( "<body>" );        
                sb.append( "<h2><i>Welcome to " ).append( localization ).append( ".</i></h2>" );
       
                renderLinkToGoBack( sb , goBackDescription , pathForBackButton );
                
                sb.append( "<hr />" );     
    }

    // ================================================
    
    public static void renderPageBottom( StringBuilder sb , String goBackDescription , String pathForBackButton )
    {            
                sb.append( "<hr />" );

                renderLinkToGoBack( sb , goBackDescription , pathForBackButton );
                
                sb.append( "<table style='border-style:none; width:100%;'>" );
                    sb.append( "<tr><td style='width:100%; text-align:right;'>" );
                        sb.append( "<font style='font-size:smaller;font-family: Verdana, Arial, Helvetica, sans-serif;'>" );
                            sb.append( "Server time: " ).append( new java.sql.Timestamp( System.currentTimeMillis() ) ).append( " (" ).append( System.currentTimeMillis() ).append( " ms)");
                            sb.append( "<br /><b>Artur Stanek 2012</b>" );
                        sb.append( "</font>" );
                    sb.append( "</td></tr>" );
                sb.append( "</table>" );
        
            sb.append( "</body>" );
        sb.append( "</html>" );        
    }
    
    // ================================================
    
    public static void renderLinkToGoBack( StringBuilder sb , String goBackDescription , String pathForBackButton )
    { 
        if( pathForBackButton != null && !pathForBackButton.isEmpty() && goBackDescription != null && !goBackDescription.isEmpty() ) sb.append( "<a href='" ).append( pathForBackButton ).append( "'><font style='font-size:smaller;font-family: Verdana, Arial, Helvetica, sans-serif;'>Go to ").append(goBackDescription).append(" page.</font></a>" );
    }   
    
    // ================================================
    
    public static void renderException( StringBuilder sb , Exception e )
    { 
        sb.append( "Catched exception: <b>" ).append( e ).append( "</b>.<br /><pre>" );
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        PrintStream ps = new PrintStream( bos );
        e.printStackTrace( ps );
        ps.close();

        sb.append( bos.toString() ).append("</pre>");
    }  
    
    // ================================================
}

// ====================================================