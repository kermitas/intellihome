package as.intellihome.neo4j.objects.impl;

import as.intellihome.neo4j.Config;
import as.intellihome.neo4j.objects.Relations;
import org.neo4j.graphdb.*;

// ====================================================

public class UserRightsGroup extends AbstractNodeContainer implements as.intellihome.neo4j.objects.UserRightsGroup
{
    // ================================================
    
    private UserRightsGroup( Node node )
    {
        super( node );
    }
   
    // ================================================
    
    public static Relationship getRelationTo( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        return intelliHome.getNode().getSingleRelationship( staticGetMainRelationshipType() , Direction.OUTGOING );
    }   
    
    // ================================================
    
    public static boolean exists( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        return intelliHome.getNode().hasRelationship( staticGetMainRelationshipType() , Direction.OUTGOING );
    }   
    
    // ================================================
    
    public static as.intellihome.neo4j.objects.UserRightsGroup getOrCreate( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        Relationship mainRelation = getRelationTo( intelliHome );
        
        if( mainRelation == null )
        {
            return create( intelliHome );
        }
        else
        {
            return new UserRightsGroup( mainRelation.getEndNode() );
        }
    }
    
    // ================================================
    
    private static UserRightsGroup create( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        Transaction tx = intelliHome.getNode().getGraphDatabase().beginTx();
        try
        {
            Node userRightsGroupNode = intelliHome.getNode().getGraphDatabase().createNode();

            if( Config.addDescriptionPropertyToNodes ) userRightsGroupNode.setProperty( "description" , "Singleton node - a grup for all user's rights like CAN_LOGIN_TO_ADMIN, CAN_CREATE_DEVICE." );
                
            intelliHome.getNode().createRelationshipTo( userRightsGroupNode , staticGetMainRelationshipType() );
            
            tx.success();
            
            return new UserRightsGroup( userRightsGroupNode );
        }
        finally
        {
            tx.finish();
        }
    }
    
    // ================================================
    
    public static RelationshipType staticGetMainRelationshipType()
    {
        return Relations.UserRightsGroup.USER_RIGHTS_GROUP;
    }
    
    // ================================================
    
    @Override
    public RelationshipType getMainRelationshipType()
    {
        return UserRightsGroup.staticGetMainRelationshipType();
    } 
    
    // ================================================

    @Override
    public void addRightToUser( as.intellihome.neo4j.objects.User user , Relations.UserRight userRight )
    {
        addRightsToUser( user , userRight );              
    }
    
    // ================================================

    @Override
    public void addRightToUser( as.intellihome.neo4j.objects.User user , Relations.UserRight ... userRights )
    {   
        addRightsToUser( user , userRights );        
    }   
    
    // ================================================

    private void addRightsToUser( as.intellihome.neo4j.objects.User user , Relations.UserRight ... userRights )
    {   
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            for( Relations.UserRight userRight : userRights )
            {
                if( !user.getNode().hasRelationship( Direction.INCOMING , userRight ) )
                {
                    node.createRelationshipTo( user.getNode() , userRight );
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