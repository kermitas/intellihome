/*
 * RWSubTaskDecideToReadIncommingData.h
 *
 *  Created on: 21-05-2012
 *      Author: root
 */

#ifndef RWSUBTASKDECIDETOREADINCOMMINGDATA_H_
#define RWSUBTASKDECIDETOREADINCOMMINGDATA_H_

// =================================================

#include <Arduino.h>

// =================================================

#include "DebugPrinter.h"
#include "RWSubTask.h"
#include "AnyBuffer.h"

// =================================================

class RWSubTaskDecideToReadIncommingData : public RWSubTask
{
	public:

		RWSubTaskDecideToReadIncommingData( AnyBuffer< byte , byte >* _inputBuffer , RWSubTask* _subTaskIfReadIncommingData , RWSubTask* _subTaskIfNotReadIncommingData );

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

		RWSubTask* subTaskIfReadIncommingData;
		RWSubTask* subTaskIfNotReadIncommingData;

		// ---
};

// =================================================

#endif /* RWSUBTASKDECIDETOREADINCOMMINGDATA_H_ */

