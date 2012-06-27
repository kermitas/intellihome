/*
 * StreamReadUntilByte.h
 *
 *  Created on: 10-05-2012
 *      Author: root
 */

#ifndef StreamReadUntilByte_H_
#define StreamReadUntilByte_H_

// =================================================

#include <Arduino.h>

// =================================================

class StreamReadUntilByte : public Stream
{
	public:

		StreamReadUntilByte( char* _buffer , unsigned char _bufferSize );

		size_t write( uint8_t b );
		int available();
		int read();
			// -1 if no data available in stream
			// 0 if any of stopByte found, buffer is growing, execute me again later
			// x if stopByte found and it is its returned from this method, buffer contains ready data (to reset internal state you have to execute initStream() )

		int peek();
		void flush();

		void resetInternalState( char* _stopBytes );
		void setStream( Stream* _mainStream );

		char* buffer;
		Stream* mainStream;

	protected:

		unsigned char bufferSize;

		char* stopBytes;

		unsigned char alreadyReadLetterIndex;

		unsigned char foundByte;
};

// =================================================

#endif /* StreamReadUntilByte_H_ */

