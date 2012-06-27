/*
 * RWSubTaskSendRECVCommand.cpp
 *
 *  Created on: 21-05-2012
 *      Author: root
 */

// =================================================

#include "RWSubTaskSendRECVCommand.h"

// =================================================

RWSubTaskSendRECVCommand::RWSubTaskSendRECVCommand( AnyBuffer< byte , byte >* _inputBuffer , StreamHFA11xRS232WiFiCRC* _crcStream , RWCommandSerialNumber* _rwCommandSerialNumber , RWSubTaskWaitForData* _rwSubTaskWaitForData , RWSubTaskReadRECVACKCommandHeader* _rwSubTaskReadRECVACKCommandHeader , RWSubTask* _subTaskOnFail ) : dp( PSTR( "RWSubTaskSendRECVCommand" ) , DEBUG_LEVEL_ALL )
{
	inputBuffer = _inputBuffer;
	crcStream = _crcStream;
	rwCommandSerialNumber = _rwCommandSerialNumber;
	rwSubTaskWaitForData = _rwSubTaskWaitForData;
	rwSubTaskReadRECVACKCommandHeader = _rwSubTaskReadRECVACKCommandHeader;
	subTaskOnFail = _subTaskOnFail;

	arr[0] = 2;
	arr[2] = 0;
	arr[3] = 0;
	arr[5] = 0;
}

// =================================================

char* RWSubTaskSendRECVCommand::getSubTaskName()
{
	return "SendRECVCommand";
}

// =================================================

void RWSubTaskSendRECVCommand::resetInternalState()
{

}

// =================================================

unsigned long RWSubTaskSendRECVCommand::getStateTimeout()
{
	return 2*1000;
}

// =================================================

RWSubTask* RWSubTaskSendRECVCommand::getStateAfterTimeout()
{
	return subTaskOnFail;
}

// =================================================

RWSubTask* RWSubTaskSendRECVCommand::executeSubTask()
{
	// ---

	// discarding any waiting unread data
	while( crcStream->underlyingStream->available() > 0 ) crcStream->underlyingStream->read();

	// ---

	crcStream->resetOutgoingState();

	// ---

	arr[1] = rwCommandSerialNumber->commandSerialNumber;
	arr[4] = inputBuffer->getUnusedSpace();

	crcStream->write( arr , 6 );
	crcStream->flush();

	/*
	// command
	crcStream->write( (unsigned char)2 );

	// sn
	crcStream->write( rwCommandSerialNumber->commandSerialNumber );

	// reserved two bytes (0 and 0)
	crcStream->write( 0 );
	crcStream->write( 0 );

	// low byte of incomming buffer size
	crcStream->write( inputBuffer->getUnusedSpace() );

	// high byte of incomming buffer size
	crcStream->write( (unsigned char)0 );
	*/

	crcStream->writeCRC();

	if( crcStream->available() >= 6 )
	{
		return rwSubTaskReadRECVACKCommandHeader;
	}
	else
	{
		rwSubTaskWaitForData->setWork( 6 , rwSubTaskReadRECVACKCommandHeader , 2*1000 , subTaskOnFail );
		return rwSubTaskWaitForData;
	}

	/*
	if(
		// command
		crcStream->write( (unsigned char)2 ) != 1 ||

		// sn
		crcStream->write( rwCommandSerialNumber->commandSerialNumber ) != 1 ||

		// reserved two bytes (0 and 0)
		crcStream->write( 0 ) != 1 ||
		crcStream->write( 0 ) != 1 ||

		// low byte of incomming buffer size
		crcStream->write( inputBuffer->getUnusedSpace() ) != 1 ||

		// high byte of incomming buffer size
		crcStream->write( (unsigned char)0 ) != 1 ||

		!crcStream->writeCRC()
	)
	{
		return subTaskOnFail;
	}
	else
	{
		if( crcStream->available() >= 6 )
		{
			return rwSubTaskReadRECVACKCommandHeader;
		}
		else
		{
			rwSubTaskWaitForData->setWork( 6 , rwSubTaskReadRECVACKCommandHeader , 2*1000 , subTaskOnFail );
			return rwSubTaskWaitForData;
		}
	}
	*/
}

// =================================================


