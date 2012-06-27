/*
 * SendResponseSubTask.h
 *
 *  Created on: 22-04-2012
 *      Author: root
 */

#ifndef SENDRESPONSESUBTASK_H_
#define SENDRESPONSESUBTASK_H_

// =================================================

#include <Arduino.h>
//#include <Print.h>

// =================================================

//#include "Configuration.c"
#include "DebugPrinter.h"
#include "RestServerSubTask.h"
//#include "Streaming.h"

#include "RestServerCommon.h"
#include "PageRenderer.h"
#include "StreamHttpChunkedTransferEncoding.h"
#include "AnyBuffer.h"

// =================================================

class SendResponseSubTask : public RestServerSubTask
{
	public:

		SendResponseSubTask( RestServerSubTask* _errorSubTask , PageRenderer* _htmlPageRenderer , PageRenderer* _jsonPageRenderer , bool _readLasyByteFromStreamAfterFullResponse , AnyBuffer< byte , byte >* _chunkedStreamBuffer );

		void setWork( bool _isGEThttpMethod , bool _sendResponseInJSON, bool _sendResponseAsServiceMetaDescription , ServiceDescription* _selectdServices , unsigned char _selectedServicesCount );

		char* getSubTaskName();
		void resetInternalState();
		RestServerSubTask* executeSubTask( Stream* stream );

	protected:

		//Print& p;
		DebugPrinter dp;
		//static const PROGMEM prog_char className[];

		RestServerSubTask* errorSubTask;
		PageRenderer* htmlPageRenderer;
		PageRenderer* jsonPageRenderer;
		bool readLasyByteFromStreamAfterFullResponse;

		unsigned char indexOfGeneratedService;

		bool isGETHttpMethod;
		bool sendResponseAsServiceMetaDescription;
		bool sendResponseInJSON;
		ServiceDescription* selectdServices;
		unsigned char selectedServicesCount;
		PageRenderer* currentPageRenderer;

		//uint8_t chunkedStreamBuffer[ 300 ];
		StreamHttpChunkedTransferEncoding chunkedStream;//( &chunkedStreamBuffer[0] , (sizeof(chunkedStreamBuffer) / sizeof(uint8_t)) );
		//StreamHttpChunkedTransferEncoding* chunkedStreamPtr;
};

// =================================================

#endif /* SENDRESPONSESUBTASK_H_ */
