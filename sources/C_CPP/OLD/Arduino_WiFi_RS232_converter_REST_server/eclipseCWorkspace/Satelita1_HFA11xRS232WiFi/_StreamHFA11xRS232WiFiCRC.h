/*
 * StreamHFA11xRS232WiFiCRC.h
 *
 *  Created on: 12-05-2012
 *      Author: root
 */

/*
#ifndef STREAMHFA11XRS232WIFICRC_H_
#define STREAMHFA11XRS232WIFICRC_H_

// =================================================

#include <Arduino.h>

// =================================================

#include "HFA11xRS232WiFiCRC.h"

// =================================================

class StreamHFA11xRS232WiFiCRC : public Stream
{
	public:

		StreamHFA11xRS232WiFiCRC( unsigned char _maximumLengthOfIncommingData );

		size_t write( uint8_t b );
		int available();
		int read();
			// -1 if no data available in stream (can be returned many times)
			// -2 when read first byte of CRC (returned once)
			// -3 when read second byte of crc (returned once; after this result of isIncommingCRCValid() is valid until next -2 )
			// -4 received incomming data length was bigger than maximumLengthOfIncommingData (returned once, now stream is in undeterminated state!!, please execute resetIncommingState() and start transmission from the beginning)
			// x - normally read byte from underlying stream
		int peek(); // behaves like read()
		void flush();

		void setStream( Stream* _mainStream );
		void resetIncommingAndOutgoingState();

		// outgoing
		void writeCrCToStream();
		void resetOutgoingState();

		// incomming
		void resetIncommingState();
		bool isIncommingCrcValid(); // return of this method is valid after first read() == -3 until next read() == -2

		Stream* mainStream;
		unsigned char maximumLengthOfIncommingData;

	protected:

		HFA11xRS232WiFiCRC outgoingCRC;

		// incomming
		HFA11xRS232WiFiCRC incommingCRC;
		int lengthOfIncommingPacket;
		unsigned char lowByteOfLengthSectionInRECVACKcommand;
		int readOrPeekResponseIfThereWasPeekedByte;
		bool incommingCRCcheck;

		int processIncommingByte( unsigned char b );
		int readOrPeek( bool doPeek );
};

// =================================================

#endif */ /* STREAMHFA11XRS232WIFICRC_H_ */

