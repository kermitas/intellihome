/*
 * RWSubTaskReadSENDACKCommand.h
 *
 *  Created on: 22-05-2012
 *      Author: root
 */

#ifndef RWSUBTASKREADSENDACKCOMMAND_H_
#define RWSUBTASKREADSENDACKCOMMAND_H_

// =================================================

#include <Arduino.h>

// =================================================

#include "DebugPrinter.h"
#include "RWSubTask.h"
#include "AnyBuffer.h"
#include "StreamHFA11xRS232WiFiCRC.h"
#include "RWCommandSerialNumber.h"
//#include "RWSubTaskSendSENDCommand.h"

// =================================================

class RWSubTaskReadSENDACKCommand : public RWSubTask
{
	public:

		RWSubTaskReadSENDACKCommand( AnyBuffer< byte , byte >* _outputBuffer , StreamHFA11xRS232WiFiCRC* _crcStream , RWCommandSerialNumber* _rwCommandSerialNumber , RWSubTask* _subTaskOnSuccess , RWSubTask* _subTaskOnFail );

		char* getSubTaskName();

		void resetInternalState();

		unsigned long getStateTimeout();
		RWSubTask* getStateAfterTimeout();

		RWSubTask* executeSubTask();

		void setWork( byte _sendDataSize , RWSubTask* _subTaskOnRetry );
		//void setSubTaskOnRetry( RWSubTask* _subTaskOnRetry );

	protected:

		// ---

		DebugPrinter dp;

		// ---

		AnyBuffer< byte , byte >* outputBuffer;

		StreamHFA11xRS232WiFiCRC* crcStream;

		RWCommandSerialNumber* rwCommandSerialNumber;

		RWSubTask* subTaskOnRetry;
		RWSubTask* subTaskOnSuccess;
		RWSubTask* subTaskOnFail;

		byte sendDataSize;
		//byte retryNumber;

		// ---

		//bool compareCRCsumWithCRCsumCalculatedOnTwoIncommingBytes( unsigned int crcCountedByUnderlyingCRCStream );

		// ---
};

// =================================================

#endif /* RWSUBTASKREADSENDACKCOMMAND_H_ */

