/*
 * RestServerTask.cpp
 *
 *  Created on: 10-04-2012
 *      Author: root
 */

/*
// =================================================

#include "RestServerTask.h"

// =================================================

RestServerTask::RestServerTask( Print& _p , EthernetServer* _serverSocket , ServiceDescription** serviceDescrptions , unsigned char serviceDescrptionsCount , bool _blockToServeIncommingConnectionToTheEnd , PageRenderer* htmlPageRenderer , PageRenderer* jsonPageRenderer , const char* jsonActivatorURLPrefix , const char* metadescriptionActivatorURLPrefix , ServiceDescription** readHttpPathSubTaskArrayForSelectdServices , unsigned char** readHttpPathSubTaskArrayForMatchServiceNames , bool** readHttpParameterNameSubTaskArrayForMatchServiceNames , unsigned char** readHttpParameterValueSubTaskArrayForValueBytes , unsigned char readHttpParameterValueSubTaskArrayForValueBytesSize , uint8_t** sendResponseSubTaskChunkedStreamBuffer , unsigned char sendResponseSubTaskChunkedStreamBufferSize ) : p(_p) , restServerForConnection0( p , serviceDescrptions , serviceDescrptionsCount , htmlPageRenderer , jsonPageRenderer , jsonActivatorURLPrefix , metadescriptionActivatorURLPrefix , readHttpPathSubTaskArrayForSelectdServices[0] , readHttpPathSubTaskArrayForMatchServiceNames[0] , _blockToServeIncommingConnectionToTheEnd , readHttpParameterNameSubTaskArrayForMatchServiceNames[0] , readHttpParameterValueSubTaskArrayForValueBytes[0] , readHttpParameterValueSubTaskArrayForValueBytesSize , sendResponseSubTaskChunkedStreamBuffer[0] , sendResponseSubTaskChunkedStreamBufferSize ) , restServerForConnection1( p , serviceDescrptions , serviceDescrptionsCount , htmlPageRenderer , jsonPageRenderer , jsonActivatorURLPrefix , metadescriptionActivatorURLPrefix , readHttpPathSubTaskArrayForSelectdServices[1] , readHttpPathSubTaskArrayForMatchServiceNames[1] , _blockToServeIncommingConnectionToTheEnd , readHttpParameterNameSubTaskArrayForMatchServiceNames[1] , readHttpParameterValueSubTaskArrayForValueBytes[1] , readHttpParameterValueSubTaskArrayForValueBytesSize , sendResponseSubTaskChunkedStreamBuffer[1] , sendResponseSubTaskChunkedStreamBufferSize ) , restServerForConnection2( p , serviceDescrptions , serviceDescrptionsCount , htmlPageRenderer , jsonPageRenderer , jsonActivatorURLPrefix , metadescriptionActivatorURLPrefix , readHttpPathSubTaskArrayForSelectdServices[2] , readHttpPathSubTaskArrayForMatchServiceNames[2] , _blockToServeIncommingConnectionToTheEnd , readHttpParameterNameSubTaskArrayForMatchServiceNames[2] , readHttpParameterValueSubTaskArrayForValueBytes[2] , readHttpParameterValueSubTaskArrayForValueBytesSize , sendResponseSubTaskChunkedStreamBuffer[2] , sendResponseSubTaskChunkedStreamBufferSize ) , restServerForConnection3( p , serviceDescrptions , serviceDescrptionsCount , htmlPageRenderer , jsonPageRenderer , jsonActivatorURLPrefix , metadescriptionActivatorURLPrefix , readHttpPathSubTaskArrayForSelectdServices[3] , readHttpPathSubTaskArrayForMatchServiceNames[3] , _blockToServeIncommingConnectionToTheEnd , readHttpParameterNameSubTaskArrayForMatchServiceNames[3] , readHttpParameterValueSubTaskArrayForValueBytes[3] , readHttpParameterValueSubTaskArrayForValueBytesSize , sendResponseSubTaskChunkedStreamBuffer[3] , sendResponseSubTaskChunkedStreamBufferSize )
{
	serverSocket = _serverSocket;
	//blockToServeIncommingConnectionToTheEnd = _blockToServeIncommingConnectionToTheEnd;

	restServerForConnection[0] = &restServerForConnection0;
	restServerForConnection[1] = &restServerForConnection1;
	restServerForConnection[2] = &restServerForConnection2;
	restServerForConnection[3] = &restServerForConnection3;
}

// =================================================

void RestServerTask::run()
{
	static const char* prefix = "RestServerTask:run():";

	EthernetClient client = serverSocket->available();

	if( client )
	{
		all( p << prefix << "ethernet shield tells that socket " << client._sock << " is available to process" << endl; )

		if( client.connected() )
		{
			processClient( &client );
		}
		else
		{
			warning( p << prefix << "socket " << client._sock << " not connected, closing" << endl; )
			client.stop();
		}
	}
}

// =================================================

void RestServerTask::processClient( EthernetClient* client )
{
	static const char* prefix = "RestServerTask:processClient():";

	all( p << prefix << "processing socket " << client->_sock << endl; )


	if( client->_sock >= 0 && client->_sock < 4 )
	{
		if( restServerForConnection[client->_sock]->processStream( client ) )
		{
			all( p << prefix << "all operations finished, closing socket " << client->_sock << endl; )
			client->stop();
		}
		else
		{
			all( p << prefix << "socket " << client->_sock << " will be also processed in the future" << endl; )
		}

	}
	else
	{
		warning( p << prefix << "unknown socket _sock number (" << client->_sock << "), closing socket without any actions" << endl; )
		client->stop();
	}

}
*/
// =================================================


