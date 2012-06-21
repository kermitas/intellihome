package as.intellihome.neo4j.objects.impl;

import as.intellihome.neo4j.objects.Relations;
import org.neo4j.graphdb.*;

// ====================================================

public class StartupTime extends AbstractNodeContainer implements as.intellihome.neo4j.objects.StartupTime
{
    // ================================================
    
    public StartupTime( Node latestStartupTimeNode )
    {
        super( latestStartupTimeNode );
    }
    
    // ================================================
    
    public static RelationshipType staticGetMainRelationshipType()
    {
        return Relations.StartupTime.LATEST_STARTUP;
    }
    
    // ================================================
        
    @Override
    public RelationshipType getMainRelationshipType()
    {
        return StartupTime.staticGetMainRelationshipType();
    }
        
    // ================================================
    
    @Override
    public void setShutdownTime()
    {
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            node.setProperty( "shutdownTime" , System.currentTimeMillis() );
            
            tx.success();
        }
        finally
        {
            tx.finish();
        }
    }
    
    // ================================================
    
    @Override
    public void delete()
    {
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            Relationship latestStartupRelationship = getRelationTo();

            if( latestStartupRelationship != null )
            {
                Node latestStartupNode = latestStartupRelationship.getEndNode();

                Relationship prevStartupRelationship = latestStartupNode.getSingleRelationship( Relations.StartupTime.PREVIOUS_STARTUP , Direction.INCOMING );

                latestStartupRelationship.delete();
                latestStartupNode.delete();

                while( prevStartupRelationship != null )
                {
                    latestStartupNode = prevStartupRelationship.getStartNode();

                    prevStartupRelationship.delete();

                    prevStartupRelationship = latestStartupNode.getSingleRelationship( Relations.StartupTime.PREVIOUS_STARTUP , Direction.INCOMING );

                    latestStartupNode.delete();
                }
            }
            
            tx.success();
        }
        finally
        {
            tx.finish();
        }
    }
    
    // ================================================
}

// ====================================================