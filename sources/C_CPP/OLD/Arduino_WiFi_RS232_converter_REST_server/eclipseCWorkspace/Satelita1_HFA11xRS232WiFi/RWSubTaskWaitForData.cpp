/*
 * RWSubTaskWaitForData.cpp
 *
 *  Created on: 21-05-2012
 *      Author: root
 */

// =================================================

#include "RWSubTaskWaitForData.h"

// =================================================

RWSubTaskWaitForData::RWSubTaskWaitForData( Stream* _stream ) : dp( PSTR( "RWSubTaskWaitForData" ) )
{
	stream = _stream;
}

// =================================================

void RWSubTaskWaitForData::setWork( unsigned int _waitForBytesCount , RWSubTask* _taskIfDataAvailable , unsigned long _timeout , RWSubTask* _taskOnTimeout )
{
	static const PROGMEM prog_char functionName[] = "setWork";

	waitForBytesCount = _waitForBytesCount;
	taskIfDataAvailable = _taskIfDataAvailable;

	timeout = _timeout;
	taskOnTimeout = _taskOnTimeout;

	aln( "waitForBytesCount = %u , taskIfDataAvailable = '%s' , timeout = %lums , taskOnTimeout = '%s'" , waitForBytesCount , taskIfDataAvailable->getSubTaskName() , timeout , (taskOnTimeout !=NULL ? taskOnTimeout->getSubTaskName() : "-null-" ) )

	/*if( taskOnTimeout != NULL )
	{
		iln( "waitForBytesCount = %u , taskIfDataAvailable = '%s' , timeout = %lums , taskOnTimeout = '%s'" , waitForBytesCount , taskIfDataAvailable->getSubTaskName() , timeout , taskOnTimeout->getSubTaskName() )
	}
	else
	{
		iln( "waitForBytesCount = %u , taskIfDataAvailable = '%s' , timeout = %lums , taskOnTimeout = '-null-'" , waitForBytesCount , taskIfDataAvailable->getSubTaskName() , timeout )
	}*/
}

// =================================================

char* RWSubTaskWaitForData::getSubTaskName()
{
	return "WaitForData";
}

// =================================================

void RWSubTaskWaitForData::resetInternalState()
{

}

// =================================================

unsigned long RWSubTaskWaitForData::getStateTimeout()
{
	return timeout;
}

// =================================================

RWSubTask* RWSubTaskWaitForData::getStateAfterTimeout()
{
	return taskOnTimeout;
}

// =================================================

RWSubTask* RWSubTaskWaitForData::executeSubTask()
{
	return stream->available() >= waitForBytesCount ? taskIfDataAvailable : NULL;
}

// =================================================


