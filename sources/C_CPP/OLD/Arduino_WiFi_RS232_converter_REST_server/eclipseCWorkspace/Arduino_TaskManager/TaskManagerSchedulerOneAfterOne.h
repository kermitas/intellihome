/*
 * TaskManagerABLogicTaskExecutionInfo.h
 *
 *  Created on: 06-01-2012
 *      Author: root
 */

#ifndef TASKMANAGERSCHEDULERONEAFTERONE_H_
#define TASKMANAGERSCHEDULERONEAFTERONE_H_

#include "TaskManagerScheduler.h"
#include "QueueList.h"

class TaskManagerSchedulerOneAfterOne : public TaskManagerScheduler
{
	public:
		TaskManagerSchedulerOneAfterOne( QueueList<TaskManagerScheduler*>* _tasks );
		bool canExecute();
		bool canRemoveFromTaskManager();
		virtual ~TaskManagerSchedulerOneAfterOne();

	protected:
		QueueList<TaskManagerScheduler*>* tasks;
		TaskManagerScheduler* currentTask;
		QueueList<TaskManagerScheduler*>* backupQueue;
};

#endif /* TASKMANAGERSCHEDULERONEAFTERONE_H_ */
