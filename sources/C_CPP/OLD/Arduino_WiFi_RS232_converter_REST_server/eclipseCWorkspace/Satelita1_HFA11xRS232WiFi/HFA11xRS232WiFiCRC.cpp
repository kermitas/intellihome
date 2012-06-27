/*
 * HFA11xRS232WiFiCRC.cpp
 *
 *  Created on: 13-05-2012
 *      Author: root
 */

// =================================================

#include "HFA11xRS232WiFiCRC.h"

// =================================================

HFA11xRS232WiFiCRC::HFA11xRS232WiFiCRC() : dp( PSTR( "HFA11xRS232WiFiCRC" ) )
{
	reset();
}

// =================================================

void HFA11xRS232WiFiCRC::reset()
{
	crcCounter = 0;
	//lastprocessedByte = 0;
	//isLastprocessedByteSet = false;
	isFirstByteSet = false;
}

// =================================================

void HFA11xRS232WiFiCRC::processBytes( byte* buff , byte size )
{
	unsigned int* p = NULL;

	if( isFirstByteSet )
	{
		processByte( buff[0] );
		p = (unsigned int*)(buff+1);
		size--;
	}
	else
	{
		p = (unsigned int*)buff;
	}

	while( size > 1 )
	{
		crcCounter += *p++;
		size -= 2;
	}

	if( size > 0 )
	{
		//crcCounter += *(byte*)p;

		arr[0] = *(byte*)p;
		isFirstByteSet = true;
	}
	//else
	//{
	//	isFirstByteSet = false;
	//}
}

// =================================================

void HFA11xRS232WiFiCRC::processByte( byte b )
{
	//static const PROGMEM prog_char functionName[] = "processByte";

	if( !isFirstByteSet )
	{
		arr[0] = b;
		isFirstByteSet = true;
	}
	else
	{
		arr[1] = b;
		char* arrPtr = &arr[0];
		unsigned int* u = (unsigned int*)arrPtr;
		crcCounter += *u;

		isFirstByteSet = false;
	}

	/*
	if( !isLastprocessedByteSet )
	{
		lastprocessedByte = b;
		isLastprocessedByteSet = true;
	}
	else
	{
		//crcCounter += lastprocessedByte * 256 + b;
		crcCounter += b * 256 + lastprocessedByte;
		isLastprocessedByteSet = false;
	}*/

	//isLastprocessedByteSet = !isLastprocessedByteSet;

	//crcCounter += oddByte ? b * 256 : b;

	//crcCounter += oddByte ? b * 256 : b;
	//crcCounter += oddByte ? b : b * 256; //A1

	//lastprocessedByte = b;

	//aln( "b = %c (%u), crcCounter = %lu" , b , b , crcCounter )

	//oddByte = !oddByte;
}

// =================================================

unsigned char HFA11xRS232WiFiCRC::getCRCLowByte( unsigned int crcSum )
{
	return (crcSum) & 0xff;
}

// =================================================

unsigned char HFA11xRS232WiFiCRC::getCRCHighByte( unsigned int crcSum )
{
	return (crcSum) >> 8;
}

// =================================================

unsigned int HFA11xRS232WiFiCRC::getCRCSum()
{
	static const PROGMEM prog_char functionName[] = "getCRCSum";

	unsigned long localCRCcounter = crcCounter;

	if( isFirstByteSet ) localCRCcounter += arr[0];

	/*if( isLastprocessedByteSet )
	{
		localCRCcounter += lastprocessedByte;
	}*/

	localCRCcounter = ( localCRCcounter >> 16 ) + ( localCRCcounter & 0xffff );
	localCRCcounter += ( localCRCcounter >> 16 );
	//localCRCcounter = ~localCRCcounter;

	unsigned int crcSum = ~localCRCcounter;

	aln( "calculated crcSum = %u , localCRCcounter = %lu" , crcSum , localCRCcounter )

	return crcSum;
}

// =================================================

bool HFA11xRS232WiFiCRC::writeCRCBytesToStream( Stream* stream )
{
	static const PROGMEM prog_char functionName[] = "writeCRCBytesToStream";

	unsigned int crcSum = getCRCSum();
	unsigned char highByte = getCRCHighByte( crcSum );
	unsigned char lowByte = getCRCLowByte( crcSum );

	aln( "writing to stream crc highByte = %u, lowByte = %u (in order: first LOW %u, then HIGH byte %u)" , highByte , lowByte , lowByte , highByte )

	//stream->write( lowByte );
	//stream->write( highByte );

	return stream->write( lowByte ) + stream->write( highByte ) == 2;
}

// =================================================

/*
// =================================================

HFA11xRS232WiFiCRC::HFA11xRS232WiFiCRC() : dp( PSTR( "HFA11xRS232WiFiCRC" ) , DEBUG_LEVEL_ALL )
{
	reset();
}

// =================================================

void HFA11xRS232WiFiCRC::reset()
{
	crcCounter = 0;
	lastprocessedByte = 0;
	oddByte = true;
}

// =================================================

void HFA11xRS232WiFiCRC::processByte( unsigned char b )
{
	static const PROGMEM prog_char functionName[] = "processByte";

	//crcCounter += oddByte ? b * 256 : b;

	//crcCounter += oddByte ? b * 256 : b;
	crcCounter += oddByte ? b : b * 256; //A1

	lastprocessedByte = b;

	aln( "b = %c (%u), crcCounter = %lu" , b , b , crcCounter )

	oddByte = !oddByte;
}

// =================================================

unsigned char HFA11xRS232WiFiCRC::getCRCLowByte( unsigned int crcSum )
{
	return (crcSum) & 0xff;
}

// =================================================

unsigned char HFA11xRS232WiFiCRC::getCRCHighByte( unsigned int crcSum )
{
	return (crcSum) >> 8;
}

// =================================================

unsigned int HFA11xRS232WiFiCRC::getCRCSum()
{
	static const PROGMEM prog_char functionName[] = "getCRCSum";

	unsigned long localCRCcounter = crcCounter;

	if( !oddByte )
	{
		//localCRCcounter -= lastprocessedByte;
		//localCRCcounter += lastprocessedByte * 256;

		localCRCcounter -= lastprocessedByte * 256; //A1
		localCRCcounter += lastprocessedByte; //A1

	}



	localCRCcounter = ( (localCRCcounter) >> 16 ) + ( (localCRCcounter) & 0xffff );
	localCRCcounter += ( (localCRCcounter) >> 16 );
	localCRCcounter = ~localCRCcounter;

	//unsigned int crcSum = (localCRCcounter) & 0xffff;
	unsigned int crcSum = localCRCcounter;

	aln( "calculated crcSum = %u , oddByte = %u, localCRCcounter = %lu" , crcSum , oddByte , localCRCcounter )

	return crcSum;
}

// =================================================

bool HFA11xRS232WiFiCRC::writeCRCBytesToStream( Stream* stream )
{
	static const PROGMEM prog_char functionName[] = "writeCRCBytesToStream";

	unsigned int crcSum = getCRCSum();
	unsigned char highByte = getCRCHighByte( crcSum );
	unsigned char lowByte = getCRCLowByte( crcSum );

	aln( "writing to stream crc highByte = %u, lowByte = %u (in order: first LOW %u, then HIGH byte %u)" , highByte , lowByte , lowByte , highByte )

	if( stream->write( lowByte ) != 1 || stream->write( highByte ) != 1 ) return false;

	return true;
}

// =================================================
*/


