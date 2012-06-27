/*
 * SingleEthernetConnectionRestServerTask.h
 *
 *  Created on: 07-05-2012
 *      Author: root
 */
/*
#ifndef SINGLEETHERNETCONNECTIONRESTSERVERTASK_H_
#define SINGLEETHERNETCONNECTIONRESTSERVERTASK_H_

// =================================================

#include <Arduino.h>
#include <Print.h>
#include <Ethernet.h>

// =================================================

#include "Configuration.c"
#include "Runnable.h"
#include "RestServer.h"
#include "Streaming.h"

#include "RestServer.h"

// =================================================

class SingleEthernetConnectionRestServerTask: public Runnable
{
	public:

		SingleEthernetConnectionRestServerTask( Print& _p , EthernetServer* _serverSocket , ServiceDescription** serviceDescrptions , unsigned char serviceDescrptionsCount , bool _blockToServeIncommingConnectionToTheEnd , PageRenderer* htmlPageRenderer , PageRenderer* jsonPageRenderer , const char* jsonActivatorURLPrefix , const char* metadescriptionActivatorURLPrefix , ServiceDescription* readHttpPathSubTaskArrayForSelectdServices , unsigned char* readHttpPathSubTaskArrayForMatchServiceNames , bool* readHttpParameterNameSubTaskArrayForMatchServiceNames , unsigned char* readHttpParameterValueSubTaskArrayForValueBytes , unsigned char readHttpParameterValueSubTaskArrayForValueBytesSize , uint8_t* sendResponseSubTaskChunkedStreamBuffer , unsigned char sendResponseSubTaskChunkedStreamBufferSize );
		void run();

	protected:

		Print& p;

		EthernetServer* serverSocket;
		RestServer restServer;

		char currentSock;

		void processClient( EthernetClient* client );
};

// =================================================

#endif*/ /* SINGLEETHERNETCONNECTIONRESTSERVERTASK_H_ */
