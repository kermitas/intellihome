/*
 * DeterminateHttpMethodSubTask.cpp
 *
 *  Created on: 10-04-2012
 *      Author: root
 */

// =================================================

#include "DeterminateHttpMethodSubTask.h"

// =================================================

DeterminateHttpMethodSubTask::DeterminateHttpMethodSubTask( RestServerSubTask* _errorSubTask , SkipBytesUntilSequenceSubTask* _skipBytesUntilSequenceSubTask , ReadHttpPathSubTask* _readHttpPathSubTask ) : dp( PSTR( "DeterminateHttpMethodSubTask" ) )//: p( _p )
{
	errorSubTask = _errorSubTask;
	skipBytesUntilSequenceSubTask = _skipBytesUntilSequenceSubTask;
	readHttpPathSubTask = _readHttpPathSubTask;
}

// =================================================

char* DeterminateHttpMethodSubTask::getSubTaskName()
{
	return "DeterminateHttpMethod-sub-task";
}

// =================================================

void DeterminateHttpMethodSubTask::resetInternalState() {}

// =================================================

RestServerSubTask* DeterminateHttpMethodSubTask::executeSubTask( Stream* stream )
{
	static const PROGMEM prog_char functionName[] = "executeSubTask";
	//static const char* prefix = "DeterminateHttpMethodSubTask:executeSubTask():";

	streamReadHttpMethod.setStreamAndResetInternalState( stream );

	int httpMethod = streamReadHttpMethod.read();

	//info( p << prefix << "httpMethod read from streamReadHttpMethod = " << httpMethod << endl; )

	if( httpMethod == -1 )
	{
		return NULL;
	}
	else
	if( httpMethod == 2 )
	{
		return errorSubTask;
	}
	else
	{
		readHttpPathSubTask->setWork( httpMethod == 0 );

		skipBytesUntilSequenceSubTask->setSkipBytesCountAndNextSubTask( 4+httpMethod , readHttpPathSubTask );
		return skipBytesUntilSequenceSubTask;
	}

	/*
	if( stream->available() > 0 )
	{
		int readByte = stream->read();

		if( readByte == 'G' )
		{
			readHttpPathSubTask->setWork( true );
			skipBytesUntilSequenceSubTask->setSkipBytesCountAndNextSubTask( 4 , readHttpPathSubTask );
			return skipBytesUntilSequenceSubTask;
		}
		else
		if( readByte == 'P' )
		{
			readHttpPathSubTask->setWork( false );
			skipBytesUntilSequenceSubTask->setSkipBytesCountAndNextSubTask( 5 , readHttpPathSubTask );
			return skipBytesUntilSequenceSubTask;
		}
		else
		{
			return errorSubTask;
		}
	}
	else
	{
		return NULL;
	}*/
}

// =================================================


