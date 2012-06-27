/*
 * RWSubTaskReadRECVACKCommandData.cpp
 *
 *  Created on: 21-05-2012
 *      Author: root
 */

// =================================================

#include "RWSubTaskReadRECVACKCommandData.h"

// =================================================

RWSubTaskReadRECVACKCommandData::RWSubTaskReadRECVACKCommandData( AnyBuffer< byte , byte >* _inputBuffer , StreamHFA11xRS232WiFiCRC* _crcStream , RWCommandSerialNumber* _rwCommandSerialNumber , RWSubTask* _subTaskOnSuccess , RWSubTask* _subTaskOnFail )
	: dp( PSTR( "RWSubTaskReadRECVACKCommandData" ) )
{
	inputBuffer = _inputBuffer;
	crcStream = _crcStream;
	rwCommandSerialNumber = _rwCommandSerialNumber;
	subTaskOnSuccess = _subTaskOnSuccess;
	subTaskOnFail = _subTaskOnFail;
}

// =================================================

char* RWSubTaskReadRECVACKCommandData::getSubTaskName()
{
	return "ReadRECVACKCommandData";
}

// =================================================

void RWSubTaskReadRECVACKCommandData::resetInternalState()
{

}

// =================================================

unsigned long RWSubTaskReadRECVACKCommandData::getStateTimeout()
{
	return 2*1000;
}

// =================================================

RWSubTask* RWSubTaskReadRECVACKCommandData::getStateAfterTimeout()
{
	return subTaskOnFail;
}

// =================================================

void RWSubTaskReadRECVACKCommandData::setWork( unsigned int _incommingDataSize )
{
	static const PROGMEM prog_char functionName[] = "setWork";

	incommingDataSize = _incommingDataSize;

	aln( "setting incommingDataSize to %u" , incommingDataSize )
}

// =================================================

RWSubTask* RWSubTaskReadRECVACKCommandData::executeSubTask()
{
	static const PROGMEM prog_char functionName[] = "executeSubTask";

	byte positionBefore = inputBuffer->position;
	byte limitBefore = inputBuffer->limit;

	if( incommingDataSize > 0 )
	{
		//iln( "command=2, sn=%u, incomming data size=%u" , commandSerialNumber , size )

		//while( crcStream.available() < size ); // waiting for incomming data



		inputBuffer->setPositionAndLimit( limitBefore , limitBefore + incommingDataSize );

		{ // todo temporary
			aln( "positionBefore=%u , limitBefore=%u , incomming data size=%u" , positionBefore , limitBefore , incommingDataSize );
			inputBuffer->printReport( "BEFORE READING (after buffer set)" );
			//delay( 1000 );
		}

		char* arr = (char*)inputBuffer->array;

		byte readBytesCount = crcStream->readBytes( &arr[ inputBuffer->position ] , incommingDataSize );

		if( readBytesCount != incommingDataSize )
		{
			wln( "should read %u bytes but only read %u bytes" , incommingDataSize , readBytesCount )
			return subTaskOnFail;
		}

		/*
		while( inputBuffer->getRemaining() > 0 )
		{
			int readByte = crcStream->read();

			if( readByte == -1 )
			{
				//inputBuffer->setPositionAndLimit( positionBefore , inputBuffer->position );

				return subTaskOnFail;
			}

			inputBuffer->put( readByte );

			{ // todo temporary
				inputBuffer->printReport( "WHILE READING" );
				//delay( 1000 );
			}
		}
		*/

		//inputBuffer->setPositionAndLimit( positionBefore , inputBuffer->position );
		inputBuffer->setPositionAndLimit( positionBefore , limitBefore + incommingDataSize );

		//delay( 1000 ); // todo temporary
	}

	// ---

	// todo temporary
	if( inputBuffer->getRemaining() > 0 )
	{
		inputBuffer->printReport( "AFTER READING" );
		//delay( 3000 );
	}

	// ---

	if( !compareCRCsumWithCRCsumCalculatedOnTwoIncommingBytes( crcStream->getCRC() ) )
	{
		wln( "incomming CRC (in RECV_ACK) and our locally counted CRC does not match!" )

		delay( 3000 ); // todo temporary

		inputBuffer->setPositionAndLimit( positionBefore , limitBefore );
		inputBuffer->printReport( "AFTER CRC fail" ); // todo tmp

		//read_error = -5;
		//return;

		return subTaskOnFail;
	}
	else
	{
		rwCommandSerialNumber->commandSerialNumber++;
		return subTaskOnSuccess;
	}

	// ---
}

// =================================================

bool RWSubTaskReadRECVACKCommandData::compareCRCsumWithCRCsumCalculatedOnTwoIncommingBytes( unsigned int crcCountedByUnderlyingCRCStream )
{
	static const PROGMEM prog_char functionName[] = "compareCRCsumWithCRCsumCalculatedOnTwoIncommingBytes";

	//while( crcStream->available() < 2 ); // waiting for 2B of crc

	unsigned int crcCountedUsingTwoLastBytes = 0;

	crcCountedUsingTwoLastBytes = (unsigned char)crcStream->read(); // first byte of crc (low byte of u16)

	crcCountedUsingTwoLastBytes += 256 * (unsigned char)crcStream->read(); // second byte of crc (high byte of u16)

	aln( "crcCountedUsingTwoLastBytes = %u , crcCountedByUnderlyingCRCStream = %u" , crcCountedUsingTwoLastBytes , crcCountedByUnderlyingCRCStream )

	return crcCountedUsingTwoLastBytes == crcCountedByUnderlyingCRCStream;
}

// =================================================


