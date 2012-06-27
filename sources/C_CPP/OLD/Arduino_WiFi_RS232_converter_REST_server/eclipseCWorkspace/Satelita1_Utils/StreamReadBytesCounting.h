/*
 * StreamReadBytesCounting.h
 *
 *  Created on: 10-05-2012
 *      Author: root
 */

#ifndef STREAMREADBYTESCOUNTING_H_
#define STREAMREADBYTESCOUNTING_H_

// =================================================

#include <Arduino.h>

// =================================================

class StreamReadBytesCounting : public Stream
{
	public:

		StreamReadBytesCounting();

		size_t write( uint8_t b );
		int available();
		int read();
		int peek();
		void flush();

		void setStream( Stream* _mainStream );
		void resetInternalState();
		unsigned int getReadBytesCount();

		Stream* mainStream;

	protected:

		unsigned int readBytesCount;
};

// =================================================

#endif /* STREAMREADBYTESCOUNTING_H_ */

