/*
 * TaskManagerTaskRecord.h
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

#ifndef TASKMANAGERTASKRECORD_H_
#define TASKMANAGERTASKRECORD_H_

#include "TaskManagerScheduler.h"
#include "Runnable.h"
#include "TaskManagerMemoryConfigurator.h"

class TaskManagerRecord
{
	public:
	TaskManagerRecord( TaskManagerMemoryConfigurator* _taskManagerMemoryConfigurator , TaskManagerScheduler* _taskManagerScheduler , Runnable* _runnable );
		virtual ~TaskManagerRecord();

		TaskManagerMemoryConfigurator* taskManagerMemoryConfigurator;
		TaskManagerScheduler* taskManagerScheduler;
		Runnable* runnable;

};

#endif /* TASKMANAGERTASKRECORD_H_ */
