/*
 * HttpChunkedTransferEncodingStream.cpp
 *
 *  Created on: 08-05-2012
 *      Author: root
 */

// =================================================

#include "HttpChunkedTransferEncodingStream.h"

// =================================================

HttpChunkedTransferEncodingStream::HttpChunkedTransferEncodingStream( uint8_t* _buffer , unsigned char _bufferSize )
{
	buffer = _buffer;
	bufferSize = _bufferSize;
}

// =================================================

size_t HttpChunkedTransferEncodingStream::write( uint8_t b )
{
	buffer[ index ] = b;

	index++;

	if( index == bufferSize ) flush();

	return 1;
}

// =================================================

void HttpChunkedTransferEncodingStream::flush()
{
	if( index > 0 )
	{
		if( index < 16 ) mainStream->write( "0" );
		mainStream->print( index , HEX );
		mainStream->write( "\r\n" );
		mainStream->write( buffer , index );
		mainStream->write( "\r\n" );

		index = 0;
	}
}

// =================================================

void HttpChunkedTransferEncodingStream::resetStream( Stream* _mainStream )
{
	mainStream = _mainStream;
	index = 0;
}

// =================================================

void HttpChunkedTransferEncodingStream::finishChunkedTransmission()
{
	flush();

	mainStream->write( "0\r\n\r\n" );
}

// =================================================

int HttpChunkedTransferEncodingStream::available()
{
	return mainStream->available();
}

// =================================================

int HttpChunkedTransferEncodingStream::read()
{
	return mainStream->read();
}

// =================================================

int HttpChunkedTransferEncodingStream::peek()
{
	return mainStream->peek();
}

// =================================================


