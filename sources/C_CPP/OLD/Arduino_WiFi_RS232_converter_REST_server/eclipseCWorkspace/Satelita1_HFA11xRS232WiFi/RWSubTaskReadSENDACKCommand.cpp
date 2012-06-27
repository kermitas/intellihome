/*
 * RWSubTaskReadSENDACKCommand.cpp
 *
 *  Created on: 22-05-2012
 *      Author: root
 */

// =================================================

#include "RWSubTaskReadSENDACKCommand.h"

// =================================================

RWSubTaskReadSENDACKCommand::RWSubTaskReadSENDACKCommand( AnyBuffer< byte , byte >* _outputBuffer , StreamHFA11xRS232WiFiCRC* _crcStream , RWCommandSerialNumber* _rwCommandSerialNumber , RWSubTask* _subTaskOnSuccess , RWSubTask* _subTaskOnFail ) : dp( PSTR( "RWSubTaskReadSENDACKCommand" ) , DEBUG_LEVEL_ALL )
{
	outputBuffer = _outputBuffer;
	crcStream = _crcStream;
	rwCommandSerialNumber = _rwCommandSerialNumber;
	//subTaskOnRetry = _subTaskOnRetry;
	subTaskOnSuccess = _subTaskOnSuccess;
	subTaskOnFail = _subTaskOnFail;
}

// =================================================

char* RWSubTaskReadSENDACKCommand::getSubTaskName()
{
	return "ReadSENDACKCommand";
}

// =================================================

void RWSubTaskReadSENDACKCommand::resetInternalState()
{

}

// =================================================

unsigned long RWSubTaskReadSENDACKCommand::getStateTimeout()
{
	return 2*1000;
}

// =================================================

RWSubTask* RWSubTaskReadSENDACKCommand::getStateAfterTimeout()
{
	return subTaskOnFail;
}

// =================================================

void RWSubTaskReadSENDACKCommand::setWork( byte _sendDataSize , RWSubTask* _subTaskOnRetry )
{
	static const PROGMEM prog_char functionName[] = "setWork";

	sendDataSize = _sendDataSize;
	//retryNumber = _retryNumber;
	subTaskOnRetry = _subTaskOnRetry;

	iln( "setting sendDataSize to %u, do retry on fail = %u" , sendDataSize , (subTaskOnRetry != NULL ? 1 : 0) )
}

// =================================================

RWSubTask* RWSubTaskReadSENDACKCommand::executeSubTask()
{
	static const PROGMEM prog_char functionName[] = "executeSubTask";

	// ---

	//crcStream->resetIncommingState();

	// ---

	// command
	if( crcStream->underlyingStream->read() != 1 ) return subTaskOnFail;

	// sn
	if( crcStream->underlyingStream->read() != rwCommandSerialNumber->commandSerialNumber ) return subTaskOnFail;

	// ---

	// reserved two bytes byte
	if( crcStream->underlyingStream->read() != 0 ) return subTaskOnFail;
	if( crcStream->underlyingStream->read() != 0 ) return subTaskOnFail;

	// ---

	byte ackInfo = crcStream->underlyingStream->read();

	// ---

	/*if( !compareCRCsumWithCRCsumCalculatedOnTwoIncommingBytes( crcStream->getIncommingDataCRC() ) )
	{
		wln( "incomming CRC (in SEND_ACK) and our locally counted CRC does not match! setting write_error to" )

		delay( 3000 ); // todo temporary

		//inputBuffer->setPositionAndLimit( positionBefore , limitBefore );

		//read_error = -5;
		//return;

		return subTaskOnFail;
	}
	else*/


	// todo 0 - ok, 255 - err
	if( ackInfo != 0 )
	{
		//retryNumber--;

		//rwCommandSerialNumber->commandSerialNumber++;

		wln( "received ackInfo=%u (0 = OK)" , ackInfo )
		//delay( 1000 ); // todo remove

		if( subTaskOnRetry != NULL )
		{
			// todo rozwazyc co sie stanie jak pomiedzy kolejnymi retry ktos dopisze nowe dane do outputBuffer !!

			//rwSubTaskSendSENDCommand->setWork( retryNumber );

			return subTaskOnRetry;
		}
		else
		{
			return subTaskOnFail;
		}
	}
	else
	{
		// jesli ackInfo wykazuje, ze wszystko jest OK!!

		rwCommandSerialNumber->commandSerialNumber++;

		/*
		byte positionDiff = outputBuffer->position - bytesSendInSENDcommand;

		if( positionDiff > 0 ) // ktos dodal do bufora jakies dane po tym jak wyslalismy poprzednie
		{
			memcpy( &outputBuffer->array[ 0 ] , &outputBuffer->array[ bytesSendInSENDcommand ] , positionDiff );

			outputBuffer->setPositionAndLimit( positionDiff , outputBuffer->capacity );
		}
		else
		{
			outputBuffer->setPositionAndLimit( 0 , outputBuffer->capacity );
		}*/

		outputBuffer->setPosition( outputBuffer->position + sendDataSize );

		//if( outputBuffer->position == outputBuffer->limit == outputBuffer->capacity ) outputBuffer->setPositionAndLimit( 0 , 0 );

		if( outputBuffer->position == outputBuffer->limit )
		{
			if( outputBuffer->limit == outputBuffer->capacity )
			{
				outputBuffer->setPositionAndLimit( 0 , 0 );
			}
		}

		return subTaskOnSuccess;
	}

	// ---

	/*
	unsigned int size;

	size = crcStream->read(); // low byte of incomming data length
	size += 256 * crcStream->read(); // high byte of incomming data length

	if( size > inputBuffer->getUnusedSpace() ) return subTaskOnFail;

	// ---

	rwSubTaskReadRECVACKCommandData->setWork( size );

	rwSubTaskWaitForData->setWork( size+2 , rwSubTaskReadRECVACKCommandData , 2*1000 , subTaskOnFail );

	// ---

	return rwSubTaskWaitForData;*/
}


// =================================================

/*
bool RWSubTaskReadSENDACKCommand::compareCRCsumWithCRCsumCalculatedOnTwoIncommingBytes( unsigned int crcCountedByUnderlyingCRCStream )
{
	static const PROGMEM prog_char functionName[] = "compareCRCsumWithCRCsumCalculatedOnTwoIncommingBytes";

	//while( crcStream->available() < 2 ); // waiting for 2B of crc

	unsigned int crcCountedUsingTwoLastBytes = 0;

	crcCountedUsingTwoLastBytes = (unsigned char)crcStream->read(); // first byte of crc (low byte of u16)

	crcCountedUsingTwoLastBytes += 256 * (unsigned char)crcStream->read(); // second byte of crc (high byte of u16)

	aln( "crcCountedUsingTwoLastBytes = %u , crcCountedByUnderlyingCRCStream = %u" , crcCountedUsingTwoLastBytes , crcCountedByUnderlyingCRCStream )

	return crcCountedUsingTwoLastBytes == crcCountedByUnderlyingCRCStream;
}*/

// =================================================

