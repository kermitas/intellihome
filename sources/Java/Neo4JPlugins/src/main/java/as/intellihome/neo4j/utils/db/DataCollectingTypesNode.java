package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.Direction;
import org.neo4j.graphdb.Node;
import org.neo4j.graphdb.Relationship;
import org.neo4j.graphdb.RelationshipType;

// ====================================================

enum DataCollectingTypesRelationships implements RelationshipType
{
    DATA_COLLECTING_TYPES
}

// ====================================================

public class DataCollectingTypesNode
{
    // ================================================
    
    // creates relation DATA_COLLECTING_TYPES and empty node (as a group of phisicality types), then creates all outgoing relations and nodes
    // should be executed under active transaction
    public static void createDefaultData( Node intelliHomeNode , boolean addDecriptionProperty )
    {
        Node dataCollectingTypesNode = intelliHomeNode.getGraphDatabase().createNode();
        if( addDecriptionProperty ) dataCollectingTypesNode.setProperty( "description" , "This is a singleton node - group of data collecting types." );
        intelliHomeNode.createRelationshipTo( dataCollectingTypesNode , DataCollectingTypesRelationships.DATA_COLLECTING_TYPES );
        
        DataCollectingTypeNode.createDefaultData( dataCollectingTypesNode , addDecriptionProperty );
    }
    
    // ================================================
    
    // return DATA_COLLECTING_TYPES relation (outgoing form IntelliHome) or null (or throws exception if there is more than one)
    public static Relationship getRelationTo( Node intelliHomeNode )
    {
        return intelliHomeNode.getSingleRelationship( DataCollectingTypesRelationships.DATA_COLLECTING_TYPES , Direction.OUTGOING );
    }   
    
    // ================================================
    
    // delete main incomming relation, this node, all outgoing relations and it's nodes
    // should be executed under active transaction
    public static void delete( Node intelliHomeNode )
    {   
        Relationship dataCollectingTypesReference = getRelationTo( intelliHomeNode );

        if( dataCollectingTypesReference != null )
        {
            Node dataCollectingTypesNode = dataCollectingTypesReference.getEndNode();

            Iterator< Relationship > iter = dataCollectingTypesNode.getRelationships( Direction.OUTGOING , DataCollectingTypeRelationships.values() ).iterator();

            while( iter.hasNext() ) DataCollectingTypeNode.delete( iter.next().getEndNode() );
         
            dataCollectingTypesReference.delete();
            dataCollectingTypesNode.delete();
        }  
    }
    
    // ================================================
}

// ====================================================