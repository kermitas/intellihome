package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.Direction;
import org.neo4j.graphdb.Node;
import org.neo4j.graphdb.Relationship;
import org.neo4j.graphdb.RelationshipType;

// ====================================================

enum DataIncomeTypesRelationships implements RelationshipType
{
    DATA_INCOME_TYPES
}

// ====================================================

public class DataIncomeTypesNode
{
    // ================================================
    
    // creates relation DATA_COLLECTING_TYPES and empty node (as a group of phisicality types), then creates all outgoing relations and nodes
    // should be executed under active transaction
    public static void createDefaultData( Node intelliHomeNode , boolean addDecriptionProperty )
    {
        Node dataIncomeTypesNode = intelliHomeNode.getGraphDatabase().createNode();
        if( addDecriptionProperty ) dataIncomeTypesNode.setProperty( "description" , "Singleton node - group of data income types (like deivce-push or server-pull)." );
        intelliHomeNode.createRelationshipTo( dataIncomeTypesNode , DataIncomeTypesRelationships.DATA_INCOME_TYPES );
        
        DataIncomeTypeNode.createDefaultData( dataIncomeTypesNode , addDecriptionProperty );
    }
    
    // ================================================
    
    // return DATA_COLLECTING_TYPES relation (outgoing form IntelliHome) or null (or throws exception if there is more than one)
    public static Relationship getRelationTo( Node intelliHomeNode )
    {
        return intelliHomeNode.getSingleRelationship( DataIncomeTypesRelationships.DATA_INCOME_TYPES , Direction.OUTGOING );
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

            Iterator< Relationship > iter = dataCollectingTypesNode.getRelationships( Direction.OUTGOING , DataIncomeTypeRelationships.values() ).iterator();

            while( iter.hasNext() ) DataIncomeTypeNode.delete( iter.next().getEndNode() );
         
            dataCollectingTypesReference.delete();
            dataCollectingTypesNode.delete();
        }  
    }
    
    // ================================================
}

// ====================================================