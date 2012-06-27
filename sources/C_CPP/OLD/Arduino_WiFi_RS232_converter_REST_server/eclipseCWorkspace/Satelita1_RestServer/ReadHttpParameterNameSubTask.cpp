/*
 * ReadHttpParameterNameSubTask.cpp
 *
 *  Created on: 28-04-2012
 *      Author: root
 */

// =================================================

#include "ReadHttpParameterNameSubTask.h"

// =================================================

ReadHttpParameterNameSubTask::ReadHttpParameterNameSubTask( RestServerSubTask* _errorSubTask , unsigned int _readingMaxTime , unsigned int _readingMaxBytesCount , ServiceDescription** _serviceDescrptions , unsigned char _serviceDescrptionsCount , bool* _arrayForMatchServiceNames , ReadHttpParameterValueSubTask* _readHttpParameterValueSubTask ) : dp( PSTR( "ReadHttpParameterNameSubTask" ) ) // : p( _p )
{
	errorSubTask = _errorSubTask;

	readingMaxTime = _readingMaxTime;
	readingMaxBytesCount = _readingMaxBytesCount;

	serviceDescrptions = _serviceDescrptions;
	serviceDescrptionsCount = _serviceDescrptionsCount;

	arrayForMatchServiceNames = _arrayForMatchServiceNames;

	readHttpParameterValueSubTask = _readHttpParameterValueSubTask;
}

// =================================================

void ReadHttpParameterNameSubTask::setWork( RestServerSubTask* _subTaskAfterParsingAllParameters )
{
	subTaskAfterParsingAllParameters = _subTaskAfterParsingAllParameters;
}

// =================================================

char* ReadHttpParameterNameSubTask::getSubTaskName()
{
	return "ReadHttpParameterName-sub-task";
}

// =================================================

void ReadHttpParameterNameSubTask::resetInternalState()
{
	static const PROGMEM prog_char functionName[] = "resetInternalState";
	//static const char* prefix = "ReadHttpParameterNameSubTask:resetInternalState():";

	alreadyReadBytesCount = 0;
	letterIndex = 0;

	for( int i = 0 ; i < serviceDescrptionsCount ; i++ ) arrayForMatchServiceNames[i] = (serviceDescrptions[i]->restService->type != REST_SERVICE_TYPE_READ_ONLY );

	startTime = millis();
}

// =================================================

RestServerSubTask* ReadHttpParameterNameSubTask::executeSubTask( Stream* stream )
{
	static const PROGMEM prog_char functionName[] = "executeSubTask";
	//static const char* prefix = "ReadHttpParameterNameSubTask:executeSubTask():";

	while( alreadyReadBytesCount < readingMaxBytesCount && ( millis() - startTime < readingMaxTime ) )
	{
		if( stream->available() == 0 ) return NULL;

		int readByte = stream->read();

		if( readByte == -1 ) return NULL;

		alreadyReadBytesCount++;

		if( readByte == ' ' )
		{
			return subTaskAfterParsingAllParameters;
		}
		else
		if( readByte == '=' )
		{
			ServiceDescription* selectedService = NULL;

			for( int i = 0 ; i < serviceDescrptionsCount ; i++ )
			{
				if( arrayForMatchServiceNames[i] )
				{
					if( serviceDescrptions[i]->restService->name[ letterIndex ] == 0 )
					{
						selectedService = serviceDescrptions[i];
						break;
					}
				}
			}

			// todo tego prawdopodobnie nie trzeba robic tutaj gdyz sie zrobi w resetInternalState()
			for( int i = 0 ; i < serviceDescrptionsCount ; i++ ) arrayForMatchServiceNames[i] = (serviceDescrptions[i]->restService->type != REST_SERVICE_TYPE_READ_ONLY );

			readHttpParameterValueSubTask->setWork( subTaskAfterParsingAllParameters , selectedService , this );
			return readHttpParameterValueSubTask;
		}
		else
		{
			for( int i = 0 ; i < serviceDescrptionsCount ; i++ )
			{
				if( arrayForMatchServiceNames[i] )
				{
					if( serviceDescrptions[i]->restService->name[ letterIndex ] != readByte )
					{
						arrayForMatchServiceNames[i] = false;
						//all( p << prefix << "service '" << serviceDescrptions[i]->restService->name << "' not matching incomming http parameter name, setting as unselected" << endl; )
						aln( "service '%s' not matching incomming http parameter name, setting as unselected" , serviceDescrptions[i]->restService->name )
					}
				}

			}

			letterIndex++;
		}
	}

	return errorSubTask;
}

// =================================================
