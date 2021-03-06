/*
 * RWSubTaskDecideToSendOutgoingData.cpp
 *
 *  Created on: 22-05-2012
 *      Author: root
 */

// =================================================

#include "RWSubTaskDecideToSendOutgoingData.h"

// =================================================

RWSubTaskDecideToSendOutgoingData::RWSubTaskDecideToSendOutgoingData( AnyBuffer< byte , byte >* _outputBuffer , RWSubTaskSendSENDCommand* _rwSubTaskSendSENDCommand , RWSubTask* _subTaskIfNotSendOutgoingData , byte _sendRetryCount ) : dp( PSTR( "RWSubTaskDecideToSendOutgoingData" ) , DEBUG_LEVEL_ALL )
{
	outputBuffer = _outputBuffer;
	rwSubTaskSendSENDCommand = _rwSubTaskSendSENDCommand;
	subTaskIfNotSendOutgoingData = _subTaskIfNotSendOutgoingData;
	sendRetryCount = _sendRetryCount;
}

// =================================================

char* RWSubTaskDecideToSendOutgoingData::getSubTaskName()
{
	return "DecideToSendOutgoingData";
}

// =================================================

void RWSubTaskDecideToSendOutgoingData::resetInternalState()
{

}

// =================================================

unsigned long RWSubTaskDecideToSendOutgoingData::getStateTimeout()
{
	return 0;
}

// =================================================

RWSubTask* RWSubTaskDecideToSendOutgoingData::getStateAfterTimeout()
{
	return NULL;
}

// =================================================

RWSubTask* RWSubTaskDecideToSendOutgoingData::executeSubTask()
{
	static const PROGMEM prog_char functionName[] = "executeSubTask";

	//outputBuffer->printReport( "outputBuffer FROM RWSubTaskDecideToSendOutgoingData::executeSubTask()" ); // todo to remove

	if( outputBuffer->getRemaining() > 0 )
	{
		//iln( "%u remaining bytes in output buffer, decided to send data (SEND commnad)" , outputBuffer->getRemaining() );

		rwSubTaskSendSENDCommand->setWork( sendRetryCount );

		return rwSubTaskSendSENDCommand;
	}
	else
	{
		//iln( "%u remaining bytes in output buffer, decided NOT to send data (SEND command)" , outputBuffer->getRemaining() );

		return subTaskIfNotSendOutgoingData;
	}

	//return outputBuffer->getRemaining() > 0 ? rwSubTaskSendSENDCommand : subTaskIfNotSendOutgoingData;
}

// =================================================


