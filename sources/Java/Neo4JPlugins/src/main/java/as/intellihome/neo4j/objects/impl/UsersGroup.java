package as.intellihome.neo4j.objects.impl;

import as.intellihome.neo4j.Config;
import as.intellihome.neo4j.objects.Relations;
import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================

public class UsersGroup extends AbstractNodeContainer implements as.intellihome.neo4j.objects.UsersGroup
{
    // ================================================
    
    private UsersGroup( Node node )
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
    
    public static as.intellihome.neo4j.objects.UsersGroup getOrCreate( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        Relationship mainRelation = getRelationTo( intelliHome );
        
        if( mainRelation == null )
        {
            return create( intelliHome );
        }
        else
        {
            return new UsersGroup( mainRelation.getEndNode() );
        }
    }
    
    // ================================================
    
    private static UsersGroup create( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        Transaction tx = intelliHome.getNode().getGraphDatabase().beginTx();
        try
        {
            Node usersGroupNode = intelliHome.getNode().getGraphDatabase().createNode();

            if( Config.addDescriptionPropertyToNodes ) usersGroupNode.setProperty( "description" , "Singleton node - a grup for all users." );
                
            intelliHome.getNode().createRelationshipTo( usersGroupNode , staticGetMainRelationshipType() );
            
            tx.success();
            
            return new UsersGroup( usersGroupNode );
        }
        finally
        {
            tx.finish();
        }
    }
    
    // ================================================
    
    public static RelationshipType staticGetMainRelationshipType()
    {
        return Relations.UsersGroup.USERS_GROUP;
    }
    
    // ================================================
    
    @Override
    public RelationshipType getMainRelationshipType()
    {
        return UsersGroup.staticGetMainRelationshipType();
    } 
    
    // ================================================
    
    @Override
    public boolean containsUserByLogin( String login )
    {
        Iterator< Relationship > iter = node.getRelationships( Direction.OUTGOING , Relations.UsersGroupContains.CONTAINS_USER ).iterator();
        while( iter.hasNext() ) if( iter.next().getEndNode().getProperty( "login" ).equals( login ) ) return true;

        return false;
    }
    
    // ================================================

    @Override
    public void addUserToGroup( as.intellihome.neo4j.objects.User user )
    {
        if( !user.getNode().hasRelationship( Direction.INCOMING , Relations.UsersGroupContains.CONTAINS_USER ) )
        {
            Transaction tx = node.getGraphDatabase().beginTx();
            try
            {
                node.createRelationshipTo( user.getNode() , Relations.UsersGroupContains.CONTAINS_USER );
                
                tx.success();
            }
            finally
            {
                tx.finish();
            }
        }
    }
    
    // ================================================
    
    @Override
    public User createUser( String login , String password , String name , String description , boolean enabled )
    {
        if( containsUserByLogin( login ) ) throw new RuntimeException( "User '" + login + "' already exists." );
        
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            User user = User.createUser( node.getGraphDatabase() , login , password , name , description , enabled );

            addUserToGroup( user );
            
            tx.success();
            
            return user;
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
            Iterator< Relationship > iter = node.getRelationships( Direction.OUTGOING , Relations.UsersGroupContains.CONTAINS_USER ).iterator();
            while( iter.hasNext() ) new User( iter.next().getEndNode() ).delete();
            
            super.delete();
            
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