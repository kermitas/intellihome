/*
 * StreamHFA11xRS232WiFi3.h
 *
 *  Created on: 11-05-2012
 *      Author: root
 */

#ifndef STREAMHFA11XRS232WIFI3_H_
#define STREAMHFA11XRS232WIFI3_H_

// =================================================

#include <Arduino.h>

// =================================================

#include "DebugPrinter.h"
#include "AnyRingBuffer.h"
#include "StreamHFA11xRS232WiFiCRC.h"

// =================================================

// trzeba pamietac, ze ogolnie max rozmiar jaki mozna dodac poprzez komende SEND czy RECEIVE to 1024 bajty danych
// a w tym systemie ograniczylem to do 256B

class StreamHFA11xRS232WiFi3 : public Stream
{
	public:

		StreamHFA11xRS232WiFi3( AnyRingBuffer< byte >* _inputBuffer , AnyRingBuffer< byte >* _outputBuffer , StreamHFA11xRS232WiFiCRC* _crcStream );

		size_t write( uint8_t b );
		//size_t write( const uint8_t* buffer , size_t size );
		int available();
		int read();
		int peek();
		void flush();

		void resetInternalState();

	protected:

		DebugPrinter dp;

		AnyRingBuffer< byte >* inputBuffer;
		AnyRingBuffer< byte >* outputBuffer;

		StreamHFA11xRS232WiFiCRC* crcStream;

		byte arr[6];

		void discardAnyWaitingDataInUnderlyingStream( bool discardForAllSerialNumbers );

		void doFullReadCycle();
		bool sendRECVAndReadRECVACK();

		void doFullSendCycle();
		bool sendSENDAndReadSENDACK();
};

// =================================================

#endif /* STREAMHFA11XRS232WIFI3_H_ */