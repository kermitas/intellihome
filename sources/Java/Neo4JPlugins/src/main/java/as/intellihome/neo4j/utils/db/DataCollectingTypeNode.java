package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.Direction;
import org.neo4j.graphdb.Node;
import org.neo4j.graphdb.Relationship;
import org.neo4j.graphdb.RelationshipType;

// ====================================================

enum DataCollectingTypeRelationships implements RelationshipType
{
    OVERRIDE , APPEND_UNLIMITED , APPEND_1M , APPEND_2M , APPEND_3M , APPEND_6M , APPEND_12M , APPEND_18M , APPEND_24M
}

// ====================================================

public class DataCollectingTypeNode
{
    // ================================================
    
    // creates relation like OVERRIDE, APPEND and empty nodes at the end of each relation
    // should be executed under active transaction
    public static void createDefaultData( Node dataCollectingTypesNode , boolean addDecriptionProperty )
    {
        Node overrideNode = dataCollectingTypesNode.getGraphDatabase().createNode();
        if( addDecriptionProperty ) overrideNode.setProperty( "description" , "Singleton node - override incomming data." );
        dataCollectingTypesNode.createRelationshipTo( overrideNode , DataCollectingTypeRelationships.OVERRIDE );

        Node appendUnlimitedNode = dataCollectingTypesNode.getGraphDatabase().createNode();
        if( addDecriptionProperty ) appendUnlimitedNode.setProperty( "description" , "Singleton node - append incomming data." );
        dataCollectingTypesNode.createRelationshipTo( appendUnlimitedNode , DataCollectingTypeRelationships.APPEND_UNLIMITED );      
        
        Node append1MNode = dataCollectingTypesNode.getGraphDatabase().createNode();
        if( addDecriptionProperty ) append1MNode.setProperty( "description" , "Singleton node - append incomming data for 1 month." );
        dataCollectingTypesNode.createRelationshipTo( append1MNode , DataCollectingTypeRelationships.APPEND_1M );            
        
        Node append2MNode = dataCollectingTypesNode.getGraphDatabase().createNode();
        if( addDecriptionProperty ) append2MNode.setProperty( "description" , "Singleton node - append incomming data for 2 month." );
        dataCollectingTypesNode.createRelationshipTo( append2MNode , DataCollectingTypeRelationships.APPEND_2M );
        
        Node append3MNode = dataCollectingTypesNode.getGraphDatabase().createNode();
        if( addDecriptionProperty ) append3MNode.setProperty( "description" , "Singleton node - append incomming data for 3 month." );
        dataCollectingTypesNode.createRelationshipTo( append3MNode , DataCollectingTypeRelationships.APPEND_3M );
        
        Node append6MNode = dataCollectingTypesNode.getGraphDatabase().createNode();
        if( addDecriptionProperty ) append6MNode.setProperty( "description" , "Singleton node - append incomming data for 6 month." );
        dataCollectingTypesNode.createRelationshipTo( append6MNode , DataCollectingTypeRelationships.APPEND_6M );
        
        Node append12MNode = dataCollectingTypesNode.getGraphDatabase().createNode();
        if( addDecriptionProperty ) append12MNode.setProperty( "description" , "Singleton node - append incomming data for 12 month." );
        dataCollectingTypesNode.createRelationshipTo( append12MNode , DataCollectingTypeRelationships.APPEND_12M );
        
        Node append18MNode = dataCollectingTypesNode.getGraphDatabase().createNode();
        if( addDecriptionProperty ) append18MNode.setProperty( "description" , "Singleton node - append incomming data for 18 month." );
        dataCollectingTypesNode.createRelationshipTo( append18MNode , DataCollectingTypeRelationships.APPEND_18M );
        
        Node append24MNode = dataCollectingTypesNode.getGraphDatabase().createNode();
        if( addDecriptionProperty ) append24MNode.setProperty( "description" , "Singleton node - append incomming data for 24 month." );
        dataCollectingTypesNode.createRelationshipTo( append24MNode , DataCollectingTypeRelationships.APPEND_24M );        
    }
    
    // ================================================
    
    // delete main incomming relation and node
    // should be executed under active transaction
    public static void delete( Node dataCollectingTypeNode )
    {   
        Iterator< Relationship > iter = dataCollectingTypeNode.getRelationships( Direction.INCOMING , DataCollectingTypeRelationships.values() ).iterator();

        while( iter.hasNext() )
        {
            Relationship r = iter.next();
            r.delete();
        }
        
        dataCollectingTypeNode.delete();
    }
    
    // ================================================
}

// ====================================================