package as.intellihome.neo4j.objects;

import java.util.List;
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
    
    public static enum DataCollectingLimitExceededAction implements RelationshipType
    {
        DO_NOT_COLLECT , THROW_EXCEPTION , REMOVE_OLDEST
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
        public DataCollectingLimitExceededAction limitExceededAction;
        
        // ============================================
        
        public static DataCollectingType getAppendLimitedByTime( long expirationTime , DataCollectingLimitExceededAction limitExceededAction )
        {

            DataCollectingType result = DataCollectingType.APPEND_LIMITED_BY_TIME;
            
            setLimits( result , expirationTime , limitExceededAction );
            
            return result;
        }
        
        // ============================================
        
        public static DataCollectingType getAppendLimitedByCount( long countLimit , DataCollectingLimitExceededAction limitExceededAction )
        {
            DataCollectingType result = DataCollectingType.APPEND_LIMITED_BY_COUNT;
            
            setLimits( result , countLimit , limitExceededAction );
            
            return result;
        }        
        
        // ================================================
        
        private static void setLimits( DataCollectingType dct , long limit , DataCollectingLimitExceededAction limitExceededAction )
        {
            if( limitExceededAction == null ) throw new IllegalArgumentException( "'limitExceededAction' can not be null" );
            
            dct.limit = limit;
            dct.limitExceededAction = limitExceededAction;
        }
        
        // ================================================
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
    
    public static enum SensorDataLimitExceededAction implements RelationshipType
    {
        DO_NOT_COLLECT , THROW_EXCEPTION , TRIM
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
        public SensorDataLimitExceededAction minLimitExceededAction , maxLimitExceededAction;
         
        // ============================================
        
        public static SensorDataType setMinLimit( SensorDataType sensorDataType , long min , SensorDataLimitExceededAction minLimitExceededAction )
        {
            if( minLimitExceededAction == null ) throw new IllegalArgumentException( "'minLimitExceededAction' can not be null" );
            
            sensorDataType.min = min;
            sensorDataType.minLimitExceededAction = minLimitExceededAction;
           
            return sensorDataType;
        }      
        
        // ============================================
        
        public static SensorDataType setMaxLimit( SensorDataType sensorDataType , long max , SensorDataLimitExceededAction maxLimitExceededAction )
        {
            if( maxLimitExceededAction == null ) throw new IllegalArgumentException( "'maxLimitExceededAction' can not be null" );
            
            sensorDataType.min = max;
            sensorDataType.maxLimitExceededAction = maxLimitExceededAction;
            
            return sensorDataType;
        }   
        
        // ============================================
        
        // it will return improved t, throw exception or return null (if DO_NOT_COLLECT)
        public <T> T validate( T t )
        {
            if( min == null && max == null ) return t;
            
            // TODO here have to write more validators
            
            if( equals( BOOLEAN ) && t instanceof Boolean )
            {
                return t;
            }
            else
            if( equals( BYTE ) && t instanceof Byte )
            {
                Byte b = (Byte)t;
                
                if( min != null && b < min )
                {
                    if( SensorDataLimitExceededAction.DO_NOT_COLLECT.equals( minLimitExceededAction ) )
                        return null;
                    else
                    if( SensorDataLimitExceededAction.THROW_EXCEPTION.equals( minLimitExceededAction ) )
                        throw new RuntimeException( "Value '" + b + "' exceeds min limit '" + min + "'." );
                    else    
                    if( SensorDataLimitExceededAction.TRIM.equals( minLimitExceededAction ) )
                        b = new Byte( min.byteValue() );
                    else   
                        throw new UnsupportedOperationException( "Unknown type '" + minLimitExceededAction + "'." );
                }
                
                if( max != null && b > max )
                {
                    if( SensorDataLimitExceededAction.DO_NOT_COLLECT.equals( maxLimitExceededAction ) )
                        return null;
                    else
                    if( SensorDataLimitExceededAction.THROW_EXCEPTION.equals( maxLimitExceededAction ) )
                        throw new RuntimeException( "Value '" + b + "' exceeds max limit '" + max + "'." );
                    else    
                    if( SensorDataLimitExceededAction.TRIM.equals( maxLimitExceededAction ) )
                        b = new Byte( max.byteValue() );
                    else   
                        throw new UnsupportedOperationException( "Unknown type '" + maxLimitExceededAction + "'." );
                }     
                
                return (T)b;
            }
            else                
                throw new IllegalArgumentException( "Type mismatch, this enum is '" +  name() + "' and data type is " + t.getClass().getName() + "." );
        }
        
        // ============================================
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
    /*
    public interface DataValidator<T>
    {
        public T validate( T t );
    }
    
    // ================================================
    
    public class ListDataValidator<T> implements DataValidator<T>
    {
        public final List< DataValidator<T> > list;

        // ============================================
        
        public ListDataValidator( List< DataValidator<T> > list )
        {
            this.list = list;
        }
        
        // ============================================
        
        @Override
        public T validate( T t )
        {
            for( DataValidator<T> validator : list )
            {
                t = validator.validate( t );
                if( t == null ) return;
            }
            
            return t;
        }
        
        // ============================================
    }  
    
    // ================================================
    
    public class NumberDataValidator<T extends Number > implements DataValidator<T>
    {
        public final T minLimit;
        public final boolean minLimitThrowExceptionOrTrim;
       
        public final T maxLimit;
        public final boolean maxLimitThrowExceptionOrTrim;
        
        // ============================================
        
        public NumberDataValidator( T minLimit , boolean minLimitThrowExceptionOrTrim , T maxLimit , boolean maxLimitThrowExceptionOrTrim )
        {
            this.minLimit = minLimit;
            this.minLimitThrowExceptionOrTrim = minLimitThrowExceptionOrTrim;
            this.maxLimit = maxLimit;
            this.maxLimitThrowExceptionOrTrim = maxLimitThrowExceptionOrTrim;
        }
        
        // ============================================
        
        @Override
        public T validate( T t )
        {
            return null;
        }
        
        // ============================================
    }   */ 
    
    // ================================================
}

// ====================================================