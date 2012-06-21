package as.intellihome.neo4j.objects.impl;

import as.intellihome.neo4j.objects.Relations;
import org.neo4j.graphdb.Direction;
import org.neo4j.graphdb.Node;
import org.neo4j.graphdb.Relationship;
import org.neo4j.graphdb.Transaction;

// ====================================================

public class StartupTimeManager implements as.intellihome.neo4j.objects.StartupTimeManager
{
    private final Node intelliHomeNode;
    
    // ================================================
    
    private StartupTimeManager( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        intelliHomeNode = intelliHome.getNode();
    }
        
    // ================================================
    
    public static as.intellihome.neo4j.objects.StartupTimeManager getManager( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        return new StartupTimeManager( intelliHome );
    }
    
    // ================================================
    
    public Relationship getRelationToLatestStartupTime()
    {
        return intelliHomeNode.getSingleRelationship( StartupTime.staticGetMainRelationshipType() , Direction.OUTGOING );
    }
    
    // ================================================
    
    @Override
    public as.intellihome.neo4j.objects.StartupTime addNewStartupTime()
    {
        Transaction tx = intelliHomeNode.getGraphDatabase().beginTx();
        try
        {
            Node latestStartupNode = intelliHomeNode.getGraphDatabase().createNode();
            latestStartupNode.setProperty( "startupTime" , System.currentTimeMillis() );
            
            Relationship currentRelationToLatestStartupNode = getRelationToLatestStartupTime();
            
            if( currentRelationToLatestStartupNode != null )
            {
                Node currentLatestStartupNode = currentRelationToLatestStartupNode.getEndNode();
                
                intelliHomeNode.createRelationshipTo( latestStartupNode , StartupTime.staticGetMainRelationshipType() );
                
                currentLatestStartupNode.createRelationshipTo( latestStartupNode , Relations.StartupTime.PREVIOUS_STARTUP );
                
                currentRelationToLatestStartupNode.delete();
            }
            else
            {
                intelliHomeNode.createRelationshipTo( latestStartupNode , StartupTime.staticGetMainRelationshipType() );
            }

            tx.success();
            
            return new StartupTime( latestStartupNode );
        }
        finally
        {
            tx.finish();
        }
    }
    
    // ================================================
    
    @Override
    public boolean containsStartupTime()
    {
        return getRelationToLatestStartupTime() != null;
    }
    
    // ================================================
    
    @Override
    public as.intellihome.neo4j.objects.StartupTime getLatestStartupTime()
    {
        return new StartupTime( getRelationToLatestStartupTime().getEndNode() );
    }          
    
    // ================================================
}

// ====================================================