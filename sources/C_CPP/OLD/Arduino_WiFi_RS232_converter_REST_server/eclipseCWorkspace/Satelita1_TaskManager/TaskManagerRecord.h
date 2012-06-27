/*
 * TaskManagerTaskRecord.h
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

#ifndef TASKMANAGERTASKRECORD_H_
#define TASKMANAGERTASKRECORD_H_

// =================================================

#include "TaskManagerScheduler.h"
#include "Runnable.h"

// =================================================

class TaskManagerRecord
{
	public:
		TaskManagerRecord( TaskManagerScheduler* _scheduler , Runnable* _runnable );
		//virtual ~TaskManagerRecord();

		TaskManagerScheduler* scheduler;
		Runnable* runnable;
};

// =================================================

#endif /* TASKMANAGERTASKRECORD_H_ */
