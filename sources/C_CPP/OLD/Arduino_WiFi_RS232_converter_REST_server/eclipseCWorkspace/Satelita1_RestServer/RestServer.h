/*
 * RestServer.h
 *
 *  Created on: 10-04-2012
 *      Author: root
 */

#ifndef RESTSERVER_H_
#define RESTSERVER_H_

// =================================================

#include <Arduino.h>
#include <Print.h>
#include <Stream.h>

// =================================================

#include "DebugPrinter.h"
//#include "Configuration.c"
//#include "Streaming.h"


#include "RestServerCommon.h"

#include "RestService.h"
//#include "RestServiceRenderer.h"
#include "PageRenderer.h"
//#include "JSONPageRenderer.h"

#include "ErrorSubTask.h"
#include "DeterminateHttpMethodSubTask.h"
#include "SkipBytesUntilSequenceSubTask.h"
#include "ReadHttpPathSubTask.h"
#include "SendResponseSubTask.h"
#include "ReadHttpParameterNameSubTask.h"
#include "ReadHttpParameterValueSubTask.h"
#include "StreamReadBytesCounting.h"
#include "AnyBuffer.h"

// =================================================

class RestServer
{
	public:

		RestServer( ServiceDescription** _serviceDescrptions , unsigned char _serviceDescrptionsCount , PageRenderer* _htmlPageRenderer , PageRenderer* _jsonPageRenderer , const char* jsonActivatorURLPrefix , const char* metadescriptionActivatorURLPrefix , ServiceDescription* readHttpPathSubTaskArrayForSelectdServices , bool _blockToServeIncommingConnectionToTheEnd , bool* readHttpParameterNameSubTaskArrayForMatchServiceNames , unsigned char* readHttpParameterValueSubTaskArrayForValueBytes , unsigned char readHttpParameterValueSubTaskArrayForValueBytesSize , AnyBuffer< byte , byte >* sendResponseSubTaskChunkedStreamBuffer , char* _buffer , unsigned char _bufferSize );

		bool processStream( Stream* stream );
			// true - stream processed (read -> parse -> execute business logic -> send response) and can be closed
			// false - stream during parsing, please check if stream is connected and execute this function again

	protected:

		//Print& p;
		DebugPrinter dp;

		bool blockToServeIncommingConnectionToTheEnd;

		// ---

		RestService jsonActivatorRestService;
		ServiceDescription jsonServiceDescription;

		// ---

		RestService metadescriptionActivatorRestService;
		ServiceDescription metadescriptionServiceDescription;

		// ---

		ErrorSubTask errorSubTask;
		ErrorSubTask* errorSubTaskPtr;

		// ---

		RestServerSubTask* currentSubTask;

		// ---

		SkipBytesUntilSequenceSubTask skipBytesUntilSequenceSubTask;
		SendResponseSubTask sendResponseSubTask;
		ReadHttpParameterValueSubTask readHttpParameterValueSubTask;
		ReadHttpParameterNameSubTask readHttpParameterNameSubTask;
		ReadHttpPathSubTask readHttpPathSubTask;
		DeterminateHttpMethodSubTask determinateHttpMethodSubTask;

		// ---

		StreamReadBytesCounting streamReadBytesCounting;
		StreamReadBytesCounting* streamReadBytesCountingPtr;

		// ---

		bool isTimeoutWatcherStarted;
		unsigned long startTime;

		// ---

		void resetInternalState();
};

// =================================================

#endif /* RESTSERVER_H_ */
