/*
 * ReadHttpPathSubTask.h
 *
 *  Created on: 22-04-2012
 *      Author: root
 */

/*

#ifndef READHTTPPATHSUBTASK_H_
#define READHTTPPATHSUBTASK_H_

// =================================================

#include <Arduino.h>
#include <Print.h>

// =================================================

#include "RestServerSubTask.h"
#include "Streaming.h"

#include "Configuration.c"
#include "RestServerCommon.h"
#include "SkipBytesUntilSequenceSubTask.h"
#include "ReadHttpParameterNameSubTask.h"
#include "SendResponseSubTask.h"
#include "StreamReadUntilByte.h"

// =================================================

#define ReadHttpPathSubTask_IS_SELECTED 1
#define ReadHttpPathSubTask_IS_COMPLETELY_MATCHED 2

// =================================================

class ReadHttpPathSubTask : public RestServerSubTask
{
	public:

		ReadHttpPathSubTask( Print& _p , RestServerSubTask* _errorSubTask , SkipBytesUntilSequenceSubTask* _skipBytesUntilSequenceSubTask , ReadHttpParameterNameSubTask* _readHttpParameterNameSubTask , SendResponseSubTask* _sendResponseSubTask , unsigned int _readingMaxTime , unsigned int _readingMaxBytesCount , ServiceDescription** _serviceDescrptions , unsigned char _serviceDescrptionsCount , ServiceDescription* _arrayForSelectdServices , unsigned char* _arrayForMatchServiceNames , bool _leaveLastByteOfHttpHeaderInStream , char* _buffer , unsigned char _bufferSize );

		void setWork( bool _isGETHttpMethod );

		char* getSubTaskName();
		void resetInternalState();
		RestServerSubTask* executeSubTask( Stream* stream );

	protected:

		Print& p;
		RestServerSubTask* errorSubTask;
		SkipBytesUntilSequenceSubTask* skipBytesUntilSequenceSubTask;
		ReadHttpParameterNameSubTask* readHttpParameterNameSubTask;
		SendResponseSubTask* sendResponseSubTask;
		unsigned int readingMaxTime;
		unsigned int readingMaxBytesCount;
		ServiceDescription** serviceDescrptions;
		unsigned char serviceDescrptionsCount;
		ServiceDescription* arrayForSelectdServices;
		unsigned char* arrayForMatchServiceNames;
		bool leaveLastByteOfHttpHeaderInStream;

		unsigned long startTime;
		bool isGETHttpMethod;

		unsigned int alreadyReadBytesCount;
		unsigned char letterIndex;
		bool thereWasAtLeastOneMatching;

		void sumUpWorkOrOnlyWorkPart();
		unsigned char prepareSelectedServicesArray( bool addAllIfNoneWasSelectedDuringMatching );

		bool isSelected( unsigned char index );
		void setSelected( unsigned char index , bool isSelected );
		bool isCompletelyMatched( unsigned char index );
		void setCompletelyMatched( unsigned char index , bool isCompletelyMatched );

		static const char* stopBytes;
		StreamReadUntilByte streamReadUntilByte;

};

// =================================================

#endif */ /* READHTTPPATHSUBTASK_H_ */
