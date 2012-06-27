/*
 * InternalEEPROMIdDataOrganisation.cpp
 *
 *  Created on: 10-01-2012
 *      Author: root
 */
/*
#include "InternalEEPROMIdDataOrganisation.h"

InternalEEPROMIdDataOrganisation::InternalEEPROMIdDataOrganisation( InternalEEPROM* _ieeprom )
{
	ieeprom = _ieeprom;

}

InternalEEPROMMemoryMapRecord* InternalEEPROMIdDataOrganisation::getMemoryRecord( uint8_t dataId )
{
	InternalEEPROMMemoryMapRecord* r = ieeprom->read( 0 );

	for( int i = 0 ; r != NULL ; i++ )
	{
		if( r->readByte( 0 ) == dataId )
			return r;
		else
		{
			delete( r );
			r = ieeprom->read( i );
		}
	}

	return NULL;
}

bool InternalEEPROMIdDataOrganisation::contains( uint8_t dataId )
{
	InternalEEPROMMemoryMapRecord* r = getMemoryRecord( dataId );
	bool result = r != NULL;
	delete( r );

	return result;
}

bool InternalEEPROMIdDataOrganisation::remove( uint8_t dataId )
{
	InternalEEPROMMemoryMapRecord* r = getMemoryRecord( dataId );

	if( r == NULL ) return false;

	bool result = ieeprom->remove( r->index );

	delete( r );

	return result;
}

bool InternalEEPROMIdDataOrganisation::write( uint8_t dataId , int dataLength , uint8_t* data )
{
	remove( dataId );

	QueueList<InternalEEPROMDataToWrite*>* queue = new QueueList<InternalEEPROMDataToWrite*>();


	uint8_t* dataOfDataId = (uint8_t*) malloc( sizeof(uint8_t)*1 );
	dataOfDataId[0] = dataId;

	queue->push( new InternalEEPROMDataToWrite( 1 , dataOfDataId ) );
	queue->push( new InternalEEPROMDataToWrite( dataLength , data ) );

	bool result = ieeprom->write( queue );

	while( !queue->isEmpty() ) delete( queue->pop() );

	delete( queue );
	delete( dataOfDataId );

	return result;

}

InternalEEPROMMemoryMapRecord* InternalEEPROMIdDataOrganisation::read( uint8_t dataId )
{
	return getMemoryRecord( dataId );
}


InternalEEPROMIdDataOrganisation::~InternalEEPROMIdDataOrganisation()
{
}
*/

