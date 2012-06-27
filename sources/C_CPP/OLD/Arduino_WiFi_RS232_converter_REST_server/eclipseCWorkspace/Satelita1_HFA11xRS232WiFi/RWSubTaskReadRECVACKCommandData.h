/*
 * RWSubTaskReadRECVACKCommandData.h
 *
 *  Created on: 21-05-2012
 *      Author: root
 */

#ifndef RWSUBTASKREADRECVACKCOMMANDDATA_H_
#define RWSUBTASKREADRECVACKCOMMANDDATA_H_

// =================================================

#include <Arduino.h>

// =================================================

#include "DebugPrinter.h"
#include "RWSubTask.h"
#include "AnyBuffer.h"
#include "StreamHFA11xRS232WiFiCRC.h"
#include "RWCommandSerialNumber.h"

// =================================================

class RWSubTaskReadRECVACKCommandData : public RWSubTask
{
	public:

		RWSubTaskReadRECVACKCommandData( AnyBuffer< byte , byte >* _inputBuffer , StreamHFA11xRS232WiFiCRC* _crcStream , RWCommandSerialNumber* _rwCommandSerialNumber , RWSubTask* _subTaskOnSuccess , RWSubTask* _subTaskOnFail );

		char* getSubTaskName();

		void resetInternalState();

		unsigned long getStateTimeout();
		RWSubTask* getStateAfterTimeout();

		RWSubTask* executeSubTask();

		void setWork( unsigned int _incommingDataSize );

	protected:

		// ---

		DebugPrinter dp;

		// ---

		AnyBuffer< byte , byte >* inputBuffer;

		StreamHFA11xRS232WiFiCRC* crcStream;

		RWCommandSerialNumber* rwCommandSerialNumber;

		RWSubTask* subTaskOnSuccess;
		RWSubTask* subTaskOnFail;

		unsigned int incommingDataSize;

		// ---

		bool compareCRCsumWithCRCsumCalculatedOnTwoIncommingBytes( unsigned int crcCountedByUnderlyingCRCStream );

		// ---
};

// =================================================

#endif /* RWSUBTASKREADRECVACKCOMMANDDATA_H_ */

