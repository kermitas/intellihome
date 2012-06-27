/*
 * RestServerCommon.h
 *
 *  Created on: 22-04-2012
 *      Author: root
 */

#ifndef RESTSERVERCOMMON_H_
#define RESTSERVERCOMMON_H_

// =================================================

#include "RestService.h"
#include "RestServiceRenderer.h"

// =================================================

//#define MAX_TIME_FOR_SKIPPING_INCOMMING_BYTES 5000
//#define MAX_BYTES_COUNT_WHILE_SKIPPING_INCOMMING_BYTES 10240

#define MAX_TIME_FOR_PROCESS_INCOMMING_HTTP_REQUEST 15000
#define MAX_BYTES_COUNT_OF_INCOMMING_HTTP_REQUEST 10240

//#define MAX_TIME_FOR_READING_HTTP_PATH 5000
//#define MAX_BYTES_COUNT_WHILE_READING_HTTP_PATH 10240

#define MAX_TIME_FOR_READING_HTTP_PARAMETER_NAME 5000
#define MAX_BYTES_COUNT_WHILE_READING_HTTP_PARAMETER_NAME 10240

#define MAX_TIME_FOR_READING_HTTP_PARAMETER_VALUE 5000

// =================================================

typedef struct ServiceDescription
{
	RestService* restService;

	RestServiceRenderer** restServiceRenderers; // html , json , metadescription (always in json)

	//RestServiceRenderer* htmlRestServiceRenderer;
	//RestServiceRenderer* jsonRestServiceRenderer;
	//RestServiceRenderer* metadescriptionRestServiceRenderer;
};

// =================================================

#endif /* RESTSERVERCOMMON_H_ */
