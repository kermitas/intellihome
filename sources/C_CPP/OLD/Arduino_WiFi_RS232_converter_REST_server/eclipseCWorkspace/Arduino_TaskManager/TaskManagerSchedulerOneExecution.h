/*
 * TaskManagerSchedulerOneExecution.h
 *
 *  Created on: 08-01-2012
 *      Author: root
 */

#ifndef TASKMANAGERSCHEDULERONEEXECUTION_H_
#define TASKMANAGERSCHEDULERONEEXECUTION_H_

#include "TaskManagerScheduler.h"

class TaskManagerSchedulerOneExecution : public TaskManagerScheduler
{
	public:
		TaskManagerSchedulerOneExecution();

		bool canExecute();
		bool canRemoveFromTaskManager();

		virtual ~TaskManagerSchedulerOneExecution();
};

#endif /* TASKMANAGERSCHEDULERONEEXECUTION_H_ */
