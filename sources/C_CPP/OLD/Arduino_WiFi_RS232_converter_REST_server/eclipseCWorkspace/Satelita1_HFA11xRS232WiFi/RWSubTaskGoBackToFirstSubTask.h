/*
 * RWSubTaskGoBackToFirstSubTask.h
 *
 *  Created on: 22-05-2012
 *      Author: root
 */

#ifndef RWSUBTASKGOBACKTOFIRSTSUBTASK_H_
#define RWSUBTASKGOBACKTOFIRSTSUBTASK_H_

// =================================================

#include <Arduino.h>

// =================================================

#include "RWSubTask.h"

// =================================================

class RWSubTaskGoBackToFirstSubTask : public RWSubTask
{
	public:

		//RWSubTaskGoBackToFirstSubTask();

		char* getSubTaskName();

		void resetInternalState();

		unsigned long getStateTimeout();
		RWSubTask* getStateAfterTimeout();

		RWSubTask* executeSubTask();
};

// =================================================

#endif /* RWSUBTASKGOBACKTOFIRSTSUBTASK_H_ */

