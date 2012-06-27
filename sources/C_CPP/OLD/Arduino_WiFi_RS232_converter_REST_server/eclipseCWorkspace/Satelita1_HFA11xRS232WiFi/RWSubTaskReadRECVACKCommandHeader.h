/*
 * RWSubTaskReadRECVACKCommandHeader.h
 *
 *  Created on: 21-05-2012
 *      Author: root
 */

#ifndef RWSubTaskReadRECVACKCommandHeader_H_
#define RWSubTaskReadRECVACKCommandHeader_H_

// =================================================

#include <Arduino.h>

// =================================================

#include "DebugPrinter.h"
#include "RWSubTask.h"
#include "AnyBuffer.h"
#include "StreamHFA11xRS232WiFiCRC.h"
#include "RWCommandSerialNumber.h"
#include "RWSubTaskWaitForData.h"
#include "RWSubTaskReadRECVACKCommandData.h"

// =================================================

class RWSubTaskReadRECVACKCommandHeader : public RWSubTask
{
	public:

		RWSubTaskReadRECVACKCommandHeader( AnyBuffer< byte , byte >* _inputBuffer , StreamHFA11xRS232WiFiCRC* _crcStream , RWCommandSerialNumber* _rwCommandSerialNumber , RWSubTaskWaitForData* _rwSubTaskWaitForData , RWSubTaskReadRECVACKCommandData* _rwSubTaskReadRECVACKCommandData , RWSubTask* _subTaskOnFail );

		char* getSubTaskName();

		void resetInternalState();

		unsigned long getStateTimeout();
		RWSubTask* getStateAfterTimeout();

		RWSubTask* executeSubTask();

	protected:

		// ---

		DebugPrinter dp;

		// ---

		AnyBuffer< byte , byte >* inputBuffer;

		StreamHFA11xRS232WiFiCRC* crcStream;

		RWCommandSerialNumber* rwCommandSerialNumber;

		RWSubTaskWaitForData* rwSubTaskWaitForData;
		RWSubTaskReadRECVACKCommandData* rwSubTaskReadRECVACKCommandData;
		RWSubTask* subTaskOnFail;

		// ---
};

// =================================================

#endif /* RWSubTaskReadRECVACKCommandHeader_H_ */

