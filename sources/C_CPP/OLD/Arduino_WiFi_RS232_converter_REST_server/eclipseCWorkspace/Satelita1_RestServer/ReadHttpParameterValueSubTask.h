/*
 * ReadHttpParameterValueSubTask.h
 *
 *  Created on: 28-04-2012
 *      Author: root
 */

#ifndef READHTTPPARAMETERVALUESUBTASK_H_
#define READHTTPPARAMETERVALUESUBTASK_H_

// =================================================

#include <Arduino.h>
//#include <Print.h>

// =================================================

#include "RestServerSubTask.h"
//#include "Streaming.h"
#include "DebugPrinter.h"
//#include "Configuration.c"
#include "RestServerCommon.h"
#include "SendResponseSubTask.h"

// =================================================

class ReadHttpParameterValueSubTask : public RestServerSubTask
{
	public:

		ReadHttpParameterValueSubTask( RestServerSubTask* _errorSubTask , unsigned int _readingMaxTime , unsigned char* _arrayForValueBytes , unsigned char _arrayForValueBytesSize );

		void setWork( RestServerSubTask* _subTaskAfterParsingAllParameters , ServiceDescription* _selectedServiceDescription , RestServerSubTask* _subTaskThatWillReadNextHttpParameterName );

		char* getSubTaskName();
		void resetInternalState();
		RestServerSubTask* executeSubTask( Stream* stream );

	protected:

		//Print& p;
		DebugPrinter dp;

		RestServerSubTask* errorSubTask;
		unsigned int readingMaxTime;
		unsigned char* arrayForValueBytes;
		unsigned char arrayForValueBytesSize;

		RestServerSubTask* subTaskAfterParsingThisOneValue;
		RestServerSubTask* subTaskAfterParsingAllParameters;
		ServiceDescription* selectedServiceDescription;
		RestServerSubTask* subTaskThatWillReadNextHttpParameterName;

		unsigned long startTime;
		unsigned char letterIndex;

		void parseReadParameterValue();
};

// =================================================

#endif /* READHTTPPARAMETERVALUESUBTASK_H_ */
