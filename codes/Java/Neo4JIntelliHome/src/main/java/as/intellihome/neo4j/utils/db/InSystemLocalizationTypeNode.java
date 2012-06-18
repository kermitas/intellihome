package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.Direction;
import org.neo4j.graphdb.Node;
import org.neo4j.graphdb.Relationship;
import org.neo4j.graphdb.RelationshipType;

// ====================================================

enum InSystemLocalizationTypeRelationships implements RelationshipType
{
    HEAD , PASS_THROUGH , END_POINT
}

// ====================================================

public class InSystemLocalizationTypeNode
{
    // ================================================
    
    // creates relation like HEAD , PASS_THROUGH , END_POINT and empty nodes at the end of each relation
    // should be executed under active transaction
    public static void createDefaultData( Node inSystemTypesNode )
    {
        Node headNode = inSystemTypesNode.getGraphDatabase().createNode();
        inSystemTypesNode.createRelationshipTo( headNode , InSystemLocalizationTypeRelationships.HEAD );

        Node passThroughNode = inSystemTypesNode.getGraphDatabase().createNode();
        inSystemTypesNode.createRelationshipTo( passThroughNode , InSystemLocalizationTypeRelationships.PASS_THROUGH ); 
        
        Node endPointNode = inSystemTypesNode.getGraphDatabase().createNode();
        inSystemTypesNode.createRelationshipTo( endPointNode , InSystemLocalizationTypeRelationships.END_POINT );            
    }
    
    // ================================================
    
    // delete main incomming relation and node
    // should be executed under active transaction
    public static void delete( Node inSystemTypeNode )
    {   
        Iterator< Relationship > iter = inSystemTypeNode.getRelationships( Direction.INCOMING , InSystemLocalizationTypeRelationships.values() ).iterator();

        while( iter.hasNext() )
        {
            Relationship r = iter.next();
            //System.out.println( InSystemLocalizationTypeNode.class.getName() + ": deleting relation " + r.getId() );
            r.delete();
        }
        
        //System.out.println( InSystemLocalizationTypeNode.class.getName() + ": deleting node " + inSystemTypeNode.getId() );
        inSystemTypeNode.delete();
    }
    
    // ================================================
}

// ====================================================