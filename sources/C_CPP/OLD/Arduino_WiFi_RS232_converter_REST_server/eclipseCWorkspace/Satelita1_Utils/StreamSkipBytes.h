/*
 * StreamSkipBytes.h
 *
 *  Created on: 10-05-2012
 *      Author: root
 */

#ifndef STREAMSKIPBYTES_H_
#define STREAMSKIPBYTES_H_

// =================================================

#include <Arduino.h>
//#include <Print.h>

// =================================================

//#include "Configuration.c"
//#include "Streaming.h"
#include "DebugPrinter.h"

// =================================================

class StreamSkipBytes : public Stream
{
	public:

		StreamSkipBytes();//( Print& _p );

		size_t write( uint8_t b );
		int available();
		int read(); // -1 if no data available in stream, 0 if bytes are still not skipped (execute read() again), 1 if successfully skip bytes (to reset internal state you have to execute initStream() )
		int peek();
		void flush();

		void setStream( Stream* _mainStream );
		void resetInternalState( unsigned int _skipBytesCount );
		void resetInternalState( char* _stopSequence , bool _leaveLastByteInStream );

		Stream* mainStream;

	protected:
		//Print& p;
		DebugPrinter dp;
		//static const PROGMEM prog_char className[];

		bool workAsByteCountSkipper;
		unsigned int skipBytesCount;
		bool leaveLastByteInStream;
		char* stopSequence;
		unsigned char alreadyMatchedBytesCount;
};

// =================================================

#endif /* STREAMSKIPBYTES_H_ */

