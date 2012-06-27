/*
 * InternalEEPROM.cpp
 *
 *  Created on: 09-01-2012
 *      Author: root
 */

/*
 #include "InternalEEPROM.h"

 InternalEEPROM::InternalEEPROM( unsigned long _eepromSize )
 {
 eepromSize = _eepromSize;
 }

 bool InternalEEPROM::write( uint8_t id , EEPROMData* data )
 {
 if( data == NULL ) return false;

 if( getFreeSpace() + readSize( id ) ) return false;

 remove( id );

 long a = getFirstFreeAddress();

 if( a == -1 ) return false;

 EEPROM.write( a , id );
 a++;
 EEPROM.write( a , data->size );
 a++;

 for( uint8_t i = 0 ; i < data->size ; i++ ) EEPROM.write( a + i , data->data[i] );

 return true;
 }

 long InternalEEPROM::getFirstFreeAddress()
 {
 return getUsedSpace();
 }

 bool InternalEEPROM::remove( uint8_t id )
 {
 unsigned long a = findSectionAddress( id );

 if( a == -1 ) return false;

 // remove...

 return true;
 }

 bool InternalEEPROM::contains( uint8_t id )
 {
 return findSectionAddress( id ) != -1;
 }

 long InternalEEPROM::readSize( uint8_t id )
 {
 unsigned long a = findSectionAddress( id );

 if( a == -1 ) return -1;

 return readSectionSize( a );
 }

 EEPROMData* InternalEEPROM::read( uint8_t id )
 {
 unsigned long a = findSectionAddress( id );

 if( a == -1 ) return NULL;

 uint8_t size = readSectionSize( a );

 char* data = new char[size];

 for( uint8_t i = 0 ; i < size ; i++ ) data[i] = EEPROM.read( a + i );

 return new EEPROMData( size , data , true );
 }

 unsigned long InternalEEPROM::getFreeSpace()
 {
 return eepromSize - getUsedSpace();
 }

 unsigned long InternalEEPROM::getUsedSpace()
 {
 unsigned long a = 0;

 while( true )
 {
 uint8_t id = readSectionId( a );

 if( id >= 255 )
 break;
 else
 {
 a++;

 if( a >= eepromSize ) break;

 uint8_t size = readSectionSize( a );

 a = 1 + size;

 if( a >= eepromSize ) break;
 }
 }

 return a;
 }

 long InternalEEPROM::findSectionAddress( uint8_t idToFind )
 {
 if( idToFind >= 255 ) return -1;

 unsigned long a = 0;

 while( true )
 {
 uint8_t id = readSectionId( a );

 if( id >= 255 )
 return -1;
 else
 {
 if( id == idToFind ) return a;

 a++;

 if( a >= eepromSize ) return -1;

 uint8_t size = readSectionSize( a );

 a = 1 + size;

 if( a >= eepromSize ) return -1;
 }
 }

 return -1;
 }

 uint8_t InternalEEPROM::readSectionSize( unsigned long address )
 {
 return EEPROM.read( address );
 }

 uint8_t InternalEEPROM::readSectionId( unsigned long address )
 {
 return EEPROM.read( address );
 }

 InternalEEPROM::~InternalEEPROM()
 {

 }

 */
