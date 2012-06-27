/*
 * RWSubTaskWaitForData.h
 *
 *  Created on: 21-05-2012
 *      Author: root
 */

#ifndef RWSUBTASKWAITFORDATA_H_
#define RWSUBTASKWAITFORDATA_H_

// =================================================

#include <Arduino.h>
#include <Stream.h>

// =================================================

#include "DebugPrinter.h"
#include "RWSubTask.h"

// =================================================

class RWSubTaskWaitForData : public RWSubTask
{
	public:

		RWSubTaskWaitForData( Stream* _stream );

		char* getSubTaskName();

		void resetInternalState();

		unsigned long getStateTimeout();
		RWSubTask* getStateAfterTimeout();

		RWSubTask* executeSubTask();

		void setWork( unsigned int _waitForBytesCount , RWSubTask* _taskIfDataAvailable , unsigned long _timeout , RWSubTask* _taskOnTimeout );

	protected:

		// ---

		DebugPrinter dp;

		// ---

		Stream* stream;

		unsigned int waitForBytesCount;
		RWSubTask* taskIfDataAvailable;
		unsigned long timeout;
		RWSubTask* taskOnTimeout;

		// ---
};

// =================================================

#endif /* RWSUBTASKWAITFORDATA_H_ */

