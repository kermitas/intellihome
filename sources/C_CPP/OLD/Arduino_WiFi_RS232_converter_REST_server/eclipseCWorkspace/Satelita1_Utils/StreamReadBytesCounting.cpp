/*
 * StreamReadBytesCounting.cpp
 *
 *  Created on: 10-05-2012
 *      Author: root
 */

// =================================================

#include "StreamReadBytesCounting.h"

// =================================================

StreamReadBytesCounting::StreamReadBytesCounting()
{
	setStream( NULL );
	resetInternalState();
}

// =================================================

void StreamReadBytesCounting::setStream( Stream* _mainStream )
{
	mainStream = _mainStream;
}

// =================================================

void StreamReadBytesCounting::resetInternalState()
{
	readBytesCount = 0;
}

// =================================================

int StreamReadBytesCounting::read()
{
	int readByte = mainStream->read();

	if( readByte == -1 )
		return -1;
	else
	{
		readBytesCount++;
		return readByte;
	}
}

// =================================================

unsigned int StreamReadBytesCounting::getReadBytesCount()
{
	return readBytesCount;
}

// =================================================

int StreamReadBytesCounting::peek()
{
	return mainStream->peek();
}

// =================================================

void StreamReadBytesCounting::flush()
{
	mainStream->flush();
}

// =================================================

size_t StreamReadBytesCounting::write( uint8_t b )
{
	return mainStream->write( b );
}

// =================================================

int StreamReadBytesCounting::available()
{
	return mainStream->available();
}

// =================================================


