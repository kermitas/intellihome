/*
 * ReadHttpPathSubTask.cpp
 *
 *  Created on: 22-04-2012
 *      Author: root
 */

/*
// =================================================

#include "ReadHttpPathSubTask.h"

// =================================================

const char* ReadHttpPathSubTask::stopBytes = " /?*";

// =================================================

ReadHttpPathSubTask::ReadHttpPathSubTask( Print& _p , RestServerSubTask* _errorSubTask , SkipBytesUntilSequenceSubTask* _skipBytesUntilSequenceSubTask , ReadHttpParameterNameSubTask* _readHttpParameterNameSubTask , SendResponseSubTask* _sendResponseSubTask , unsigned int _readingMaxTime , unsigned int _readingMaxBytesCount , ServiceDescription** _serviceDescrptions , unsigned char _serviceDescrptionsCount , ServiceDescription* _arrayForSelectdServices , unsigned char* _arrayForMatchServiceNames , bool _leaveLastByteOfHttpHeaderInStream , char* _buffer , unsigned char _bufferSize ) : p( _p ) , streamReadUntilByte( _buffer , _bufferSize )
{
	errorSubTask = _errorSubTask;
	skipBytesUntilSequenceSubTask = _skipBytesUntilSequenceSubTask;
	readHttpParameterNameSubTask = _readHttpParameterNameSubTask;
	sendResponseSubTask = _sendResponseSubTask;

	readingMaxTime = _readingMaxTime;
	readingMaxBytesCount = _readingMaxBytesCount;

	serviceDescrptions = _serviceDescrptions;
	serviceDescrptionsCount = _serviceDescrptionsCount;

	arrayForSelectdServices = _arrayForSelectdServices;
	arrayForMatchServiceNames = _arrayForMatchServiceNames;

	leaveLastByteOfHttpHeaderInStream = _leaveLastByteOfHttpHeaderInStream;
}

// =================================================

void ReadHttpPathSubTask::setWork( bool _isGETHttpMethod )
{
	isGETHttpMethod = _isGETHttpMethod;
}

// =================================================

char* ReadHttpPathSubTask::getSubTaskName()
{
	return "ReadHttpPath-sub-task";
}

// =================================================

void ReadHttpPathSubTask::resetInternalState()
{
	static const char* prefix = "ReadHttpPathSubTask:resetInternalState():";

	alreadyReadBytesCount = 0;
	letterIndex = 0;
	thereWasAtLeastOneMatching = false;

	streamReadUntilByte.resetInternalState( (char*)stopBytes );

	for( int i = 0 ; i < serviceDescrptionsCount ; i++ )
	{
		setSelected( i , true );
		setCompletelyMatched( i , false );
	}

	startTime = millis();
}

// =================================================

RestServerSubTask* ReadHttpPathSubTask::executeSubTask( Stream* stream )
{
	static const char* prefix = "ReadHttpPathSubTask:executeSubTask():";

	while( alreadyReadBytesCount < readingMaxBytesCount && ( millis() - startTime < readingMaxTime ) )
	{
		if( stream->available() == 0 ) return NULL;

		int readByte = stream->read();

		if( readByte == -1 ) return NULL;

		alreadyReadBytesCount++;

		if( readByte == ' ' || readByte == '?' )
		{
			sumUpWorkOrOnlyWorkPart();

			// --------------

			bool sendResponseInJSON = isSelected( serviceDescrptionsCount -2 ) && isCompletelyMatched( serviceDescrptionsCount -2 );
			bool sendResponseAsServiceMetaDescription = isSelected( serviceDescrptionsCount -1 ) && isCompletelyMatched( serviceDescrptionsCount -1 );

			// --------------

			unsigned char selectedServicesCount = prepareSelectedServicesArray( !thereWasAtLeastOneMatching );

			// --------------

			sendResponseSubTask->setWork( isGETHttpMethod , sendResponseInJSON , sendResponseAsServiceMetaDescription , arrayForSelectdServices , selectedServicesCount );
			skipBytesUntilSequenceSubTask->setStopSequenceAndNextSubTask( "\r\n\r\n" , leaveLastByteOfHttpHeaderInStream , sendResponseSubTask );

			if( readByte == ' ' )
			{
				return skipBytesUntilSequenceSubTask;
			}
			else
			{
				readHttpParameterNameSubTask->setWork( skipBytesUntilSequenceSubTask );
				return readHttpParameterNameSubTask;
			}
		}
		else
		if( readByte == '/' )
		{
			sumUpWorkOrOnlyWorkPart();
			letterIndex = 0;
		}
		else
		if( readByte == '*' )
		{
			for( int i = 0 ; i < serviceDescrptionsCount - 2 ; i++ )
			{
				if( !isCompletelyMatched( i ) && isSelected( i ) )
				{
					setCompletelyMatched( i , true );
					all( p << prefix << "service '" << serviceDescrptions[i]->restService->name << "' was completely matched!" << endl; )
				}
			}

			letterIndex = 0;
		}
		else
		{
			for( int i = 0 ; i < serviceDescrptionsCount ; i++ )
			{
				if( !isCompletelyMatched( i ) )
				{
					if( isSelected( i ) )
					{
						if( serviceDescrptions[i]->restService->name[ letterIndex ] != readByte )
						{
							setSelected( i , false );
							all( p << prefix << "service '" << serviceDescrptions[i]->restService->name << "' not matching requested http path by user, setting as unselected, maybe it will be matched in next matching" << endl; )
						}
					}
				}
			}

			letterIndex++;
		}
	}

	return errorSubTask;
}

// =================================================

void ReadHttpPathSubTask::sumUpWorkOrOnlyWorkPart()
{
	static const char* prefix = "ReadHttpPathSubTask:sumUpWorkOrOnlyWorkPart():";

	bool isMatchedJsonOrMetadescription = false;

	for( int i = 0 ; i < serviceDescrptionsCount ; i++ )
	{
		if( isSelected( i ) )
		{
			if( !isCompletelyMatched( i ) )
			{
				if( serviceDescrptions[i]->restService->name[ letterIndex ] == 0 )
				{
					setCompletelyMatched( i , true );

					if( i >= serviceDescrptionsCount-2 ) isMatchedJsonOrMetadescription = true;

					all( p << prefix << "service '" << serviceDescrptions[i]->restService->name << "' was completely matched!" << endl; )
				}
			}
		}
	}

	for( int i = 0 ; i < serviceDescrptionsCount ; i++ )
	{
		if( !isMatchedJsonOrMetadescription && i < serviceDescrptionsCount-2 && !isSelected( i ) ) thereWasAtLeastOneMatching = true;
		setSelected( i , true );
	}
}

// =================================================

unsigned char ReadHttpPathSubTask::prepareSelectedServicesArray( bool addAllIfNoneWasSelectedDuringMatching )
{
	static const char* prefix = "ReadHttpPathSubTask:prepareSelectedServicesArray():";

	unsigned char addedSelectedServicesCount = 0;

	for( int i = 0 ; i < serviceDescrptionsCount - 2 ; i++ )
	{
		if( isSelected( i ) && isCompletelyMatched( i ) )
		{
			arrayForSelectdServices[addedSelectedServicesCount].restServiceRenderers = serviceDescrptions[i]->restServiceRenderers;
			arrayForSelectdServices[addedSelectedServicesCount].restService = serviceDescrptions[i]->restService;

			all( p << prefix << "service '" << arrayForSelectdServices[addedSelectedServicesCount].restService->name << "' was selected" << endl; )

			addedSelectedServicesCount++;
		}
	}

	if( addedSelectedServicesCount == 0 && addAllIfNoneWasSelectedDuringMatching )
	{
		all( p << prefix << "no service where selected so adding all services to be generated" << endl; )

		for( int i = 0 ; i < serviceDescrptionsCount - 2 ; i++ )
		{
			arrayForSelectdServices[i].restServiceRenderers = serviceDescrptions[i]->restServiceRenderers;
			arrayForSelectdServices[i].restService = serviceDescrptions[i]->restService;

			all( p << prefix << "service '" << arrayForSelectdServices[i].restService->name << "' was selected" << endl; )
		}

		addedSelectedServicesCount = serviceDescrptionsCount - 2;
	}

	all( p << prefix << "selected services count = " << addedSelectedServicesCount << " (of all " << (serviceDescrptionsCount-2) << " + json + metadescription)" << endl; )

	return addedSelectedServicesCount;
}

// =================================================

bool ReadHttpPathSubTask::isSelected( unsigned char index )
{
	return ( arrayForMatchServiceNames[ index ] & ReadHttpPathSubTask_IS_SELECTED ) == ReadHttpPathSubTask_IS_SELECTED;
}

// =================================================

void ReadHttpPathSubTask::setSelected( unsigned char index , bool isSelected )
{
	if( isSelected )
		arrayForMatchServiceNames[ index ] = arrayForMatchServiceNames[ index ] | ReadHttpPathSubTask_IS_SELECTED;
	else
		arrayForMatchServiceNames[ index ] = arrayForMatchServiceNames[ index ] & ~ReadHttpPathSubTask_IS_SELECTED;
}

// =================================================

bool ReadHttpPathSubTask::isCompletelyMatched( unsigned char index )
{
	return ( arrayForMatchServiceNames[ index ] & ReadHttpPathSubTask_IS_COMPLETELY_MATCHED ) == ReadHttpPathSubTask_IS_COMPLETELY_MATCHED;
}

// =================================================

void ReadHttpPathSubTask::setCompletelyMatched( unsigned char index , bool isCompletlyMatched )
{
	if( isCompletlyMatched )
		arrayForMatchServiceNames[ index ] = arrayForMatchServiceNames[ index ] | ReadHttpPathSubTask_IS_COMPLETELY_MATCHED;
	else
		arrayForMatchServiceNames[ index ] = arrayForMatchServiceNames[ index ] & ~ReadHttpPathSubTask_IS_COMPLETELY_MATCHED;
}

// =================================================

*/
