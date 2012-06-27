/*
 * RWSubTaskDecideToSendOutgoingData.h
 *
 *  Created on: 22-05-2012
 *      Author: root
 */

#ifndef RWSUBTASKDECIDETOSENDOUTGOINGDATA_H_
#define RWSUBTASKDECIDETOSENDOUTGOINGDATA_H_

// =================================================

#include <Arduino.h>

// =================================================

#include "DebugPrinter.h"
#include "RWSubTask.h"
#include "AnyBuffer.h"
#include "RWSubTaskSendSENDCommand.h"

// =================================================

class RWSubTaskDecideToSendOutgoingData : public RWSubTask
{
	public:

		RWSubTaskDecideToSendOutgoingData( AnyBuffer< byte , byte >* _outputBuffer , RWSubTaskSendSENDCommand* _rwSubTaskSendSENDCommand , RWSubTask* _subTaskIfNotSendOutgoingData , byte _sendRetryCount );

		char* getSubTaskName();

		void resetInternalState();

		unsigned long getStateTimeout();
		RWSubTask* getStateAfterTimeout();

		RWSubTask* executeSubTask();

	protected:

		// ---

		DebugPrinter dp;

		// ---

		AnyBuffer< byte , byte >* outputBuffer;

		RWSubTaskSendSENDCommand* rwSubTaskSendSENDCommand;
		RWSubTask* subTaskIfNotSendOutgoingData;

		byte sendRetryCount;

		// ---
};

// =================================================

#endif /* RWSUBTASKDECIDETOSENDOUTGOINGDATA_H_ */

