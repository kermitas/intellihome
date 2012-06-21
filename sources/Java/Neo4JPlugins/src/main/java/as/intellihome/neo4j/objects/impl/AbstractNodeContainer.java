package as.intellihome.neo4j.objects.impl;

import org.neo4j.graphdb.*;

// ====================================================

public abstract class AbstractNodeContainer implements as.intellihome.neo4j.objects.NodeContainer
{
    protected final Node node;
    
    // ================================================
    
    public AbstractNodeContainer( Node node )
    {
        this.node = node;
    }
   
    // ================================================
    
    @Override
    public Relationship getRelationTo()
    {
        return node.getSingleRelationship( getMainRelationshipType() , Direction.INCOMING );
    }

    // ================================================
    
    public abstract RelationshipType getMainRelationshipType();
    
    // ================================================
    
    @Override
    public void delete()
    {
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            getRelationTo().delete();
            node.delete();
            
            tx.success();
        }
        finally
        {
            tx.finish();
        }        
    }
    
    // ================================================

    @Override
    public Node getNode() { return node; }
    
    // ================================================
}

// ====================================================