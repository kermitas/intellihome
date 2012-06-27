/*
 * TimeIntervalTaskManagerTaskExecutionInfo.h
 *
 *  Created on: 06-01-2012
 *      Author: root
 */

#ifndef TASKMANAGERSCHEDULERTIMEINTERVALS_H_
#define TASKMANAGERSCHEDULERTIMEINTERVALS_H_

#include "TaskManagerScheduler.h"
#include "QueueList.h"

class TaskManagerSchedulerTimeIntervals : public TaskManagerScheduler
{
	public:
	TaskManagerSchedulerTimeIntervals( QueueList<unsigned long>* _timeIntervalsInMs , bool _isCyclic , bool _shouldIFreeQueue );
		bool canExecute();
		bool canRemoveFromTaskManager();
		void setCyclic( bool _isCyclic );
		virtual ~TaskManagerSchedulerTimeIntervals();

	protected:
		QueueList<unsigned long>* queueA;
		QueueList<unsigned long>* queueB;
		bool isCyclic;
		bool shouldIFreeQueue;
		unsigned long lastExecutionTime;
		bool wasWholeQueueExecuted;
};

#endif /* TASKMANAGERSCHEDULERTIMEINTERVALS_H_ */
