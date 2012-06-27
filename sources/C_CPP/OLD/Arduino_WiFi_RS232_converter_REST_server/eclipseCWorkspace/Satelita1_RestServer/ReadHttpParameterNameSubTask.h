/*
 * ReadHttpParameterNameSubTask.h
 *
 *  Created on: 28-04-2012
 *      Author: root
 */

#ifndef ReadHttpParameterNameSubTask_H_
#define ReadHttpParameterNameSubTask_H_

// =================================================

#include <Arduino.h>
//#include <Print.h>

// =================================================

#include "RestServerSubTask.h"
//#include "Streaming.h"
#include "DebugPrinter.h"
//#include "Configuration.c"
#include "RestServerCommon.h"
//#include "SkipBytesUntilSequenceSubTask.h"
//#include "ReadHttpParametersSubTask.h"
#include "SendResponseSubTask.h"
#include "ReadHttpParameterValueSubTask.h"

// =================================================

class ReadHttpParameterNameSubTask : public RestServerSubTask
{
	public:

		ReadHttpParameterNameSubTask( RestServerSubTask* _errorSubTask , unsigned int _readingMaxTime , unsigned int _readingMaxBytesCount , ServiceDescription** _serviceDescrptions , unsigned char _serviceDescrptionsCount , bool* _arrayForMatchServiceNames , ReadHttpParameterValueSubTask* _readHttpParameterValueSubTask );

		void setWork( RestServerSubTask* _subTaskAfterParsingAllParameters );

		char* getSubTaskName();
		void resetInternalState();
		RestServerSubTask* executeSubTask( Stream* stream );

	protected:

		//Print& p;
		DebugPrinter dp;

		RestServerSubTask* errorSubTask;
		RestServerSubTask* subTaskAfterParsingAllParameters;
		ReadHttpParameterValueSubTask* readHttpParameterValueSubTask;

		unsigned int readingMaxTime;
		unsigned int readingMaxBytesCount;
		ServiceDescription** serviceDescrptions;
		unsigned char serviceDescrptionsCount;
		bool* arrayForMatchServiceNames;

		unsigned long startTime;

		unsigned int alreadyReadBytesCount;
		unsigned char letterIndex;
};

// =================================================

#endif /* ReadHttpParameterNameSubTask_H_ */
