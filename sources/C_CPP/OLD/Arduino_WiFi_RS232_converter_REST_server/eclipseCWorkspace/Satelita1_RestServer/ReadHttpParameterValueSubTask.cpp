/*
 * ReadHttpParameterValueSubTask.cpp
 *
 *  Created on: 28-04-2012
 *      Author: root
 */

// =================================================

#include "ReadHttpParameterValueSubTask.h"

// =================================================

ReadHttpParameterValueSubTask::ReadHttpParameterValueSubTask( RestServerSubTask* _errorSubTask , unsigned int _readingMaxTime , unsigned char* _arrayForValueBytes , unsigned char _arrayForValueBytesSize ) : dp( PSTR( "ReadHttpParameterValueSubTask" ) )//: p( _p )
{
	errorSubTask = _errorSubTask;

	readingMaxTime = _readingMaxTime;
	arrayForValueBytes = _arrayForValueBytes;
	arrayForValueBytesSize = _arrayForValueBytesSize;
}

// =================================================

void ReadHttpParameterValueSubTask::setWork( RestServerSubTask* _subTaskAfterParsingAllParameters , ServiceDescription* _selectedServiceDescription , RestServerSubTask* _subTaskThatWillReadNextHttpParameterName )
{
	subTaskAfterParsingAllParameters = _subTaskAfterParsingAllParameters;
	selectedServiceDescription = _selectedServiceDescription;
	subTaskThatWillReadNextHttpParameterName = _subTaskThatWillReadNextHttpParameterName;
}

// =================================================

char* ReadHttpParameterValueSubTask::getSubTaskName()
{
	return "ReadHttpParameterValue-sub-task";
}

// =================================================

void ReadHttpParameterValueSubTask::resetInternalState()
{
	static const PROGMEM prog_char functionName[] = "resetInternalState";
	//static const char* prefix = "ReadHttpParameterValueSubTask:resetInternalState():";

	letterIndex = 0;

	for( int i = 0 ; i < arrayForValueBytesSize ; i++ ) arrayForValueBytes[i] = 0;

	startTime = millis();
}

// =================================================

RestServerSubTask* ReadHttpParameterValueSubTask::executeSubTask( Stream* stream )
{
	static const PROGMEM prog_char functionName[] = "executeSubTask";
	//static const char* prefix = "ReadHttpParameterValueSubTask:executeSubTask():";

	while( letterIndex < arrayForValueBytesSize && ( millis() - startTime < readingMaxTime ) )
	{
		if( stream->available() == 0 ) return NULL;

		int readByte = stream->read();

		if( readByte == -1 ) return NULL;

		if( readByte == ' ' )
		{
			parseReadParameterValue();

			//info( p << prefix << "przechodze do tasku 'subTaskAfterParsingAllParameters'" << endl; ) // todo usunac

			return subTaskAfterParsingAllParameters;
		}
		else
		if( readByte == '&' )
		{
			parseReadParameterValue();

			return subTaskThatWillReadNextHttpParameterName;
		}
		else
		{
			arrayForValueBytes[letterIndex] = readByte;
			letterIndex++;
		}
	}

	return errorSubTask;
}

// =================================================

void ReadHttpParameterValueSubTask::parseReadParameterValue()
{
	static const PROGMEM prog_char functionName[] = "parseReadParameterValue";
	//static const char* prefix = "ReadHttpParameterValueSubTask:parseReadParameterValue():";

	if( selectedServiceDescription != NULL )
	{
		//all( p << prefix << "for rest service '" << selectedServiceDescription->restService->name << "' incomming value = '" << (char*)arrayForValueBytes << "'" << endl; )
		aln( "for rest service '%s' incomming value = '%s'" , selectedServiceDescription->restService->name , arrayForValueBytes )

		if( selectedServiceDescription->restService->type == REST_SERVICE_TYPE_UPDATEABLE_BY_MYSELF || selectedServiceDescription->restService->type == REST_SERVICE_TYPE_UPDATEABLE_TEXT )
		{
			selectedServiceDescription->restService->setTextValue( arrayForValueBytes );
		}
		else
		if( selectedServiceDescription->restService->type == REST_SERVICE_TYPE_UPDATEABLE_BOOLEAN || selectedServiceDescription->restService->type == REST_SERVICE_TYPE_UPDATEABLE_BOOLEAN_ONOFF || selectedServiceDescription->restService->type == REST_SERVICE_TYPE_UPDATEABLE_BOOLEAN_ONE_TIME_EXECUTION )
		{
			//all( p << prefix << "for rest service '" << selectedServiceDescription->restService->name << "' incomming value = '" << (char*)arrayForValueBytes << "'" << endl; )
			//aln(  )

			bool newValue = arrayForValueBytes[0] - 48 == 1 ? true : false;

			//info( p << prefix << "arrayForValueBytes[0]=" << arrayForValueBytes[0] << ", arrayForValueBytes[0]=" << (int)arrayForValueBytes[0] << endl; )
			//info( p << prefix << "newValue=" << newValue << endl; )
			//info( p << prefix << "current value=" << selectedServiceDescription->restService->getBooleanValue() << endl; )

			//bool prev = selectedServiceDescription->restService->getBooleanValue();

			selectedServiceDescription->restService->setBooleanValue( newValue );

			// todo usunac
			//info( p << prefix << "prev value=" << prev << ", current value=" << selectedServiceDescription->restService->getBooleanValue() << endl; )
		}
		else
		if( selectedServiceDescription->restService->type == REST_SERVICE_TYPE_UPDATEABLE_INT )
		{
			// spr min max i zrownac do min max a potem przekazac
			int newValue = atoi( (char*)arrayForValueBytes );

			//if( newValue < selectedServiceDescription->restService->getIntMinValue() ) newValue = selectedServiceDescription->restService->getIntMinValue();
			//if( newValue < selectedServiceDescription->restService->getIntMaxValue() ) newValue = selectedServiceDescription->restService->getIntMaxValue();

			selectedServiceDescription->restService->setIntValue( constrain( newValue , selectedServiceDescription->restService->getIntMinValue() , selectedServiceDescription->restService->getIntMaxValue() ) );
		}
		else
		{
			//warning( p << prefix << "unsupported rest service type, tryed to set for service '" << selectedServiceDescription->restService->name << "' incomming value = '" << (char*)arrayForValueBytes << "'" << endl; )
			wln( "unsupported rest service type, tryed to set for service '%s' incomming value = '%s'" , selectedServiceDescription->restService->name , arrayForValueBytes )
		}
	}
}

// =================================================
