/*
 * RS232ToWiFiTask.cpp
 *
 *  Created on: 07-05-2012
 *      Author: root
 */

// =================================================

#include "RS232ToWiFiTask.h"

// =================================================

RS232ToWiFiTask::RS232ToWiFiTask( ServiceDescription** serviceDescrptions , unsigned char serviceDescrptionsCount , bool _blockToServeIncommingConnectionToTheEnd , PageRenderer* htmlPageRenderer , PageRenderer* jsonPageRenderer , const char* jsonActivatorURLPrefix , const char* metadescriptionActivatorURLPrefix , ServiceDescription* readHttpPathSubTaskArrayForSelectdServices , bool* readHttpParameterNameSubTaskArrayForMatchServiceNames , unsigned char* readHttpParameterValueSubTaskArrayForValueBytes , unsigned char readHttpParameterValueSubTaskArrayForValueBytesSize , AnyBuffer< byte , byte >* sendResponseSubTaskChunkedStreamBuffer , char* _buffer , unsigned char _bufferSize , Stream* _stream )
	: dp( PSTR( "RS232ToWiFiTask" ) ) ,
	  restServer( serviceDescrptions , serviceDescrptionsCount , htmlPageRenderer , jsonPageRenderer , jsonActivatorURLPrefix , metadescriptionActivatorURLPrefix , readHttpPathSubTaskArrayForSelectdServices , _blockToServeIncommingConnectionToTheEnd , readHttpParameterNameSubTaskArrayForMatchServiceNames , readHttpParameterValueSubTaskArrayForValueBytes , readHttpParameterValueSubTaskArrayForValueBytesSize , sendResponseSubTaskChunkedStreamBuffer , _buffer , _bufferSize )
	  //streamHFA11xRS232WiFi( _incommingByteBufferForStreamHFA11xRS232WiFi , _outgoingByteBufferForStreamHFA11xRS232WiFi , 2 , 2 )
{
	//streamReadBytesCountingPtr = &streamReadBytesCounting;
	//streamHFA11xRS232WiFiPtr = &streamHFA11xRS232WiFi;
	stream = _stream;
}

// =================================================

void RS232ToWiFiTask::run()
{
	static const PROGMEM prog_char functionName[] = "run";
	//static const char* prefix = "RS232ToWiFiTask:run():";

	/*
	while( stream->available() > 0 )
	{
		int c = stream->read();
		if( c == -1 ) break;
		info( p << prefix << "received : " << (char)c << endl; )
		stream->write( c );
	}*/

	//if( stream->available() > 0 )
	//{
		//info( p << prefix << "processing RS232<->WiFi, available bytes = " << stream->available() << endl; )

	//static const unsigned int readBytesCountLimit = 65535; // todo to ma byc jako parametr przekazany do konstruktora
	//static const unsigned int timeoutInSeconds = 10; // todo to ma byc jako parametr przekazany do konstruktora

	//if( streamReadBytesCounting.getReadBytesCount() < readBytesCountLimit )
	//{
		//if( restServer.processStream( streamHFA11xRS232WiFiPtr ) )
		if( restServer.processStream( stream ) )
		{
			//info( p << prefix << "all operations finished on RS232<->WiFi" << endl; )
			aln( "all operations finished on RS232<->WiFi" )

			//stream->write( -1 );
			//stream->write( -1 );
			//streamReadBytesCounting.setStreamAndResetInternalState( streamReadBytesCounting.mainStream );
		}
		else
		{
			//info( p << prefix << "RS232<->WiFi connection will be also processed in the future" << endl; )
			aln( "RS232<->WiFi connection will be also processed in the future" )
		}
	//}
	//else
	//{
	//	warning( p << prefix << "maximum read bytes count reached!" << endl; )
	//	streamReadBytesCounting.setStreamAndResetInternalState( streamReadBytesCounting.mainStream );
	//}
	//}
}

// =================================================

//void RS232ToWiFiTask::setStream( Stream* _stream )
//{
//	stream = _stream;
	//streamHFA11xRS232WiFi.setStream( _stream );
	//mainStream = &streamHFA11xRS232WiFi;

	//mainStream = _stream;
	//streamReadBytesCounting.setStreamAndResetInternalState( _stream );
//}

// =================================================


