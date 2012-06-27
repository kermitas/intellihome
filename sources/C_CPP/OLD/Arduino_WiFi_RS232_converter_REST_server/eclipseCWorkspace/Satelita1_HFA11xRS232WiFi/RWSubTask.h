/*
 * RWSubTask.h
 *
 *  Created on: 21-05-2012
 *      Author: root
 */

#ifndef RWSubTask_H_
#define RWSubTask_H_

// =================================================

class RWSubTask
{
	public:

		virtual char* getSubTaskName() = 0;

		virtual void resetInternalState() = 0;

		virtual unsigned long getStateTimeout() = 0; // 0 means no timeout
		virtual RWSubTask* getStateAfterTimeout() = 0;

		virtual RWSubTask* executeSubTask() = 0; // if returns NULL then no state transition
};

// =================================================

#endif /* RWSubTask_H_ */
