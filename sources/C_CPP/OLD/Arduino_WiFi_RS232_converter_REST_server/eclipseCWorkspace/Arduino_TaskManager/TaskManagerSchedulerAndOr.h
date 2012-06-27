/*
 * TaskManagerLogicTaskExecutionInfo.h
 *
 *  Created on: 06-01-2012
 *      Author: root
 */

#ifndef TASKMANAGERSCHEDULERANDOR_H_
#define TASKMANAGERSCHEDULERANDOR_H_

#include "TaskManagerScheduler.h"
#include "QueueList.h"

class TaskManagerSchedulerAndOr : public TaskManagerScheduler
{
	public:
	TaskManagerSchedulerAndOr( QueueList<TaskManagerScheduler*>* _tasks , bool _ifTrueThenANDifFalseThenOR );
		bool canExecute();
		bool canRemoveFromTaskManager();
		virtual ~TaskManagerSchedulerAndOr();

	protected:
		QueueList<TaskManagerScheduler*>* tasks;
		bool ifTrueThenANDifFalseThenOR;

		bool doAction( bool ifTrueDoCanExecuteIfFalseDoCanRemoveFromTaskManager );

};

#endif /* TASKMANAGERSCHEDULERANDOR_H_ */
