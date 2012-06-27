/*
 * TaskManagerTaskRecord.h
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

#ifndef TASKMANAGERSCHEDULER_H_
#define TASKMANAGERSCHEDULER_H_

// =================================================

class TaskManagerScheduler
{
	public:
		//TaskManagerScheduler();
		virtual bool canExecute() = 0;
		virtual bool canRemoveFromTaskManager() = 0;
		//virtual ~TaskManagerScheduler();
};

// =================================================

#endif /* TASKMANAGERSCHEDULER_H_ */
