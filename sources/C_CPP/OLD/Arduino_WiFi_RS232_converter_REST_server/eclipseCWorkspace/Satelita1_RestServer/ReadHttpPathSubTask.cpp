/*
 * ReadHttpPathSubTask.cpp
 *
 *  Created on: 22-04-2012
 *      Author: root
 */

// =================================================

#include "ReadHttpPathSubTask.h"

// =================================================

//const PROGMEM prog_char ReadHttpPathSubTask::className[] = "ReadHttpPathSubTask";
const char* ReadHttpPathSubTask::stopBytes = " /?*";
const char* ReadHttpPathSubTask::endOfHttpHeader = "\r\n\r\n";

// =================================================

ReadHttpPathSubTask::ReadHttpPathSubTask( RestServerSubTask* _errorSubTask , SkipBytesUntilSequenceSubTask* _skipBytesUntilSequenceSubTask , ReadHttpParameterNameSubTask* _readHttpParameterNameSubTask , SendResponseSubTask* _sendResponseSubTask , ServiceDescription** _serviceDescrptions , unsigned char _serviceDescrptionsCount , ServiceDescription* _arrayForSelectdServices , bool _leaveLastByteOfHttpHeaderInStream , char* _buffer , unsigned char _bufferSize )
	: dp( PSTR( "ReadHttpPathSubTask" ) ) ,
	  streamReadUntilByte( _buffer , _bufferSize )
{
	errorSubTask = _errorSubTask;
	skipBytesUntilSequenceSubTask = _skipBytesUntilSequenceSubTask;
	readHttpParameterNameSubTask = _readHttpParameterNameSubTask;
	sendResponseSubTask = _sendResponseSubTask;

	//readingMaxTime = _readingMaxTime;
	//readingMaxBytesCount = _readingMaxBytesCount;

	serviceDescrptions = _serviceDescrptions;
	serviceDescrptionsCount = _serviceDescrptionsCount;

	arrayForSelectdServices = _arrayForSelectdServices;
	//arrayForMatchServiceNames = _arrayForMatchServiceNames;

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
	static const PROGMEM prog_char functionName[] = "resetInternalState";
	//static const char* prefix = "ReadHttpPathSubTask:resetInternalState():";

	//alreadyReadBytesCount = 0;
	//letterIndex = 0;
	//thereWasAtLeastOneMatching = false;

	streamReadUntilByte.resetInternalState( (char*)stopBytes );

	selectedServicesArrayIndex = 0;
	responseType = 0;
	thereWasAtLeastOneMatching = false;

	/*
	for( int i = 0 ; i < serviceDescrptionsCount ; i++ )
	{
		setSelected( i , true );
		setCompletelyMatched( i , false );
	}

	startTime = millis();*/
}

// =================================================

RestServerSubTask* ReadHttpPathSubTask::executeSubTask( Stream* stream )
{
	static const PROGMEM prog_char functionName[] = "executeSubTask";
	//static const char* prefix = "ReadHttpPathSubTask:executeSubTask():";

	streamReadUntilByte.setStream( stream );

	int streamReadUntilResult;

	while( ( streamReadUntilResult = streamReadUntilByte.read() ) == 0 ){}

	if( streamReadUntilResult == -1 )
	{
		//info( p << prefix << "streamReadUntilResult = -1" << endl; )
		//info( wpln( "streamReadUntilResult = -1" ) )
		iln( "streamReadUntilResult = -1" )

		return NULL;
	}
	else
	{
		//info( p << prefix << "streamReadUntilResult = '" << (char)streamReadUntilResult << "'" << endl; )
		//info( wpln( "streamReadUntilResult = '%s'" , streamReadUntilResult ) )
		iln( "streamReadUntilResult = '%c'" , streamReadUntilResult )

		if( streamReadUntilResult == ' ' || streamReadUntilResult == '?' )
		{
			addMatchedServicesToSelectedServicesArray( false );

			if( selectedServicesArrayIndex == 0 && !thereWasAtLeastOneMatching )
			{
				//info( p << prefix << "adding all services because there were no selected services" << endl; )
				//info( wpln( "adding all services because there were no selected services" ) )
				iln( "adding all services because there were no selected services" )

				allAllServicesToSelectedServicesArray();
			}

			sendResponseSubTask->setWork( isGETHttpMethod , responseType == 1 , responseType == 2 , arrayForSelectdServices , selectedServicesArrayIndex );
			//skipBytesUntilSequenceSubTask->setStopSequenceAndNextSubTask( "\r\n\r\n" , leaveLastByteOfHttpHeaderInStream , sendResponseSubTask );
			skipBytesUntilSequenceSubTask->setStopSequenceAndNextSubTask( (char*)endOfHttpHeader , leaveLastByteOfHttpHeaderInStream , sendResponseSubTask );
			//skipBytesUntilSequenceSubTask->setStopSequenceAndNextSubTask( "\r\n\r\n" , false , sendResponseSubTask ); // todo leaveLastByteOfHttpHeaderInStream !!

			if( streamReadUntilResult == ' ' )
			{
				return skipBytesUntilSequenceSubTask;
			}
			else
			if( streamReadUntilResult == '?' )
			{
				readHttpParameterNameSubTask->setWork( skipBytesUntilSequenceSubTask );
				return readHttpParameterNameSubTask;
			}
		}
		else
		if( streamReadUntilResult == '/' )
		{
			addMatchedServicesToSelectedServicesArray( false );
			streamReadUntilByte.resetInternalState( (char*)stopBytes );
			return NULL;
		}
		else
		if( streamReadUntilResult == '*' )
		{
			addMatchedServicesToSelectedServicesArray( true );
			streamReadUntilByte.resetInternalState( (char*)stopBytes );
			return NULL;
		}
		//else
		//{
		//	warning( p << prefix << "unknown result '" << (char)streamReadUntilResult << "' from streamReadUntilByte.read()" << endl; )
		//	return errorSubTask;
		//}
	}

	//warning( p << prefix << "code should not never reach this place, streamReadUntilResult='" << (char)streamReadUntilResult << "'" << endl; )
	//warning( wpln( "code should not never reach this place, streamReadUntilResult='%s'" , streamReadUntilResult ) )
	wln( "code should not never reach this place, streamReadUntilResult='%s'" , streamReadUntilResult )

	return errorSubTask;

	/*
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
	*/
}

// =================================================

void ReadHttpPathSubTask::addMatchedServicesToSelectedServicesArray( bool matchByStartsWith )
{
	for( int i = 0 ; i < serviceDescrptionsCount ; i++ )
	{
		if( ( !matchByStartsWith && compareStrings( (char*)serviceDescrptions[i]->restService->name , streamReadUntilByte.buffer ) ) || ( matchByStartsWith && isStringStartsWith( (char*)serviceDescrptions[i]->restService->name , streamReadUntilByte.buffer ) ) )
		{
			addToSelectedServicesArray( i );
		}
		else
		{
			//if( i < serviceDescrptionsCount - 2 ) thereWasAtLeastOneMatching = true; // todo potem to odblokowac i zakodowac poprawnie
		}
	}
}

// =================================================

void ReadHttpPathSubTask::allAllServicesToSelectedServicesArray()
{
	for( int i = 0 ; i < serviceDescrptionsCount - 2 ; i++ )
	{
		arrayForSelectdServices[ i ].restServiceRenderers = serviceDescrptions[ i ]->restServiceRenderers;
		arrayForSelectdServices[ i ].restService = serviceDescrptions[ i ]->restService;

		selectedServicesArrayIndex++;
	}

	selectedServicesArrayIndex = serviceDescrptionsCount - 2;
}

// =================================================

bool ReadHttpPathSubTask::isStringStartsWith( char* str , char* startsWith )
{
	static const PROGMEM prog_char functionName[] = "executeSubTask";
	//all( wp( "isStringStartsWith():str = '%s', startsWith = '%s', result = " , str , startsWith ) )
	a( "isStringStartsWith():str = '%s', startsWith = '%s', result = " , str , startsWith )

	for( unsigned char i = 0 ; startsWith[i] != 0 ; i++ )
	{
		if( str[i] != startsWith[i] || str[i] == 0 )
		{
			//all( p << "ReadHttpPathSubTask::isStringStartsWith():str='" << str << "', startsWith='" << startsWith << "', result = false" << endl; )
			//all( wpln( "false" ) )
			aln( "false" )

			return false;
		}
	}

	//all( p << "ReadHttpPathSubTask::isStringStartsWith():str='" << str << "', startsWith='" << startsWith << "', result = true" << endl; )
	//all( wpln( "true" ) )
	aln( "true" )

	return true;
}

// =================================================

bool ReadHttpPathSubTask::compareStrings( char* str1 , char* str2 )
{
	static const PROGMEM prog_char functionName[] = "compareStrings";
	//all( wp( "isStringStartsWith():str1 = '%s', str2 = '%s', result = " , str1 , str2 ) )
	a( "isStringStartsWith():str1 = '%s', str2 = '%s', result = " , str1 , str2 )

	unsigned char i = 0 ;

	while(  true )
	{
		if( str1[i] != str2[i] )
		{
			//all( p << "ReadHttpPathSubTask::compareStrings():str1='" << str1 << "', str2='" << str2 << "', result = false" << endl; )
			//all( wpln( "false" ) )
			aln( "false" )

			return false;
		}

		if( str1[i] == 0 ) break;

		i++;
	}

	//all( p << "ReadHttpPathSubTask::compareStrings():str1='" << str1 << "', str2='" << str2 << "', result = true" << endl; )
	//all( wpln( "true" ) )
	aln( "true" )

	return true;
}

// =================================================

bool ReadHttpPathSubTask::isInSelectedServicesArray( unsigned char selectedServiceIndex )
{
	for( unsigned char i = 0 ; i < serviceDescrptionsCount - 2 ; i++ )
	{
		if( arrayForSelectdServices[ i ].restService == serviceDescrptions[ selectedServiceIndex ]->restService ) return true;
	}

	return false;
}

// =================================================

void ReadHttpPathSubTask::addToSelectedServicesArray( unsigned char selectedServiceIndex )
{
	if( selectedServiceIndex == serviceDescrptionsCount - 1 )
	{
		responseType = 2;
	}
	else
	if( selectedServiceIndex == serviceDescrptionsCount - 2 )
	{
		responseType = 1;
	}
	else
	{
		if( !isInSelectedServicesArray( selectedServiceIndex ) )
		{
			arrayForSelectdServices[ selectedServicesArrayIndex ].restServiceRenderers = serviceDescrptions[ selectedServiceIndex ]->restServiceRenderers;
			arrayForSelectdServices[ selectedServicesArrayIndex ].restService = serviceDescrptions[ selectedServiceIndex ]->restService;

			selectedServicesArrayIndex++;
		}
	}
}

// =================================================
/*
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
*/
// =================================================
