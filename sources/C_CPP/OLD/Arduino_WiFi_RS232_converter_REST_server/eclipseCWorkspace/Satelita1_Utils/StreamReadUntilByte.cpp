/*
 * StreamReadUntilByte.cpp
 *
 *  Created on: 10-05-2012
 *      Author: root
 */

// =================================================

#include "StreamReadUntilByte.h"

// =================================================

StreamReadUntilByte::StreamReadUntilByte( char* _buffer , unsigned char _bufferSize )
{
	buffer = _buffer;
	bufferSize = _bufferSize;

	setStream( NULL );
	resetInternalState( NULL );
}

// =================================================

void StreamReadUntilByte::setStream( Stream* _mainStream )
{
	mainStream = _mainStream;
}

// =================================================

void StreamReadUntilByte::resetInternalState( char* _stopBytes )
{
	stopBytes = _stopBytes;

	for( unsigned char i = 0 ; i < bufferSize ; i++ ) buffer[i] = 0;
	alreadyReadLetterIndex = 0;
	foundByte = 0;
}

// =================================================

int StreamReadUntilByte::read()
{
	if( foundByte != 0 ) return foundByte;

	bool thereWereDataRead = false;

	while( true )
	{
		int readByte = mainStream->read();

		if( readByte == -1 )// break;
		{
			if( thereWereDataRead > 0 )
				return 0;
			else
				return -1;
		}

		thereWereDataRead = true;

		for( unsigned char i = 0 ; stopBytes[i] != 0 ; i++ )
		{
			if( readByte == stopBytes[i] )
			{
				foundByte = readByte;
				//break;
				return foundByte;
			}
		}

		if( foundByte == 0 )
		{
			buffer[ alreadyReadLetterIndex ] = readByte;
			alreadyReadLetterIndex++;
		}
	}

	/*
	if( foundByte != 0 )
	{
		return foundByte;
	}
	else
	if( mainStream->available() == 0 )
	{
		if( thereWereDataRead > 0 )
			return 0;
		else
			return -1;
	}
	else
	{
		return 0;
	}*/
}

// =================================================

int StreamReadUntilByte::peek()
{
	return mainStream->peek();
}

// =================================================

void StreamReadUntilByte::flush()
{
	mainStream->flush();
}

// =================================================

size_t StreamReadUntilByte::write( uint8_t b )
{
	return mainStream->write( b );
}

// =================================================

int StreamReadUntilByte::available()
{
	return mainStream->available();
}

// =================================================
