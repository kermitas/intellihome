/*
 * HttpChunkedTransferEncodingStream.h
 *
 *  Created on: 08-05-2012
 *      Author: root
 */

#ifndef HTTPCHUNKEDTRANSFERENCODINGSTREAM_H_
#define HTTPCHUNKEDTRANSFERENCODINGSTREAM_H_

// =================================================

#include <Arduino.h>

// =================================================

class HttpChunkedTransferEncodingStream : public Stream
{
	public:

		HttpChunkedTransferEncodingStream( uint8_t* _buffer , unsigned char _bufferSize );

		size_t write( uint8_t b );
		void flush();
		int available();
		int read();
		int peek();

		void resetStream( Stream* _mainStream );
		void finishChunkedTransmission();

	protected:

		Stream* mainStream;

		uint8_t* buffer;
		unsigned char bufferSize;
		unsigned char index;

};

// =================================================

#endif /* HTTPCHUNKEDTRANSFERENCODINGSTREAM_H_ */
