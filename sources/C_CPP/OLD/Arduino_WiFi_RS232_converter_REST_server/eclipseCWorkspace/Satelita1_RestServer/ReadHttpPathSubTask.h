/*
 * ReadHttpPathSubTask.h
 *
 *  Created on: 22-04-2012
 *      Author: root
 */

#ifndef READHTTPPATHSUBTASK_H_
#define READHTTPPATHSUBTASK_H_

// =================================================

#include <Arduino.h>
//#include <Print.h>

// =================================================

#include "RestServerSubTask.h"
//#include "Streaming.h"

//#include "Configuration.c"
#include "DebugPrinter.h"
#include "RestServerCommon.h"
#include "SkipBytesUntilSequenceSubTask.h"
#include "ReadHttpParameterNameSubTask.h"
#include "SendResponseSubTask.h"
#include "StreamReadUntilByte.h"

// =================================================

//#define ReadHttpPathSubTask_IS_SELECTED 1
//#define ReadHttpPathSubTask_IS_COMPLETELY_MATCHED 2

// =================================================

class ReadHttpPathSubTask : public RestServerSubTask
{
	public:

		ReadHttpPathSubTask( RestServerSubTask* _errorSubTask , SkipBytesUntilSequenceSubTask* _skipBytesUntilSequenceSubTask , ReadHttpParameterNameSubTask* _readHttpParameterNameSubTask , SendResponseSubTask* _sendResponseSubTask , ServiceDescription** _serviceDescrptions , unsigned char _serviceDescrptionsCount , ServiceDescription* _arrayForSelectdServices , bool _leaveLastByteOfHttpHeaderInStream , char* _buffer , unsigned char _bufferSize );

		void setWork( bool _isGETHttpMethod );

		char* getSubTaskName();
		void resetInternalState();
		RestServerSubTask* executeSubTask( Stream* stream );

	protected:

		//Print& p;
		DebugPrinter dp;
		//static const PROGMEM prog_char className[];

		RestServerSubTask* errorSubTask;
		SkipBytesUntilSequenceSubTask* skipBytesUntilSequenceSubTask;
		ReadHttpParameterNameSubTask* readHttpParameterNameSubTask;
		SendResponseSubTask* sendResponseSubTask;
		//unsigned int readingMaxTime;
		//unsigned int readingMaxBytesCount;
		ServiceDescription** serviceDescrptions;
		unsigned char serviceDescrptionsCount;
		ServiceDescription* arrayForSelectdServices;
		//unsigned char* arrayForMatchServiceNames;
		bool leaveLastByteOfHttpHeaderInStream;

		//unsigned long startTime;
		bool isGETHttpMethod;

		//unsigned int alreadyReadBytesCount;
		//unsigned char letterIndex;
		//bool thereWasAtLeastOneMatching;

		//void sumUpWorkOrOnlyWorkPart();
		//unsigned char prepareSelectedServicesArray( bool addAllIfNoneWasSelectedDuringMatching );

		//bool isSelected( unsigned char index );
		//void setSelected( unsigned char index , bool isSelected );
		//bool isCompletelyMatched( unsigned char index );
		//void setCompletelyMatched( unsigned char index , bool isCompletelyMatched );


		static const char* endOfHttpHeader;

		static const char* stopBytes;
		StreamReadUntilByte streamReadUntilByte;

		unsigned char responseType; // 0 - normal , 1 - json , 2 - metadescription

		unsigned char selectedServicesArrayIndex;
		bool thereWasAtLeastOneMatching;

		void addToSelectedServicesArray( unsigned char selectedServiceIndex );
		bool isInSelectedServicesArray( unsigned char selectedServiceIndex );
		bool isStringStartsWith( char* str , char* startsWith );
		bool compareStrings( char* str , char* startsWith );
		void allAllServicesToSelectedServicesArray();
		void addMatchedServicesToSelectedServicesArray( bool matchByStartsWith );

};

// =================================================

#endif /* READHTTPPATHSUBTASK_H_ */
