/*
 * StreamHttpChunkedTransferEncoding.cpp
 *
 *  Created on: 08-05-2012
 *      Author: root
 */

// =================================================

#include "StreamHttpChunkedTransferEncoding.h"

// =================================================

StreamHttpChunkedTransferEncoding::StreamHttpChunkedTransferEncoding( AnyBuffer< byte , byte >* _buffer , Stream* _underlyingStream )
{
	buffer = _buffer;

	setStream( _underlyingStream );
	resetInternalState();
}

// =================================================

void StreamHttpChunkedTransferEncoding::setStream( Stream* _underlyingStream )
{
	underlyingStream = _underlyingStream;
}

// =================================================

void StreamHttpChunkedTransferEncoding::resetInternalState()
{
	buffer->setPositionAndLimit( 0 , buffer->capacity );
}

// =================================================

size_t StreamHttpChunkedTransferEncoding::write( uint8_t b )
{
	/*
	if( buffer->getRemaining() == 0 )
	{
		flush();
		if( getWriteError() != 0 ) return 0;
	}

	if( buffer->getRemaining() > 0 )
	{
		buffer->array[ buffer->position++ ] = b;

		if( buffer->getRemaining() == 0 ) flush();

		return 1;
	}
	else
	{
		return 0;
	}
	*/

	if( buffer->getRemaining() == 0 ) flush();

	if( buffer->getRemaining() > 0 )
	{
		buffer->array[ buffer->position++ ] = b;
		return 1;
	}
	else
	{
		return 0;
	}
}

// =================================================

size_t StreamHttpChunkedTransferEncoding::write( const uint8_t* buff , size_t size )
{

	//size_t sendBytesCount = 0;
	for( size_t i = 0 ; i < size ; i++ )
	{
		write( buff[i] );
		//sendBytesCount += write( buff[i] );
		//if( send == 0 ) break;
		//sendBytesCount += send;
	}
	return size;


	/*
	if( buffer->getRemaining() == 0 )
	{
		flush();
		if( getWriteError() != 0 ) return 0;
	}

	size_t wroteBytes = 0;

	byte sizeToWrite = 0;

	while( ( sizeToWrite = min( buffer->getRemaining() , size-wroteBytes ) ) > 0 )
	{
		buffer->put( (byte*)(buff+wroteBytes) , sizeToWrite );

		if( buffer->getRemaining() == 0 ) flush();

		wroteBytes += sizeToWrite;
		//return sizeToWrite;
	}
	//else
	//	return 0;

	return wroteBytes;
	*/

	/*
	flush();
	return writeArrayToUnderlyingStream( (uint8_t*)buff , size );
	*/

	/*if( buffer->position > 0 )
	{
		size_t result = writeArrayToUnderlyingStream( buffer->array , buffer->position , (uint8_t*)buff , size );
		buffer->setPosition( 0 );
		return result;
	}
	else
	{
		return writeArrayToUnderlyingStream( (uint8_t*)buff , size );
	}*/

}

//size_t StreamHttpChunkedTransferEncoding::write( const uint8_t* buff , size_t size )
//{
//	size_t bytesToSendCount = size;

//	while( bytesToSendCount > 0 )
//	{
//		size_t countToWrite = min( bytesToSendCount , bufferSize - index );

//		memcpy( buffer+index , buff+(size - bytesToSendCount) , countToWrite );
//		index += countToWrite;

//		if( index == bufferSize )
//		{
//			flush();
//			if( getWriteError() != 0 ) break;
//		}

//		bytesToSendCount -= countToWrite;
//	}

//	return size - bytesToSendCount;
//}

// =================================================

void StreamHttpChunkedTransferEncoding::flush()
{
	if( buffer->position > 0 )
	{
		/*
		underlyingStream->print( buffer->position , HEX );
		underlyingStream->write( "\r\n" );

		buffer->setPositionAndLimit( 0 , buffer->position );

		buffer->writeToStream( underlyingStream );

		buffer->setPositionAndLimit( 0 , buffer->capacity );

		underlyingStream->write( "\r\n" );

		underlyingStream->flush();

		//setWriteError( underlyingStream->getWriteError() );
		*/

		writeArrayToUnderlyingStream( buffer->array , buffer->position );
		underlyingStream->flush();

		buffer->setPosition( 0 );
	}
}

// =================================================

size_t StreamHttpChunkedTransferEncoding::writeArrayToUnderlyingStream( uint8_t* buff , size_t size )
{
	byte wroteBytesCount = underlyingStream->print( size , HEX );
	underlyingStream->write( "\r\n" );
	underlyingStream->write( buff , size );
	underlyingStream->write( "\r\n" );

	return size + 4 + wroteBytesCount;
}

// =================================================
/*
size_t StreamHttpChunkedTransferEncoding::writeArrayToUnderlyingStream( uint8_t* buff1 , size_t size1 , uint8_t* buff2 , size_t size2 )
{
	size_t sizeToWrite = size1 + size2;

	if( sizeToWrite < 256 )
	{
		underlyingStream->print( sizeToWrite , HEX );
		underlyingStream->write( "\r\n" );
		underlyingStream->write( buff1 , size1 );
		underlyingStream->write( buff2 , size2 );
		underlyingStream->write( "\r\n" );

		return sizeToWrite + 4 + ( sizeToWrite < 16 ? 1 : 2 );
	}
	else
	{
		return writeArrayToUnderlyingStream( buff1 , size1 ) + writeArrayToUnderlyingStream( buff2 , size2 );
	}
}*/

// =================================================

void StreamHttpChunkedTransferEncoding::finishChunkedTransmission()
{
	flush();
	underlyingStream->write( "0\r\n\r\n" );
	underlyingStream->flush();

	//write( (const uint8_t*)"0\r\n\r\n" , 5 );

	//setWriteError( underlyingStream->getWriteError() );
}

// =================================================

int StreamHttpChunkedTransferEncoding::getWriteError()
{
	return underlyingStream->getWriteError();
}

// =================================================

void StreamHttpChunkedTransferEncoding::clearWriteError()
{
	underlyingStream->clearWriteError();
}

// =================================================

int StreamHttpChunkedTransferEncoding::available()
{
	return underlyingStream->available();
}

// =================================================

int StreamHttpChunkedTransferEncoding::read()
{
	return underlyingStream->read();
}

// =================================================

int StreamHttpChunkedTransferEncoding::peek()
{
	return underlyingStream->peek();
}

// =================================================

/*
// =================================================

#include "StreamHttpChunkedTransferEncoding.h"

// =================================================

StreamHttpChunkedTransferEncoding::StreamHttpChunkedTransferEncoding( uint8_t* _buffer , unsigned char _bufferSize , Stream* _underlyingStream )
{
	buffer = _buffer;
	bufferSize = _bufferSize;

	setStream( _underlyingStream );
	resetInternalState();
}

// =================================================

void StreamHttpChunkedTransferEncoding::setStream( Stream* _underlyingStream )
{
	underlyingStream = _underlyingStream;
}

// =================================================

void StreamHttpChunkedTransferEncoding::resetInternalState()
{
	index = 0;
}

// =================================================

size_t StreamHttpChunkedTransferEncoding::write( uint8_t b )
{
	buffer[ index ] = b;

	index++;

	if( index == bufferSize )
	{
		flush();

		if( getWriteError() != 0 ) return 0;
	}

	return 1;
}

// =================================================

//size_t StreamHttpChunkedTransferEncoding::write( const uint8_t* buff , size_t size )
//{
//	size_t bytesToSendCount = size;

//	while( bytesToSendCount > 0 )
//	{
//		size_t countToWrite = min( bytesToSendCount , bufferSize - index );

//		memcpy( buffer+index , buff+(size - bytesToSendCount) , countToWrite );
//		index += countToWrite;

//		if( index == bufferSize )
//		{
//			flush();
//			if( getWriteError() != 0 ) break;
//		}

//		bytesToSendCount -= countToWrite;
//	}

//	return size - bytesToSendCount;
//}

// =================================================

void StreamHttpChunkedTransferEncoding::flush()
{
	if( index > 0 )
	{
		int sendBytesCount = 0;

		if( index < 16 ) sendBytesCount += underlyingStream->write( "0" ); // todo to najprawdopodobniej nie potrzebne, wtedy takze sume na dole poprawic, ze czasem 6, a czasem 5

		sendBytesCount += underlyingStream->print( index , HEX );
		sendBytesCount += underlyingStream->write( "\r\n" );
		sendBytesCount += underlyingStream->write( buffer , index );
		sendBytesCount += underlyingStream->write( "\r\n" );

		if( sendBytesCount != 6+index ) setWriteError( -10 );

		underlyingStream->flush();

		setWriteError( underlyingStream->getWriteError() );

		index = 0;
	}
}

// =================================================

void StreamHttpChunkedTransferEncoding::finishChunkedTransmission()
{
	flush();

	if( underlyingStream->write( "0\r\n\r\n" ) != 5 )
	{
		setWriteError( -10 );
	}
	else
	{
		underlyingStream->flush();

		setWriteError( underlyingStream->getWriteError() );
	}
}

// =================================================

int StreamHttpChunkedTransferEncoding::available()
{
	return underlyingStream->available();
}

// =================================================

int StreamHttpChunkedTransferEncoding::read()
{
	return underlyingStream->read();
}

// =================================================

int StreamHttpChunkedTransferEncoding::peek()
{
	return underlyingStream->peek();
}

// =================================================
*/

