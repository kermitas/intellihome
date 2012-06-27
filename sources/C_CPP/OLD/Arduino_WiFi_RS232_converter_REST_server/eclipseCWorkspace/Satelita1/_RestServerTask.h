/*
 * RestServerTask.h
 *
 *  Created on: 10-04-2012
 *      Author: root
 */

/*
#ifndef RESTSERVERTASK_H_
#define RESTSERVERTASK_H_

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

class RestServerTask: public Runnable
{
	public:

		RestServerTask( Print& _p , EthernetServer* _serverSocket , ServiceDescription** serviceDescrptions , unsigned char serviceDescrptionsCount , bool _blockToServeIncommingConnectionToTheEnd , PageRenderer* htmlPageRenderer , PageRenderer* jsonPageRenderer , const char* jsonActivatorURLPrefix , const char* metadescriptionActivatorURLPrefix , ServiceDescription** readHttpPathSubTaskArrayForSelectdServices , unsigned char** readHttpPathSubTaskArrayForMatchServiceNames , bool** readHttpParameterNameSubTaskArrayForMatchServiceNames , unsigned char** readHttpParameterValueSubTaskArrayForValueBytes , unsigned char readHttpParameterValueSubTaskArrayForValueBytesSize , uint8_t** sendResponseSubTaskChunkedStreamBuffer , unsigned char sendResponseSubTaskChunkedStreamBufferSize );
		void run();

	protected:

		Print& p;

		EthernetServer* serverSocket;
		RestServer restServerForConnection0, restServerForConnection1, restServerForConnection2, restServerForConnection3;

		RestServer* restServerForConnection[4];

		void processClient( EthernetClient* client );
};

// =================================================

#endif *//* RESTSERVERTASK_H_ */
