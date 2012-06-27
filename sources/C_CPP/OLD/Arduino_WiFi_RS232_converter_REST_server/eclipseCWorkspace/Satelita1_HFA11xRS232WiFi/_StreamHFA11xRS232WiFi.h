/*
 * StreamHFA11xRS232WiFi.h
 *
 *  Created on: 11-05-2012
 *      Author: root
 */

/*
#ifndef STREAMHFA11XRS232WIFI_H_
#define STREAMHFA11XRS232WIFI_H_

// =================================================

#include <Arduino.h>

// =================================================

#include "DebugPrinter.h"
#include "StreamHFA11xRS232WiFiCRC.h"
#include "AnyBuffer.h"

// =================================================

// trzeba pamietac, ze ogolnie max rozmiar jaki mozna dodac poprzez komende SEND czy RECEIVE to 1024 bajty danych

class StreamHFA11xRS232WiFi : public Stream
{
	public:

		StreamHFA11xRS232WiFi( AnyBuffer< byte , byte >* _inputBuffer , AnyBuffer< byte , byte >* _outputBuffer , unsigned char _numberOfRetriesWhileAskingForIncommingData , unsigned char _numberOfRetriesWhileSendingOutgoingData );

		size_t write( uint8_t b ); // 1 if byte was wrote, 0 if there was an write error
		int available(); // 0 if no data in stream or there were read_error
		int read(); // -1 no data in stream (or there were read_error), x read byte
		int peek(); // description like read()
		void flush();

		void setStream( Stream* _stream );
		void resetInternalState();

		StreamHFA11xRS232WiFiCRC crcStream;

		int getReadError();
		void clearReadError();

	protected:

		DebugPrinter dp;

		AnyBuffer< byte , byte >* inputBuffer;
		AnyBuffer< byte , byte >* outputBuffer;

		int read_error;

		unsigned char numberOfRetriesWhileAskingForIncommingData;
		unsigned char numberOfRetriesWhileSendingOutgoingData;

		unsigned char commandSerialNumber;

		void sendRECVndReadRECVACK();
		void sendRECV();
		void readRECVACK();

		int readOrPeek( bool justDoPeek );

		void sendSENDAndReadSENDACK();
		void sendSEND();
		void readSENDACK();

		// common codes for write_error and read_error (if error code is set that means that stream is in undefined state, connection should be closed-or-restarted):
			// 0 all ok, no error
			// -1 could not write whole data to underlying stream (while sending SEND command or RECV command)
			// -2 received bad command (RECV did not received RECV_ACK, SEND did not received SEND_ACK)
			// -3 received bad serial number (in RECV ACK or SEND ACK)
			// -4 received bad two reserved bytes (in RECV_ACK or SEND_ACK; should be 00)
			// -5 crc sum does not match (in RECV_ACK or SEND_ACK)


		// write_error codes:
			// -6 received error code in SEND_ACK command that comes from from underlying stream

		// read_error codes:
			// -6 received data exceeds availabe buffer size
			// -7 could not read data incomming in RECV_ACK command

		bool compareCRCsumWithCRCsumCalculatedOnTwoIncommingBytes( unsigned int crcCountedByUnderlyingCRCStream );
};

// =================================================

#endif *//* STREAMHFA11XRS232WIFI_H_ */

