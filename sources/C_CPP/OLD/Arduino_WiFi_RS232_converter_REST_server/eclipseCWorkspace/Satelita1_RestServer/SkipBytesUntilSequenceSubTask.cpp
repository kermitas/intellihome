/*
 * SkipBytesUntilSequenceSubTask.cpp
 *
 *  Created on: 18-04-2012
 *      Author: root
 */

// =================================================

#include "SkipBytesUntilSequenceSubTask.h"

// =================================================

//const PROGMEM prog_char SkipBytesUntilSequenceSubTask::className[] = "SkipBytesUntilSequenceSubTask";

// =================================================

//SkipBytesUntilSequenceSubTask::SkipBytesUntilSequenceSubTask( Print& _p , RestServerSubTask* _errorSubTask , unsigned int _skippingMaxTime , unsigned int _skippingMaxBytesCount ) : p( _p )
SkipBytesUntilSequenceSubTask::SkipBytesUntilSequenceSubTask( RestServerSubTask* _errorSubTask ) : dp( PSTR( "SkipBytesUntilSequenceSubTask" ) )//: p( _p ) //, streamSkipBytes( _p )
{
	errorSubTask = _errorSubTask;
	//skippingMaxTime = _skippingMaxTime;
	//skippingMaxBytesCount = _skippingMaxBytesCount;
}

// =================================================

void SkipBytesUntilSequenceSubTask::setStopSequenceAndNextSubTask( char* _stopSequence , bool _leaveLastByteInStream , RestServerSubTask* _nextSubTask )
{
	//workUsingSkipBytesCount = false;

	//stopSequence = _stopSequence;
	//leaveLastByteInStream = _leaveLastByteInStream;
	nextSubTask = _nextSubTask;

	streamSkipBytes.resetInternalState( _stopSequence , _leaveLastByteInStream );
}

// =================================================

void SkipBytesUntilSequenceSubTask::setSkipBytesCountAndNextSubTask( unsigned int _skipBytesCount , RestServerSubTask* _nextSubTask )
{
	//workUsingSkipBytesCount = true;

	//skipBytesCount = _skipBytesCount;
	nextSubTask = _nextSubTask;

	streamSkipBytes.resetInternalState( _skipBytesCount );
}

// =================================================

char* SkipBytesUntilSequenceSubTask::getSubTaskName()
{
	return "SkipBytesUntilSequence-sub-task";
}

// =================================================

void SkipBytesUntilSequenceSubTask::resetInternalState()
{
	//alreadySkippedBytesCount = 0;
	//alreadyMatchedBytesCount = 0;

	//startTime = millis();
}

// =================================================

RestServerSubTask* SkipBytesUntilSequenceSubTask::executeSubTask( Stream* stream )
{
	static const PROGMEM prog_char functionName[] = "executeSubTask";
	//static const char* prefix = "SkipBytesUntilSequenceSubTask:executeSubTask():";

	int streamReadingResult = 0;

	streamSkipBytes.setStream( stream );

	while( ( streamReadingResult = streamSkipBytes.read() ) == 0 ){}

	if( streamReadingResult == -1 )
	{
		return NULL;
	}
	else
	if( streamReadingResult == 1 )
	{
		return nextSubTask;
	}
	else
	{
		return errorSubTask;
	}

	/*
	if( workUsingSkipBytesCount )
	{
		while( alreadySkippedBytesCount < skipBytesCount )
		{
			if( millis() - startTime >= skippingMaxTime ) return errorSubTask;

			if( stream->available() == 0 ) return NULL;

			int readByte = stream->read();

			if( readByte == -1 ) return NULL;

			alreadySkippedBytesCount++;
		}

		return nextSubTask;
	}
	else
	{
		while( alreadySkippedBytesCount < skippingMaxBytesCount )
		{
			if( millis() - startTime >= skippingMaxTime ) return errorSubTask;

			if( stream->available() == 0 ) return NULL;

			int peekByte = stream->peek();

			//info( p << prefix << "skipping peekByte " << (char)peekByte << endl; )
			//info( p << (char)peekByte; )

			if( peekByte == -1 ) return NULL;

			if( stopSequence[alreadyMatchedBytesCount] == peekByte )
			{
				alreadyMatchedBytesCount++;

				if( stopSequence[alreadyMatchedBytesCount] == 0 )
				{
					if( !leaveLastByteInStream )
					{
						stream->read();
						//int readByte = stream->read();
						//info( p << prefix << "skipping readByte (the last one) " << (char)readByte << endl; )
					}
					else
					{
						//info( p << prefix << "leaving peekByte (the last one) " << (char)peekByte << " in stream and exit" << endl; )
					}

					return nextSubTask;
				}
			}
			else
				alreadyMatchedBytesCount = 0;

			stream->read();
			//int readByte = stream->read();
			//info( p << prefix << "skipping readByte " << (char)readByte << endl; )

			alreadySkippedBytesCount++;
		}

		return errorSubTask;
	}*/
}

// =================================================


