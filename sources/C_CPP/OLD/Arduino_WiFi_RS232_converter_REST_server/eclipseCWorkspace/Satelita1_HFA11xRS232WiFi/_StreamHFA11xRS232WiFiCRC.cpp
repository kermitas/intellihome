/*
 * StreamHFA11xRS232WiFiCRC.cpp
 *
 *  Created on: 12-05-2012
 *      Author: root
 */

/*
// =================================================

#include "StreamHFA11xRS232WiFiCRC.h"

// =================================================

StreamHFA11xRS232WiFiCRC::StreamHFA11xRS232WiFiCRC( unsigned char _maximumLengthOfIncommingData )
{
	maximumLengthOfIncommingData = _maximumLengthOfIncommingData;

	setStream( NULL );
	resetIncommingAndOutgoingState();
}

// =================================================

void StreamHFA11xRS232WiFiCRC::setStream( Stream* _mainStream )
{
	mainStream = _mainStream;
}

// =================================================

void StreamHFA11xRS232WiFiCRC::resetIncommingAndOutgoingState()
{
	resetIncommingState();
	resetOutgoingState();
}

// =================================================

void StreamHFA11xRS232WiFiCRC::resetOutgoingState()
{
	outgoingCRC.reset();
}

// =================================================

void StreamHFA11xRS232WiFiCRC::resetIncommingState()
{
	incommingCRC.reset();
	lengthOfIncommingPacket = -1;
	readOrPeekResponseIfThereWasPeekedByte = -1000;
	incommingCRCcheck = true;
}

// =================================================

void StreamHFA11xRS232WiFiCRC::writeCrCToStream()
{
	outgoingCRC.calculateCRC();

	mainStream->write( outgoingCRC.crcByte1 );
	mainStream->write( outgoingCRC.crcByte1 );

	resetOutgoingState();
}

// =================================================

int StreamHFA11xRS232WiFiCRC::read()
{
	return readOrPeek( false );
}

// =================================================

int StreamHFA11xRS232WiFiCRC::peek()
{
	return readOrPeek( true );
}

// =================================================

int StreamHFA11xRS232WiFiCRC::readOrPeek( bool doPeek )
{
	int b = doPeek ? mainStream->peek() : mainStream->read();

	if( b == -1 )
	{
		return -1;
	}
	else
	{
		if( doPeek )
		{
			if( readOrPeekResponseIfThereWasPeekedByte != -1000 )
			{
				return readOrPeekResponseIfThereWasPeekedByte;
			}
			else
			{
				readOrPeekResponseIfThereWasPeekedByte = processIncommingByte( b );
				return readOrPeekResponseIfThereWasPeekedByte;
			}
		}
		else
		{
			if( readOrPeekResponseIfThereWasPeekedByte != -1000 )
			{
				int result = readOrPeekResponseIfThereWasPeekedByte;
				readOrPeekResponseIfThereWasPeekedByte = -1000;
				return result;
			}
			else
			{
				return processIncommingByte( b );
			}
		}
	}
}

// =================================================

int StreamHFA11xRS232WiFiCRC::processIncommingByte( unsigned char b )
{
	if( lengthOfIncommingPacket == -1 )
	{
		if( b == 1 )
			lengthOfIncommingPacket = 8;
		else
			lengthOfIncommingPacket = 2006;
	}

	if( lengthOfIncommingPacket == 2001 )
	{
		lowByteOfLengthSectionInRECVACKcommand = b;
	}
	else
	if( lengthOfIncommingPacket == 2000 )
	{
		lengthOfIncommingPacket = lowByteOfLengthSectionInRECVACKcommand + b * 256;

		if( lengthOfIncommingPacket > maximumLengthOfIncommingData )
		{
			lengthOfIncommingPacket = maximumLengthOfIncommingData; // just for the safety; stream is now in undeterminated state, should be reset
			return -4;
		}

		lengthOfIncommingPacket += 2;
	}

	lengthOfIncommingPacket--;

	if( lengthOfIncommingPacket == 1 )
	{
		incommingCRC.calculateCRC();

		incommingCRCcheck = incommingCRC.crcByte1 == b;

		return -2;
	}
	else
	if( lengthOfIncommingPacket == 0 )
	{
		if( incommingCRCcheck ) incommingCRCcheck = incommingCRC.crcByte2 == b;

		incommingCRC.reset();
		lengthOfIncommingPacket = -1;

		return -3;
	}
	else
	{
		incommingCRC.processByte( b );
		return b;
	}
}

// =================================================

bool StreamHFA11xRS232WiFiCRC::isIncommingCrcValid()
{
	return incommingCRCcheck;
}

// =================================================

void StreamHFA11xRS232WiFiCRC::flush()
{
	mainStream->flush();
}

// =================================================

size_t StreamHFA11xRS232WiFiCRC::write( uint8_t b )
{
	outgoingCRC.processByte( b );
	return mainStream->write( b );
}

// =================================================

int StreamHFA11xRS232WiFiCRC::available()
{
	return mainStream->available();
}

// =================================================
*/


