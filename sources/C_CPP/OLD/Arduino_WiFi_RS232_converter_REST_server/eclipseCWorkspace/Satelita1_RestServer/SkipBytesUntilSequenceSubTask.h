/*
 * SkipBytesUntilSequenceSubTask.h
 *
 *  Created on: 18-04-2012
 *      Author: root
 */

#ifndef SKIPBYTESUNTILSEQUENCESUBTASK_H_
#define SKIPBYTESUNTILSEQUENCESUBTASK_H_

// =================================================

#include <Arduino.h>
//#include <Print.h>

// =================================================

//#include "Configuration.c"
#include "DebugPrinter.h"
#include "RestServerSubTask.h"
//#include "Streaming.h"
#include "StreamSkipBytes.h"

// =================================================

class SkipBytesUntilSequenceSubTask : public RestServerSubTask
{
	public:

		//SkipBytesUntilSequenceSubTask( Print& _p , RestServerSubTask* _errorSubTask , unsigned int _skippingMaxTime , unsigned int _skippingMaxBytesCount );
		SkipBytesUntilSequenceSubTask( RestServerSubTask* _errorSubTask );

		void setStopSequenceAndNextSubTask( char* _stopSequence , bool _leaveLastByteInStream , RestServerSubTask* _nextSubTask );
		void setSkipBytesCountAndNextSubTask( unsigned int _skipBytesCount , RestServerSubTask* _nextSubTask );

		char* getSubTaskName();
		void resetInternalState();
		RestServerSubTask* executeSubTask( Stream* stream );

	protected:

		//Print& p;
		DebugPrinter dp;
		//static const PROGMEM prog_char className[];

		RestServerSubTask* errorSubTask;
		//unsigned int skippingMaxTime;
		//unsigned int skippingMaxBytesCount;

		//bool workUsingSkipBytesCount;

		//const char* stopSequence;
		//unsigned int skipBytesCount;
		RestServerSubTask* nextSubTask;
		//unsigned long startTime;
		//bool leaveLastByteInStream;

		//unsigned char alreadyMatchedBytesCount;
		//unsigned int alreadySkippedBytesCount;

		StreamSkipBytes streamSkipBytes;
};

// =================================================

#endif /* SKIPBYTESUNTILSEQUENCESUBTASK_H_ */
