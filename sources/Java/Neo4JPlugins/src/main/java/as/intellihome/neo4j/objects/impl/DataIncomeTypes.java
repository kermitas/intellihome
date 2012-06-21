package as.intellihome.neo4j.objects.impl;

import as.intellihome.neo4j.Config;
import as.intellihome.neo4j.objects.Relations;
import java.util.Iterator;
import org.neo4j.graphdb.*;

// ====================================================

public class DataIncomeTypes extends AbstractNodeContainer implements as.intellihome.neo4j.objects.DataIncomeTypes
{
    // ================================================
    
    private DataIncomeTypes( Node node )
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
    
    public static as.intellihome.neo4j.objects.DataIncomeTypes getOrCreate( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        Relationship mainRelation = getRelationTo( intelliHome );
        
        if( mainRelation == null )
        {
            return create( intelliHome );
        }
        else
        {
            return new DataIncomeTypes( mainRelation.getEndNode() );
        }
    }
    
    // ================================================
    
    private static DataIncomeTypes create( as.intellihome.neo4j.objects.IntelliHome intelliHome )
    {
        Transaction tx = intelliHome.getNode().getGraphDatabase().beginTx();
        try
        {
            Node dataIncomeTypesNode = intelliHome.getNode().getGraphDatabase().createNode();

            if( Config.addDescriptionPropertyToNodes ) dataIncomeTypesNode.setProperty( "description" , "Singleton node - a grup of data income types like DEVICE_PUSH/SERVER_TCPIP_PULL (for devices)." );
                
            intelliHome.getNode().createRelationshipTo( dataIncomeTypesNode , staticGetMainRelationshipType() );
            
            tx.success();
            
            return new DataIncomeTypes( dataIncomeTypesNode );
        }
        finally
        {
            tx.finish();
        }
    }
    
    // ================================================
    
    public static RelationshipType staticGetMainRelationshipType()
    {
        return Relations.DataIncomeTypes.DATA_INCOME_TYPES;
    }
    
    // ================================================
    
    @Override
    public RelationshipType getMainRelationshipType()
    {
        return DataIncomeTypes.staticGetMainRelationshipType();
    } 
    
    // ================================================

    @Override
    public void setDataIncomeType( as.intellihome.neo4j.objects.Device device , Relations.DataIncomeType dataIncomeType )
    {
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            Iterator< Relationship > iter = device.getNode().getRelationships( Direction.INCOMING , Relations.DataIncomeType.values() ).iterator();
            while( iter.hasNext() ) iter.next().delete();

            Relationship r = node.createRelationshipTo( device.getNode() , dataIncomeType );
            
            if( dataIncomeType.ip != null && dataIncomeType.port != null )
            {
                r.setProperty( "ip" , dataIncomeType.ip );
                r.setProperty( "port" , dataIncomeType.port );
            }
            
            tx.success();
        }
        finally
        {
            tx.finish();
        }         
    }  
    
    /*
    // ================================================

    @Override
    public void setDevicePushDataIncomeType( as.intellihome.neo4j.objects.Device device )
    {
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            Iterator< Relationship > iter = device.getNode().getRelationships( Direction.INCOMING , Relations.DataIncomeType.values() ).iterator();
            while( iter.hasNext() ) iter.next().delete();

            node.createRelationshipTo( device.getNode() , Relations.DataIncomeType.DEVICE_PUSH );
            
            tx.success();
        }
        finally
        {
            tx.finish();
        }         
    }
    
    // ================================================

    @Override
    public void setServerTcpIpPullDataIncomeType( as.intellihome.neo4j.objects.Device device , String ip , int port )
    {
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {
            Iterator< Relationship > iter = device.getNode().getRelationships( Direction.INCOMING , Relations.DataIncomeType.values() ).iterator();
            while( iter.hasNext() ) iter.next().delete();

            Relationship r = node.createRelationshipTo( device.getNode() , Relations.DataIncomeType.SERVER_TCPIP_PULL );
            r.setProperty( "ip" , ip );
            r.setProperty( "port" , port );
            
            tx.success();
        }
        finally
        {
            tx.finish();
        }         
    }    */
    
    // ================================================
}

// ====================================================