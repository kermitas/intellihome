/*
 * TaskManager.h
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

#ifndef TASKMANAGER_H_
#define TASKMANAGER_H_

#include "QueueList.h"
#include "TaskManagerRecord.h"
#include "TaskManagerMemoryConfigurator.h"
#include "TaskManagerScheduler.h"
#include "Runnable.h"
#include "TaskManagerStatistics.h"

class TaskManager
{
	public:
		TaskManager( TaskManagerStatistics* _taskManagerStatistics );

		void addTask( bool _canTaskManagerFreeScheduler , bool _canTaskManagerFreeRunnable , TaskManagerScheduler* taskManagerScheduler , Runnable* runnable );
		void addTask( TaskManagerMemoryConfigurator* taskManagerMemoryConfigurator , TaskManagerScheduler* taskManagerScheduler , Runnable* runnable );
		void execute();
		virtual ~TaskManager();

	protected:
		TaskManagerStatistics* taskManagerStatistics;
		QueueList <TaskManagerRecord*>* tasksQueueA;
		QueueList <TaskManagerRecord*>* tasksQueueB;
		TaskManagerMemoryConfigurator* memConfFreeSchedulerFreeRunnable;
		TaskManagerMemoryConfigurator* memConfFreeSchedulerLeaveRunnable;
		TaskManagerMemoryConfigurator* memConfLeaveSchedulerFreeRunnable;
		TaskManagerMemoryConfigurator* memConfLeaveSchedulerLeaveRunnable;

		int executeTasksQueue();
		void tryToFreeRecordAndWhatItKeeps( TaskManagerRecord* record );
};

#endif /* TASKMANAGER_H_ */
