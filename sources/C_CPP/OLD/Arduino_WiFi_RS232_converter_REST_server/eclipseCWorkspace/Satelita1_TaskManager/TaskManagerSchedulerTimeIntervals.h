/*
 * TimeIntervalTaskManagerTaskExecutionInfo.h
 *
 *  Created on: 06-01-2012
 *      Author: root
 */

#ifndef TASKMANAGERSCHEDULERTIMEINTERVALS_H_
#define TASKMANAGERSCHEDULERTIMEINTERVALS_H_

// =================================================

#include <Arduino.h>
//#include <Print.h>

// =================================================

//#include "Configuration.c"
#include "DebugPrinter.h"
//#include "Streaming.h"
#include "TaskManagerScheduler.h"

// =================================================

class TaskManagerSchedulerTimeIntervals : public TaskManagerScheduler
{
	public:

		TaskManagerSchedulerTimeIntervals( unsigned long* _timeIntervalsInMs , unsigned char _timeIntervalsCount , bool _isCyclic );
		bool canExecute();
		bool canRemoveFromTaskManager();
		//virtual ~TaskManagerSchedulerTimeIntervals();

	protected:

		unsigned long* timeIntervalsInMs;
		unsigned char timeIntervalsCount;
		bool isCyclic;

	private:

		//Print& p;
		DebugPrinter dp;
		//static const PROGMEM prog_char className[];

		unsigned long lastExecutionTime;

		char executionTaskCounter;
		bool wasAllTasksExecuted;

		void resetState();
};

// =================================================

#endif /* TASKMANAGERSCHEDULERTIMEINTERVALS_H_ */
