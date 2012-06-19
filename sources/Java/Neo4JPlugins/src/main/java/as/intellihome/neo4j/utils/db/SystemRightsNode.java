package as.intellihome.neo4j.utils.db;

import java.util.Iterator;
import org.neo4j.graphdb.Direction;
import org.neo4j.graphdb.Node;
import org.neo4j.graphdb.Relationship;
import org.neo4j.graphdb.RelationshipType;

// ====================================================

enum SystemRightsRelationships implements RelationshipType
{
    SYSTEM_RIGHTS
}

// ====================================================

public class SystemRightsNode
{
    // ================================================
    
    // creates relation SYSTEM_RIGHTS and empty node (as a group of rights), then creates all outgoing relations and nodes
    // should be executed under active transaction
    public static void createDefaultData( Node intelliHomeNode , boolean addDecriptionProperty )
    {
        Node systemRightsNode = intelliHomeNode.getGraphDatabase().createNode();
        if( addDecriptionProperty ) systemRightsNode.setProperty( "description" , "Singleton node - group of system rights." );
        intelliHomeNode.createRelationshipTo( systemRightsNode , SystemRightsRelationships.SYSTEM_RIGHTS );
        
        SystemRightNode.createDefaultData( systemRightsNode , addDecriptionProperty );
    }
    
    // ================================================
    
    // return SYSTEM_RIGHTS relation (between IntelliHome reference node and system rights node) or null (or throws exception if there is more than one)
    public static Relationship getRelationTo( Node intelliHomeNode )
    {
        return intelliHomeNode.getSingleRelationship( SystemRightsRelationships.SYSTEM_RIGHTS , Direction.OUTGOING );
    }   
    
    // ================================================
    
    // delete main incomming relation, this node, all outgoing relations and it's nodes
    // should be executed under active transaction
    public static void delete( Node intelliHomeNode )
    {   
        Relationship systemRightsReference = getRelationTo( intelliHomeNode );

        if( systemRightsReference != null )
        {
            //System.out.println( SystemRightsNode.class.getName() + ": trying to delete child nodes..." );
            
            Node systemRightsNode = systemRightsReference.getEndNode();

            Iterator< Relationship > iter = systemRightsNode.getRelationships( Direction.OUTGOING , SystemRightRelationships.values() ).iterator();

            while( iter.hasNext() ) SystemRightNode.delete( iter.next().getEndNode() );
            
            //System.out.println( SystemRightsNode.class.getName() + ": deleting node " + systemRightsNode.getId() );
            //System.out.println( SystemRightsNode.class.getName() + ": deleting reference " + systemRightsReference.getId() );
            
            systemRightsReference.delete();
            systemRightsNode.delete();
        }  
        else
        {
            //System.out.println( SystemRightsNode.class.getName() + ": could not find systemRightsReference" );
        }        
    }
    
    // ================================================
}

// ====================================================