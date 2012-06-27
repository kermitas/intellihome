/*
 * InternalEEPROMMemoryMap.h
 *
 *  Created on: 10-01-2012
 *      Author: root
 */
/*
#ifndef INTERNALEEPROMMEMORYMAPRECORD_H_
#define INTERNALEEPROMMEMORYMAPRECORD_H_

#include <Arduino.h>
#include <EEPROM.h>

class InternalEEPROMMemoryMapRecord
{
	public:
		unsigned int index;
		unsigned int address;
		unsigned int dataLength;

		InternalEEPROMMemoryMapRecord( unsigned int _index , unsigned int _address , unsigned int _dataLength );
		virtual ~InternalEEPROMMemoryMapRecord();

		uint8_t readByte( unsigned int byteIndex );
		uint8_t* getAllData();
};

#endif*/ /* INTERNALEEPROMMEMORYMAPRECORD_H_ */
