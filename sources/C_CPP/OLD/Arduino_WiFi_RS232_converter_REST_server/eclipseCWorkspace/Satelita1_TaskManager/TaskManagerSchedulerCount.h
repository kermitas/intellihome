/*
 * TaskManagerSchedulerCount.h
 *
 *  Created on: 02-04-2012
 *      Author: root
 */

#ifndef TASKMANAGERSCHEDULERCOUNT_H_
#define TASKMANAGERSCHEDULERCOUNT_H_

// =================================================

#include <Arduino.h>
//#include <Print.h>

// =================================================

#include "DebugPrinter.h"
//#include "Configuration.c"
//#include "Streaming.h"
#include "TaskManagerScheduler.h"

// =================================================

class TaskManagerSchedulerCount : public TaskManagerScheduler
{
	public:

		TaskManagerSchedulerCount( unsigned long _executionCount );
		bool canExecute();
		bool canRemoveFromTaskManager();
		//virtual ~TaskManagerSchedulerCount();

	protected:

		unsigned long executionCount;
		unsigned long currentExecutionCount;

	private:

		//Print& p;
		DebugPrinter dp;
		//static const PROGMEM prog_char className[];
};

// =================================================

#endif /* TASKMANAGERSCHEDULERCOUNT_H_ */
