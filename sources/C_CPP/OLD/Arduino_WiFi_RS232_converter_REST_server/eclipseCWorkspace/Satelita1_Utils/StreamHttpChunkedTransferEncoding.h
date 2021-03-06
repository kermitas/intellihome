/*
 * StreamHttpChunkedTransferEncoding.h
 *
 *  Created on: 08-05-2012
 *      Author: root
 */

#ifndef StreamHttpChunkedTransferEncoding_H_
#define StreamHttpChunkedTransferEncoding_H_

// =================================================

#include <Arduino.h>
#include <Stream.h>

// =================================================

#include "AnyBuffer.h"

// =================================================

class StreamHttpChunkedTransferEncoding : public Stream
{
	public:

		StreamHttpChunkedTransferEncoding( AnyBuffer< byte , byte >* _buffer , Stream* _underlyingStream );

		size_t write( uint8_t b );
		size_t write( const uint8_t* buff , size_t size );
		void flush();
		int available();
		int read();
		int peek();

		void resetInternalState();
		void setStream( Stream* _underlyingStream );

		void finishChunkedTransmission();

		int getWriteError();
		void clearWriteError();

		Stream* underlyingStream;

	protected:

		AnyBuffer< byte , byte >* buffer;

		size_t writeArrayToUnderlyingStream( uint8_t* buff , size_t size );
		//size_t writeArrayToUnderlyingStream( uint8_t* buff1 , size_t size1 , uint8_t* buff2 , size_t size2 );
};

// =================================================

#endif /* StreamHttpChunkedTransferEncoding_H_ */

/*
#ifndef StreamHttpChunkedTransferEncoding_H_
#define StreamHttpChunkedTransferEncoding_H_

// =================================================

#include <Arduino.h>
#include <Stream.h>

// =================================================

class StreamHttpChunkedTransferEncoding : public Stream
{
	public:

		StreamHttpChunkedTransferEncoding( uint8_t* _buffer , unsigned char _bufferSize , Stream* _underlyingStream );

		size_t write( uint8_t b );
		//size_t write( const uint8_t* buff , size_t size );
		void flush();
		int available();
		int read();
		int peek();

		void resetInternalState();
		void setStream( Stream* _mainStream );

		void finishChunkedTransmission();

		Stream* underlyingStream;

	protected:

		uint8_t* buffer;
		unsigned char bufferSize;
		unsigned char index;
};

// =================================================

#endif
 */

