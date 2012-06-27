/*
 * InternalEEPROMMemoryMap.cpp
 *
 *  Created on: 10-01-2012
 *      Author: root
 */
/*
#include "InternalEEPROMMemoryMapRecord.h"

InternalEEPROMMemoryMapRecord::InternalEEPROMMemoryMapRecord( unsigned int _index , unsigned int _address , unsigned int _dataLength )
{
	index = _index;
	address = _address;
	dataLength = _dataLength;
}

uint8_t InternalEEPROMMemoryMapRecord::readByte( unsigned int byteIndex )
{
	return EEPROM.read( byteIndex + address );
}

uint8_t* InternalEEPROMMemoryMapRecord::getAllData()
{
	uint8_t* data = (uint8_t*) malloc( sizeof(uint8_t)*dataLength );

	for( unsigned int i = address ; i < address+dataLength; i++ )
	{
		uint8_t b = EEPROM.read( i );
		data[ i - address ] = b;
	}

	return data;
}

InternalEEPROMMemoryMapRecord::~InternalEEPROMMemoryMapRecord()
{

}
*/
