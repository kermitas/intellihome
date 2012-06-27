/*
 * TaskManagerTaskRecord.h
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

#ifndef TASKMANAGERSCHEDULER_H_
#define TASKMANAGERSCHEDULER_H_

class TaskManagerScheduler
{
	public:
		TaskManagerScheduler();
		virtual bool canExecute();
		virtual bool canRemoveFromTaskManager();
		virtual ~TaskManagerScheduler();
};

#endif /* TASKMANAGERSCHEDULER_H_ */
