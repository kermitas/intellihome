package as.intellihome.neo4j.objects.impl;

import as.intellihome.neo4j.objects.Relations;
import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================

public class User extends AbstractNodeContainer implements as.intellihome.neo4j.objects.User
{
    // ================================================
    
    public User( Node node )
    {
        super( node );
    }
   
    // ================================================
    
    public static User createUser( GraphDatabaseService graphDb , String login , String password , String name , String description , boolean enabled )
    {
        Transaction tx = graphDb.beginTx();
        try
        {
            Node userNode = graphDb.createNode();

            userNode.setProperty( "login" , login );
            userNode.setProperty( "password" , password );
            userNode.setProperty( "name" , name );
            userNode.setProperty( "description" , description );
            userNode.setProperty( "enabled" , enabled );
            userNode.setProperty( "creationTime" , System.currentTimeMillis() );
                
            tx.success();
            
            return new User( userNode );
        }
        finally
        {
            tx.finish();
        }
    }
    
    // ================================================
    
    public static RelationshipType staticGetMainRelationshipType()
    {
        return Relations.UsersGroupContains.CONTAINS_USER;
    }
    
    // ================================================
    
    @Override
    public RelationshipType getMainRelationshipType()
    {
        return User.staticGetMainRelationshipType();
    } 
    
    // ================================================
    
    @Override
    public void delete()
    {
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            Iterator< Relationship > iter = node.getRelationships( Direction.OUTGOING , Relations.UserContains.USER_CONTAINS_DEVICE ).iterator();
            while( iter.hasNext() ) new Device( iter.next().getEndNode() ).delete();
            
            iter = node.getRelationships( Direction.INCOMING , Relations.UserRight.values() ).iterator();
            while( iter.hasNext() ) iter.next().delete();
            
            super.delete();
            
            tx.success();
        }
        finally
        {
            tx.finish();
        }        
    }
    
    // ================================================
    
    @Override 
    public Device createDevice( String name , String description , boolean enabled , as.intellihome.neo4j.objects.Relations.PhysicalityType physicalityType , as.intellihome.neo4j.objects.Relations.DataIncomeType dataIncomeType , as.intellihome.neo4j.objects.Relations.InSystemLocalizationType inSystemLocalizationType , String locationName , String locationDescription , double locationX , double locationY , double locationZ )
    {
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            Device device = Device.createDevice( node.getGraphDatabase() , name , description , enabled , physicalityType , dataIncomeType , inSystemLocalizationType , locationName , locationDescription , locationX , locationY , locationZ );
            
            as.intellihome.neo4j.objects.IntelliHome ih = as.intellihome.neo4j.objects.impl.IntelliHome.getOrCreate( node.getGraphDatabase() );
            
            DevicesGroup.getOrCreate( ih ).addDeviceToGroup( device );
            
            node.createRelationshipTo( device.getNode() , Relations.UserContains.USER_CONTAINS_DEVICE );
            
            LocationManager.get( node.getGraphDatabase() ).setLocation( device , locationName, locationDescription, locationX , locationY , locationZ );
            
            PhysicalityTypes.getOrCreate( ih ).setPhysicalityType( device , physicalityType );
            
            InSystemLocalizationTypes.getOrCreate( ih ).setInSystemLocalizationType( device , inSystemLocalizationType );
            
            DataIncomeTypes.getOrCreate( ih ).setDataIncomeType( device , dataIncomeType );
            
            /*
            if( as.intellihome.neo4j.objects.Relations.DataIncomeType.DEVICE_PUSH.equals( dataIncomeType ) )
            {
                DataIncomeTypes.getOrCreate( ih ).setDevicePushDataIncomeType( device );
            }
            else
            {
                // TODO we have to pass here ip and port for SERVER_TCPIP_PULL type
                throw new UnsupportedOperationException( "DataIncomeType '" + dataIncomeType.name() + "' is not supported yet." );
            }   */         
            
            tx.success();
            
            return device;
        }
        finally
        {
            tx.finish();
        } 
    }
    
    // ================================================
}

// ====================================================