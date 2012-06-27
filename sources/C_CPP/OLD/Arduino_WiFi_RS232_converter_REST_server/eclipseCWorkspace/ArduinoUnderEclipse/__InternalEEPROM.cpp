/*
 * InternalEEPROM.cpp
 *
 *  Created on: 10-01-2012
 *      Author: root
 */

/*
#include "InternalEEPROM.h"

InternalEEPROM::InternalEEPROM( unsigned int _maxSize , uint8_t _dataSeparator )
{
	maxSize = _maxSize;
	dataSeparator = _dataSeparator;

	if( isMemoryIsUsedForTheFirstTime() ) formatMemory();
}

bool InternalEEPROM::isMemoryIsUsedForTheFirstTime()
{
	return EEPROM.read( 0 ) != dataSeparator;
}

void InternalEEPROM::formatMemory()
{
	EEPROM.write( 0 , dataSeparator );
	EEPROM.write( 1 , dataSeparator );
}

void InternalEEPROM::clear()
{
	formatMemory();
}

unsigned int InternalEEPROM::getFreeSpace()
{
	unsigned int usedSapce = getUsedSpace();

	if( usedSapce >= maxSize )
		return 0;
	else
		return maxSize - getUsedSpace() - 1;

	//return maxSize - getUsedSpace();
}

unsigned int InternalEEPROM::getUsedSpace()
{
	unsigned int a = getFirstFreeAddress();

	if( a == 0 || a >= maxSize )
		return maxSize;
	else
		return a + 1;

	//return ( a==0 ? maxSize : a + 1 );
}

unsigned int InternalEEPROM::getStoredDatasCount()
{
	unsigned int storedDatasCount = 0;

	uint8_t prevB = EEPROM.read( 0 );

	for( unsigned int i = 1 ; i < maxSize ; i++ )
	{
		uint8_t b = EEPROM.read( i );

		if( b == dataSeparator )
		{
			if( prevB == dataSeparator )
				break;
			else
				storedDatasCount++;
		}

		prevB = b;
	}

	return storedDatasCount;
}

unsigned int InternalEEPROM::getDataAddress( unsigned int index )
{
	for( unsigned int i = 0 ; i < maxSize-1 ; i++ )
	{
		if( EEPROM.read( i ) == dataSeparator )
		{
			if( EEPROM.read( i+1 ) == dataSeparator )
				break;
			else
			{
				if( index == 0 ) return i+1;
				index--;
			}
		}
	}

	return 0;
}

void InternalEEPROM::printMemeory()
{
	uint8_t prevB = EEPROM.read( 0 );

	Serial.print( "[0]" );
	Serial.print( prevB );

	for( unsigned int i = 1 ; i < maxSize ; i++ )
	{
		uint8_t b = EEPROM.read( i );

		Serial.print( " [" );
		Serial.print( i );
		Serial.print( "]" );
		Serial.print( b );

		if( b == dataSeparator && prevB == dataSeparator ) break;

		prevB = b;
	}

	Serial.println( "" );
}

QueueList<InternalEEPROMMemoryMapRecord*>* InternalEEPROM::getMemoryMap()
{
	QueueList<InternalEEPROMMemoryMapRecord*>* queue = new QueueList<InternalEEPROMMemoryMapRecord*>();

	uint8_t prevB = EEPROM.read( 0 );

	unsigned int index = 0;

	for( unsigned int i = 1 ; i < maxSize ; i++ )
	{
		uint8_t b = EEPROM.read( i );

		if( prevB == dataSeparator )
		{
			if( b != dataSeparator )
			{
				unsigned int nearestSeparatorAddress = getNearestSeparatorAddress( i );

				if( nearestSeparatorAddress != 0 )
				{
					queue->push( new InternalEEPROMMemoryMapRecord( index , i , nearestSeparatorAddress - i ) );
					index++;
					i = nearestSeparatorAddress;
					b = dataSeparator;
				}
				else
					break;
			}
			else
				break;
		}

		prevB = b;
	}

	return queue;
}

bool InternalEEPROM::remove( unsigned int index )
{
	InternalEEPROMMemoryMapRecord* r = read( index );

	if( r == NULL ) return false;

	if( EEPROM.read( r->address + r->dataLength + 1 ) == dataSeparator )
	{
		EEPROM.write( r->address , dataSeparator );
	}
	else
	{
		uint8_t prevB = 0;

		for( unsigned int i = r->address ; i < maxSize ; i++ )
		{
			uint8_t b = EEPROM.read( i + r->dataLength + 1 );
			EEPROM.write( i , b );

			if( prevB == dataSeparator && b == dataSeparator ) break;

			prevB = b;
		}
	}

	return true;
}

InternalEEPROMMemoryMapRecord* InternalEEPROM::read( unsigned int index )
{
	//return NULL;

	unsigned int dataSectionAddress = getDataAddress( index );

	if( dataSectionAddress == 0 ) return NULL;

	unsigned int nearestSeparatorAddress = getNearestSeparatorAddress( dataSectionAddress );

	if( nearestSeparatorAddress - dataSectionAddress <= 0 ) return NULL;

	unsigned int dataSize = nearestSeparatorAddress - dataSectionAddress;

	return new InternalEEPROMMemoryMapRecord( index , dataSectionAddress , dataSize );

}

bool InternalEEPROM::checkDataToWrite( unsigned int dataLength , uint8_t* data )
{
	if( dataLength == 0 || data == NULL ) return false;

	for( unsigned int i = 0 ; i < dataLength ; i++ ) if( data[i] == dataSeparator ) return false;

	return true;
}

bool InternalEEPROM::checkFreeSpaceForData( unsigned int firstFreeAddress , unsigned int dataLength )
{
	if( firstFreeAddress == 0 || maxSize - firstFreeAddress < dataLength+2 )
		return false;
	else
		return true;
}

bool InternalEEPROM::write( unsigned int dataLength , uint8_t* data )
{
	QueueList<InternalEEPROMDataToWrite*>* queue = new QueueList<InternalEEPROMDataToWrite*>();

	queue->push( new InternalEEPROMDataToWrite( dataLength , data ) );

	bool result = write( queue );

	while( !queue->isEmpty() ) delete( queue->pop() );
	delete( queue );

	return result;
}

bool InternalEEPROM::write( QueueList<InternalEEPROMDataToWrite*>* queue )
{
	QueueList<InternalEEPROMDataToWrite*>* secondQueue = new QueueList<InternalEEPROMDataToWrite*>();

	unsigned int wholeDataToWriteLength = 0;

	while( !queue->isEmpty() )
	{
		InternalEEPROMDataToWrite* r = queue->pop();

		if( !checkDataToWrite( r->dataLength , r->data ) ) return false;
		wholeDataToWriteLength += r->dataLength;

		secondQueue->push( r );
	}

	unsigned int firstFreeAddress = getFirstFreeAddress();

	if( !checkFreeSpaceForData( firstFreeAddress , wholeDataToWriteLength ) ) return false;

	while( !secondQueue->isEmpty() )
	{
		InternalEEPROMDataToWrite* r = secondQueue->pop();

		for( unsigned int i = 0 ; i < r->dataLength ; i++ )
		{
			EEPROM.write( firstFreeAddress , r->data[i] );
			firstFreeAddress++;
		}

		queue->push( r );
	}

	delete( secondQueue );

	EEPROM.write( firstFreeAddress , dataSeparator );
	EEPROM.write( firstFreeAddress+1 , dataSeparator );

	return true;
}

unsigned int InternalEEPROM::getNearestSeparatorAddress( unsigned int startAddress )
{
	for( unsigned int i = startAddress ; i < maxSize-1 ; i++ )
	{
		if( EEPROM.read( i ) == dataSeparator ) return i;
	}

	return 0;
}

unsigned int InternalEEPROM::getFirstFreeAddress()
{
	for( unsigned int i = 0 ; i < maxSize-3 ; i++ )
	{
		if( EEPROM.read( i ) == dataSeparator && EEPROM.read( i+1 ) == dataSeparator )
		{
			//unsigned int result = i + 1;
			//if( result >=  )
			return i+1;
		}
	}

	return 0;
}

InternalEEPROM::~InternalEEPROM()
{

}

*/
