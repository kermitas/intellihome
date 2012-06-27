/*
 * StreamReadHttpMethod.h
 *
 *  Created on: 10-05-2012
 *      Author: root
 */

#ifndef STREAMREADHTTPMETHOD_H_
#define STREAMREADHTTPMETHOD_H_

// =================================================

#include <Arduino.h>

// =================================================

#include "DebugPrinter.h"

// =================================================

class StreamReadHttpMethod : public Stream
{
	public:

		StreamReadHttpMethod();

		size_t write( uint8_t b );
		int available();
		int read();
			// -1 if no data available in stream
			// 0 if http method is GET (to reset internal state you have to execute initStream() )
			// 1 if http method is POST (to reset internal state you have to execute initStream() )
			// 2 if http method is unknown because it is not GET and it is not POST (to reset internal state you have to execute initStream() )

		int peek();
		void flush();

		void setStreamAndResetInternalState( Stream* _mainStream );

		Stream* mainStream;

	protected:

		char httpMethod; // -1 - unset, 0 - GET , 1 - POST, 2 - unknown

		DebugPrinter dp;
};

// =================================================

#endif /* STREAMREADHTTPMETHOD_H_ */

