/*
 * InternalEEPROM.h
 *
 *  Created on: 09-01-2012
 *      Author: root
 */

/*
 #ifndef INTERNALEEPROM_H_
 #define INTERNALEEPROM_H_

 #include <Arduino.h>
 #include <EEPROM.h>
 #include "EEPROMData.h"

 //[id][size][..data..]

 class InternalEEPROM
 {
 public:
 InternalEEPROM( unsigned long _eepromSize );

 bool write( uint8_t id , EEPROMData* data );
 bool remove( uint8_t id );
 bool contains( uint8_t id );
 long readSize( uint8_t id );
 EEPROMData* read( uint8_t id );
 unsigned long getFreeSpace();
 unsigned long getUsedSpace();

 virtual ~InternalEEPROM();

 protected:
 unsigned long eepromSize;

 long findSectionAddress( uint8_t idToFind );
 uint8_t readSectionSize( unsigned long address );
 uint8_t readSectionId( unsigned long address );
 long getFirstFreeAddress();
 };

 class InternalEEPROM {
 public:
 InternalEEPROM();
 virtual ~InternalEEPROM();
 };
 #endif *//* INTERNALEEPROM_H_ */

