/*
 * RestServer.cpp
 *
 *  Created on: 10-04-2012
 *      Author: root
 */

// =================================================

/*
 TODO

wycofac one time execution na rzecz po prostu booleanowego typu

generator strony HTMLowej niech bierze do konstruktora wskaznik na napis, ktory zostanie wyswietlony na samej gorze jako tytul

dodac serwis, gdzie bedzie nazwa tego urzadzenia typu "Satelita1"

ten sub task zczytujacy http path czyta jedna sciezke tylko i po "&" zwraca samego siebie, a po spacji nastepnego taska

w htmlowym widoku moze dodac kolumne z typem danych? ze to jest typ danych bool, a tamto uint8, a inne uint16 ?

w htmlowym widoku (a takze w metadescription) dodac cos takiego jak wyswietlanie description tego serwisu

 */

// =================================================

#include "RestServer.h"

// =================================================

RestServer::RestServer( ServiceDescription** _serviceDescrptions , unsigned char _serviceDescrptionsCount , PageRenderer* _htmlPageRenderer , PageRenderer* _jsonPageRenderer , const char* jsonActivatorURLPrefix , const char* metadescriptionActivatorURLPrefix , ServiceDescription* readHttpPathSubTaskArrayForSelectdServices , bool _blockToServeIncommingConnectionToTheEnd , bool* readHttpParameterNameSubTaskArrayForMatchServiceNames , unsigned char* readHttpParameterValueSubTaskArrayForValueBytes , unsigned char readHttpParameterValueSubTaskArrayForValueBytesSize , AnyBuffer< byte , byte >* sendResponseSubTaskChunkedStreamBuffer , char* _buffer , unsigned char _bufferSize )
	: dp( PSTR( "RestServer" ) ) , //, DEBUG_LEVEL_ALL ) ,
	  skipBytesUntilSequenceSubTask( &errorSubTask ) ,
	  sendResponseSubTask( &errorSubTask , _htmlPageRenderer , _jsonPageRenderer , !_blockToServeIncommingConnectionToTheEnd , sendResponseSubTaskChunkedStreamBuffer ) ,
	  readHttpParameterValueSubTask( &errorSubTask , MAX_TIME_FOR_READING_HTTP_PARAMETER_VALUE , readHttpParameterValueSubTaskArrayForValueBytes , readHttpParameterValueSubTaskArrayForValueBytesSize ) ,
	  readHttpParameterNameSubTask( &errorSubTask , MAX_TIME_FOR_READING_HTTP_PARAMETER_NAME , MAX_BYTES_COUNT_WHILE_READING_HTTP_PARAMETER_NAME , _serviceDescrptions , _serviceDescrptionsCount-2 , readHttpParameterNameSubTaskArrayForMatchServiceNames , &readHttpParameterValueSubTask ) ,
	  readHttpPathSubTask( &errorSubTask , &skipBytesUntilSequenceSubTask , &readHttpParameterNameSubTask , &sendResponseSubTask , _serviceDescrptions , _serviceDescrptionsCount , readHttpPathSubTaskArrayForSelectdServices , !_blockToServeIncommingConnectionToTheEnd , _buffer , _bufferSize) ,
	  determinateHttpMethodSubTask( &errorSubTask , &skipBytesUntilSequenceSubTask , &readHttpPathSubTask ) ,
	  jsonActivatorRestService( 255 , jsonActivatorURLPrefix , 0 ) ,
	  metadescriptionActivatorRestService( 255 , metadescriptionActivatorURLPrefix , 0 )
{
	blockToServeIncommingConnectionToTheEnd = _blockToServeIncommingConnectionToTheEnd;

	jsonServiceDescription.restService = &jsonActivatorRestService;

	metadescriptionServiceDescription.restService = &metadescriptionActivatorRestService;

	_serviceDescrptions[ _serviceDescrptionsCount - 2 ] = &jsonServiceDescription;
	_serviceDescrptions[ _serviceDescrptionsCount - 1 ] = &metadescriptionServiceDescription;

	errorSubTaskPtr = &errorSubTask;

	streamReadBytesCountingPtr = &streamReadBytesCounting;

	resetInternalState();
}

// =================================================

void RestServer::resetInternalState()
{
	currentSubTask = &determinateHttpMethodSubTask;
	currentSubTask->resetInternalState();

	streamReadBytesCounting.resetInternalState();
	isTimeoutWatcherStarted = false;
}

// =================================================

bool RestServer::processStream( Stream* stream )
{
	static const PROGMEM prog_char functionName[] = "processStream";
	//static const char* prefix = "RestServer:processStream():";

	//static const unsigned int timeoutInSeconds = 10; // todo to ma byc jako parametr przekazany do konstruktora

	//all( p << prefix << "beginning work, executing '" << currentSubTask->getSubTaskName() << "' sub-task" << endl; )
	aln( "beginning work, executing '%s' sub-task" , currentSubTask->getSubTaskName() )

	streamReadBytesCounting.setStream( stream );

	if( blockToServeIncommingConnectionToTheEnd )
	{
		while( true )
		{
			if( isTimeoutWatcherStarted && ( millis() - startTime ) > MAX_TIME_FOR_PROCESS_INCOMMING_HTTP_REQUEST )
			{
				//warning( p << prefix << "timeout while processing this request" << endl; )
				wln( "timeout while processing this request" )

				break;
			}

			if( streamReadBytesCounting.getReadBytesCount() > MAX_BYTES_COUNT_OF_INCOMMING_HTTP_REQUEST )
			{
				//warning( p << prefix << "http request max bytes reached while processing this request" << endl; )
				wln( "http request max bytes reached while processing this request" )

				break;
			}

			RestServerSubTask* newSubTask = currentSubTask->executeSubTask( streamReadBytesCountingPtr );

			if( newSubTask != NULL )
			{
				//all( p << prefix << "finishing work"; )

				if( newSubTask == errorSubTaskPtr )
				{
					//warning( p << prefix << "finishing work, already executed '" << currentSubTask->getSubTaskName() << "' sub-task asked to reset internal state (future execution will start state machine from beginning)" << endl; )
					wln( "finishing work, already executed '%s' sub-task asked to reset internal state (future execution will start state machine from beginning)" , currentSubTask->getSubTaskName() )

					break;
				}
				else
				{
					//all( p << prefix << "finishing work, changing already executed '" << currentSubTask->getSubTaskName() << "' sub-task to '" << newSubTask->getSubTaskName() << "'" << endl; )
					aln( "finishing work, changing already executed '%s' sub-task to '%s'" , currentSubTask->getSubTaskName() , newSubTask->getSubTaskName() )

					currentSubTask = newSubTask;
					currentSubTask->resetInternalState();

					if( !isTimeoutWatcherStarted )
					{
						isTimeoutWatcherStarted = true;
						startTime = millis();
						iln( "start time counter" )
					}
				}
			}
			else
			{
				//all( p << ", during next execution there will be continuation of current sub-task ('" << currentSubTask->getSubTaskName() << "')" << endl; )
				aln( "during next execution there will be continuation of current sub-task ('%s')" , currentSubTask->getSubTaskName() )
			}
		}

		resetInternalState();
		return true;
	}
	else
	{
		if( isTimeoutWatcherStarted && ( ( millis() - startTime ) ) > MAX_TIME_FOR_PROCESS_INCOMMING_HTTP_REQUEST )
		{
			//warning( p << prefix << "timeout while processing this request" << endl; )
			wln( "timeout while processing this request" )

			resetInternalState();
			return true;
		}

		if( streamReadBytesCounting.getReadBytesCount() > MAX_BYTES_COUNT_OF_INCOMMING_HTTP_REQUEST )
		{
			//warning( p << prefix << "http request max bytes reached while processing this request" << endl; )
			wln( "http request max bytes reached while processing this request" )

			resetInternalState();
			return true;
		}

		RestServerSubTask* newSubTask = currentSubTask->executeSubTask( streamReadBytesCountingPtr );

		if( newSubTask != NULL )
		{
			//all( p << prefix << "finishing work"; )

			if( newSubTask == errorSubTaskPtr )
			{
				//warning( p << prefix << "finishing work, already executed '" << currentSubTask->getSubTaskName() << "' sub-task asked to reset internal state (future execution will start state machine from beginning)" << endl; )
				wln( "finishing work, already executed '%s' sub-task asked to reset internal state (future execution will start state machine from beginning)" , currentSubTask->getSubTaskName() )

				resetInternalState();
				return true;
			}
			else
			{
				//info( p << prefix << "finishing work, changing already executed '" << currentSubTask->getSubTaskName() << "' sub-task to '" << newSubTask->getSubTaskName() << "'" << endl; )
				aln( "finishing work, changing already executed '%s' sub-task to '%s'" , currentSubTask->getSubTaskName() , newSubTask->getSubTaskName() )

				currentSubTask = newSubTask;
				currentSubTask->resetInternalState();

				if( !isTimeoutWatcherStarted )
				{
					isTimeoutWatcherStarted = true;
					startTime = millis();

					//info( p << prefix << "start time counter" << endl; )
					aln( "start time counter" )
				}

				return false;
			}
		}
		else
		{
			//all( p << ", during next execution there will be continuation of current sub-task ('" << currentSubTask->getSubTaskName() << "')" << endl; )
			aln( "during next execution there will be continuation of current sub-task ('%s')" , currentSubTask->getSubTaskName() )

			return false;
		}
	}
}

// =================================================

