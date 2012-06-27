/*
 * RWSubTaskReadRECVACKCommandHeader.cpp
 *
 *  Created on: 21-05-2012
 *      Author: root
 */

// =================================================

#include "RWSubTaskReadRECVACKCommandHeader.h"

// =================================================

RWSubTaskReadRECVACKCommandHeader::RWSubTaskReadRECVACKCommandHeader( AnyBuffer< byte , byte >* _inputBuffer , StreamHFA11xRS232WiFiCRC* _crcStream , RWCommandSerialNumber* _rwCommandSerialNumber , RWSubTaskWaitForData* _rwSubTaskWaitForData , RWSubTaskReadRECVACKCommandData* _rwSubTaskReadRECVACKCommandData , RWSubTask* _subTaskOnFail ) : dp( PSTR( "RWSubTaskSendRECVCommandHeader" ) , DEBUG_LEVEL_ALL )
{
	inputBuffer = _inputBuffer;
	crcStream = _crcStream;
	rwCommandSerialNumber = _rwCommandSerialNumber;
	rwSubTaskWaitForData = _rwSubTaskWaitForData;
	rwSubTaskReadRECVACKCommandData = _rwSubTaskReadRECVACKCommandData;
	subTaskOnFail = _subTaskOnFail;
}

// =================================================

char* RWSubTaskReadRECVACKCommandHeader::getSubTaskName()
{
	return "ReadRECVACKCommandHeader";
}

// =================================================

void RWSubTaskReadRECVACKCommandHeader::resetInternalState()
{

}

// =================================================

unsigned long RWSubTaskReadRECVACKCommandHeader::getStateTimeout()
{
	return 2*1000;
}

// =================================================

RWSubTask* RWSubTaskReadRECVACKCommandHeader::getStateAfterTimeout()
{
	return subTaskOnFail;
}

// =================================================

RWSubTask* RWSubTaskReadRECVACKCommandHeader::executeSubTask()
{
	// ---

	crcStream->resetIncommingState();

	// ---

	// command
	if( crcStream->read() != 2 ) return subTaskOnFail;

	// sn
	if( crcStream->read() != rwCommandSerialNumber->commandSerialNumber ) return subTaskOnFail;

	// ---

	// reserved two bytes byte
	if( crcStream->read() != 0 ) return subTaskOnFail;
	if( crcStream->read() != 0 ) return subTaskOnFail;

	// ---

	unsigned int incommingDataSize;

	incommingDataSize = crcStream->read(); // low byte of incomming data length
	incommingDataSize += 256 * crcStream->read(); // high byte of incomming data length

	if( incommingDataSize > inputBuffer->getUnusedSpace() ) return subTaskOnFail;

	// ---

	rwSubTaskReadRECVACKCommandData->setWork( incommingDataSize );

	if( crcStream->available() >= incommingDataSize+2 )
	{
		return rwSubTaskReadRECVACKCommandData;
	}
	else
	{
		rwSubTaskWaitForData->setWork( incommingDataSize+2 , rwSubTaskReadRECVACKCommandData , 2*1000 , subTaskOnFail );
		return rwSubTaskWaitForData;
	}
}

// =================================================

