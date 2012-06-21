package as.intellihome.neo4j.objects.impl;

import as.intellihome.neo4j.Config;
import as.intellihome.neo4j.objects.Relations;
import org.neo4j.graphdb.*;

// ====================================================

public class IntelliHome extends AbstractNodeContainer implements as.intellihome.neo4j.objects.IntelliHome
{
    // ================================================
    
    private IntelliHome( Node node )
    {
        super( node );
    }
   
    // ================================================
    
    public static Relationship getRelationTo( GraphDatabaseService graphDb )
    {
        return graphDb.getReferenceNode().getSingleRelationship( staticGetMainRelationshipType() , Direction.OUTGOING );
    }   
    
    // ================================================
    
    public static boolean exists( GraphDatabaseService graphDb )
    {
        return graphDb.getReferenceNode().hasRelationship( staticGetMainRelationshipType() , Direction.OUTGOING );
    }   
    
    // ================================================
    
    public static as.intellihome.neo4j.objects.IntelliHome getOrCreate( GraphDatabaseService graphDb )
    {
        Relationship mainRelation = getRelationTo( graphDb );
        
        IntelliHome ih;
        
        if( mainRelation == null )
        {
            ih = create( graphDb );
        }
        else
        {
            ih = new IntelliHome( mainRelation.getEndNode() );
        }
        
        return ih;
    }
    
    // ================================================
    
    private static IntelliHome create( GraphDatabaseService graphDb )
    {
        Transaction tx = graphDb.beginTx();
        try
        {
            Node intelliHomeNode = graphDb.createNode();

            if( Config.addDescriptionPropertyToNodes ) intelliHomeNode.setProperty( "description" , "IntelliHome main node." );
            intelliHomeNode.setProperty( "majorVersion" , Config.interlliHomeMajorVersion );
            intelliHomeNode.setProperty( "minorVersion" , Config.interlliHomeMinorVersion );
                
            graphDb.getReferenceNode().createRelationshipTo( intelliHomeNode , staticGetMainRelationshipType() );
            
            IntelliHome ih = new IntelliHome( intelliHomeNode );
            ih.createStaticNodes();
            
            tx.success();
            
            return ih;
        }
        finally
        {
            tx.finish();
        }
    }
    
    // ================================================
    
    private void createStaticNodes()
    {
        getPysicalityTypes();
        getInSystemLocalizationTypes();
        getDataCollectingTypes();
        getDoorLocalizationTypes();
        getDataIncomeTypes();
        getSensorDataTypes();
        getUserRightsGroup();
        getUsersGroup();
        getDevicesGroup();
        getSensorsGroup();

        // TODO
    }
    
    // ================================================
    
    public static RelationshipType staticGetMainRelationshipType()
    {
        return Relations.IntelliHome.INTELLI_HOME;
    }
    
    // ================================================
    
    @Override
    public RelationshipType getMainRelationshipType()
    {
        return IntelliHome.staticGetMainRelationshipType();
    }    

    // ================================================
    
    @Override
    public as.intellihome.neo4j.objects.PhysicalityTypes getPysicalityTypes()
    {
        return PhysicalityTypes.getOrCreate( this );
    }
    
    // ================================================
    
    @Override
    public as.intellihome.neo4j.objects.DataIncomeTypes getDataIncomeTypes()
    {
        return DataIncomeTypes.getOrCreate( this );
    }    
    
    // ================================================
    
    @Override
    public as.intellihome.neo4j.objects.InSystemLocalizationTypes getInSystemLocalizationTypes()
    {
        return InSystemLocalizationTypes.getOrCreate( this );
    }
    
    // ================================================
    
    @Override
    public as.intellihome.neo4j.objects.DataCollectingTypes getDataCollectingTypes()
    {
        return DataCollectingTypes.getOrCreate( this );
    }
    
    // ================================================
    
    @Override
    public as.intellihome.neo4j.objects.DoorLocalizationTypes getDoorLocalizationTypes()
    {
        return DoorLocalizationTypes.getOrCreate( this );
    }
    
    // ================================================
    
    @Override
    public as.intellihome.neo4j.objects.SensorDataTypes getSensorDataTypes()
    {
        return SensorDataTypes.getOrCreate( this );
    }    
    
    // ================================================
    
    @Override
    public as.intellihome.neo4j.objects.UserRightsGroup getUserRightsGroup()
    {
        return UserRightsGroup.getOrCreate( this );
    } 
    
    // ================================================
    
    @Override
    public as.intellihome.neo4j.objects.UsersGroup getUsersGroup()
    {
        return UsersGroup.getOrCreate( this );
    }  
    
    // ================================================
    
    @Override
    public as.intellihome.neo4j.objects.DevicesGroup getDevicesGroup()
    {
        return DevicesGroup.getOrCreate( this );
    } 
    
    // ================================================
    
    @Override
    public as.intellihome.neo4j.objects.SensorsGroup getSensorsGroup()
    {
        return SensorsGroup.getOrCreate( this );
    } 
   
    // ================================================
    
    @Override
    public as.intellihome.neo4j.objects.StartupTime addNewStartupTime()
    {
        return StartupTimeManager.getManager( this ).addNewStartupTime();
    }
    
    // ================================================
    
    @Override
    public void setShutdownTime()
    {
        as.intellihome.neo4j.objects.StartupTimeManager stm = StartupTimeManager.getManager( this );
        if( stm.containsStartupTime() ) stm.getLatestStartupTime().setShutdownTime();
    }
    
    // ================================================
    
    @Override
    public as.intellihome.neo4j.objects.User createUser( String login , String password , String name , String description , boolean enabled , Relations.UserRight ... userRights )
    {
        Transaction tx = node.getGraphDatabase().beginTx();
        try
        {        
            as.intellihome.neo4j.objects.User user = getUsersGroup().createUser( login , password , name , description , enabled );

            getUserRightsGroup().addRightToUser( user , userRights );
        
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
            as.intellihome.neo4j.objects.StartupTimeManager stm = StartupTimeManager.getManager( this );
            if( stm.containsStartupTime() ) stm.getLatestStartupTime().delete();

            getPysicalityTypes().delete();
            getInSystemLocalizationTypes().delete();
            getDataCollectingTypes().delete();
            getDoorLocalizationTypes().delete();
            getDataIncomeTypes().delete();
            getSensorDataTypes().delete();
            getUserRightsGroup().delete();
            getUsersGroup().delete();
            getDevicesGroup().delete();
            getSensorsGroup().delete();
            
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