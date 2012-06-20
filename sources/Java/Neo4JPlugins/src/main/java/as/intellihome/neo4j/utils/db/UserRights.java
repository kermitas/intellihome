package as.intellihome.neo4j.utils.db;

import org.neo4j.graphdb.RelationshipType;

// ====================================================

public enum UserRights implements RelationshipType
{
    CAN_LOGIN_TO_ADMIN , CAN_CREATE_DEVICE , CAN_CREATE_SENSOR
}

// ====================================================