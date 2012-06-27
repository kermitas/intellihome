/*
 * SingleEthernetConnectionRestServerTask.cpp
 *
 *  Created on: 07-05-2012
 *      Author: root
 */
/*
// =================================================

#include "SingleEthernetConnectionRestServerTask.h"

// =================================================

SingleEthernetConnectionRestServerTask::SingleEthernetConnectionRestServerTask( Print& _p , EthernetServer* _serverSocket , ServiceDescription** serviceDescrptions , unsigned char serviceDescrptionsCount , bool _blockToServeIncommingConnectionToTheEnd , PageRenderer* htmlPageRenderer , PageRenderer* jsonPageRenderer , const char* jsonActivatorURLPrefix , const char* metadescriptionActivatorURLPrefix , ServiceDescription* readHttpPathSubTaskArrayForSelectdServices , unsigned char* readHttpPathSubTaskArrayForMatchServiceNames , bool* readHttpParameterNameSubTaskArrayForMatchServiceNames , unsigned char* readHttpParameterValueSubTaskArrayForValueBytes , unsigned char readHttpParameterValueSubTaskArrayForValueBytesSize , uint8_t* sendResponseSubTaskChunkedStreamBuffer , unsigned char sendResponseSubTaskChunkedStreamBufferSize ) : p(_p) , restServer( p , serviceDescrptions , serviceDescrptionsCount , htmlPageRenderer , jsonPageRenderer , jsonActivatorURLPrefix , metadescriptionActivatorURLPrefix , readHttpPathSubTaskArrayForSelectdServices , readHttpPathSubTaskArrayForMatchServiceNames , _blockToServeIncommingConnectionToTheEnd , readHttpParameterNameSubTaskArrayForMatchServiceNames , readHttpParameterValueSubTaskArrayForValueBytes , readHttpParameterValueSubTaskArrayForValueBytesSize , sendResponseSubTaskChunkedStreamBuffer , sendResponseSubTaskChunkedStreamBufferSize )
{
	serverSocket = _serverSocket;

	currentSock = -1;
}

// =================================================

void SingleEthernetConnectionRestServerTask::run()
{
	static const char* prefix = "SingleEthernetConnectionRestServerTask:run():";

	EthernetClient client = serverSocket->available();

	if( client )
	{
		all( p << prefix << "ethernet shield tells that socket " << client._sock << " is available to process" << endl; )

		if( client.connected() )
		{
			if( currentSock  == -1 ) currentSock = client._sock;

			if( currentSock == client._sock )
			{
				processClient( &client );

				//delay( 100 ); // tutaj sztuczne spowolnienie akcji
			}
			else
			{
				warning( p << prefix << "socket " << client._sock << " will be not processed because already processing " << (int)currentSock << " socket, closing" << endl; )
				client.stop();
			}
		}
		else
		{
			warning( p << prefix << "socket " << client._sock << " not connected, closing" << endl; )
			client.stop();

			if( currentSock == client._sock ) currentSock = -1;
		}
	}
}

// =================================================

void SingleEthernetConnectionRestServerTask::processClient( EthernetClient* client )
{
	static const char* prefix = "SingleEthernetConnectionRestServerTask:processClient():";

	all( p << prefix << "processing socket " << client->_sock << endl; )



		//if( client->_sock >= 0 && client->_sock < 4 )
		//{
			if( restServer.processStream( client ) )
			{
				all( p << prefix << "all operations finished, closing socket " << client->_sock << endl; )
				client->stop();
				currentSock = -1;
			}
			else
			{
				all( p << prefix << "socket " << client->_sock << " will be also processed in the future" << endl; )
			}

		//}
		//else
		//{
		//	warning( p << prefix << "unknown socket _sock number (" << client->_sock << "), closing socket without any actions" << endl; )
		//	client->stop();
		//}
	//}
}
*/
// =================================================


