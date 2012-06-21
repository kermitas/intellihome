package as.intellihome.neo4j.objects;

import org.neo4j.graphdb.RelationshipType;

// ====================================================

public class Relations
{
    // ================================================
    
    public static enum IntelliHome implements RelationshipType
    {
        INTELLI_HOME
    }
    
    // ================================================
    
    public static enum StartupTime implements RelationshipType
    {
        LATEST_STARTUP , PREVIOUS_STARTUP
    }    
    
    // ================================================
    
    public static enum PhysicalityTypes implements RelationshipType
    {
        PHYSICALITY_TYPES
    }  
    
    // ================================================
    
    public static enum PhysicalityType implements RelationshipType
    {
        REAL , VIRTUAL
    }
    
    // ================================================
    
    public static enum InSystemLocalizationTypes implements RelationshipType
    {
        IN_SYSTEM_LOCALIZATION_TYPES
    }    
    
    // ================================================
    
    public static enum InSystemLocalizationType implements RelationshipType
    {
        HEAD , PASS_THROUGH , END_POINT
    }    
    
    // ================================================
    
    public static enum DataCollectingTypes implements RelationshipType
    {
        DATA_COLLECTING_TYPES
    } 
    
    // ================================================
    
    public static enum DataCollectingType implements RelationshipType
    {
        OVERRIDE , APPEND_UNLIMITED , APPEND_LIMITED_BY_TIME , APPEND_LIMITED_BY_COUNT;
        
        // limit is just for APPEND_LIMITED_BY_TIME or APPEND_LIMITED_BY_COUNT
        public Long limit;
        
        DataCollectingType() {}
        DataCollectingType( long limit ) { this.limit = limit; } 
    }    
    
    // ================================================
    
    public static enum DoorLocalizationTypes implements RelationshipType
    {
        DOOR_LOCALIZATION_TYPES
    }
    
    // ================================================
    
    public static enum DoorLocalizationType implements RelationshipType
    {
        INDOOR , OUTDOOR
    }    
    
    // ================================================
    
    public static enum DataIncomeTypes implements RelationshipType
    {
        DATA_INCOME_TYPES
    }
    
    // ================================================
    
    public static enum DataIncomeType implements RelationshipType
    {
        DEVICE_PUSH , SERVER_TCPIP_PULL;
        
        // ip and port is just for SERVER_TCPIP_PULL
        public String ip;
        public Integer port;
        
        DataIncomeType() {}
        DataIncomeType( String ip , int port ) { this.ip = ip; this.port = port; }         
    }    
    
    // ================================================
    
    public static enum SensorDataTypes implements RelationshipType
    {
        SENSOR_DATA_TYPES
    }
    
    // ================================================
    
    public static enum SensorDataType implements RelationshipType
    {
        BOOLEAN , BYTE , SHORT , CHAR , INTEGER , LONG , FLOAT , DOUBLE , STRING;
        
        // limits: for string min & max length, for number min & max value
        // if null that means there is no min and/or max limit
        public Long min , max;
        
        SensorDataType() {}
        SensorDataType( long min , long max ) { this.min = min; this.max = max; }         
    }  
    
    // ================================================
    
    public static enum UserRightsGroup implements RelationshipType
    {
        USER_RIGHTS_GROUP
    } 
    
    // ================================================
    
    public static enum UserRight implements RelationshipType
    {
        CAN_LOGIN_TO_ADMIN , CAN_CREATE_DEVICE , CAN_CREATE_SENSOR
    }  
    
    // ================================================
    
    public static enum UsersGroup implements RelationshipType
    {
        USERS_GROUP
    }   
    
    // ================================================
    
    public static enum UsersGroupContains implements RelationshipType
    {
        CONTAINS_USER
    }  
    
    // ================================================
    
    public static enum DevicesGroup implements RelationshipType
    {
        DEVICES_GROUP
    }   
    
    // ================================================
    
    public static enum DevicesGroupContains implements RelationshipType
    {
        CONTAINS_DEVICE
    }   
    
    // ================================================
    
    public static enum SensorsGroup implements RelationshipType
    {
        SENSORS_GROUP
    }   
    
    // ================================================
    
    public static enum SensorsGroupContains implements RelationshipType
    {
        CONTAINS_SENSOR
    }  
    
    // ================================================
    
    public static enum UserContains implements RelationshipType
    {
        USER_CONTAINS_DEVICE
    }
    
    // ================================================
    
    public static enum DeviceContains implements RelationshipType
    {
        DEVICE_CONTAINS_SENSOR
    } 
    
    // ================================================
    
    public static enum Location implements RelationshipType
    {
        HAS_LOCATION
    }     
    
    // ================================================
    
    public static enum SensorSample implements RelationshipType
    {
        LATEST_SAMPLE , PREVIOUS_SAMPLE
    }     
    
    // ================================================
}

// ====================================================