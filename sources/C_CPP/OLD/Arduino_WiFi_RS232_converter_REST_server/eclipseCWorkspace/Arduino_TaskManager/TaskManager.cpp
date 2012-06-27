/*
 * TaskManager.cpp
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

#include "TaskManager.h"

#include <Arduino.h>

TaskManager::TaskManager( TaskManagerStatistics* _taskManagerStatistics )
{
	taskManagerStatistics = _taskManagerStatistics;

	tasksQueueA = new QueueList <TaskManagerRecord*>();
	tasksQueueB = new QueueList <TaskManagerRecord*>();

	memConfFreeSchedulerFreeRunnable = new TaskManagerMemoryConfigurator( true , true , false );
	memConfFreeSchedulerLeaveRunnable = new TaskManagerMemoryConfigurator( true , false , false );
	memConfLeaveSchedulerFreeRunnable = new TaskManagerMemoryConfigurator( false , true , false );
	memConfLeaveSchedulerLeaveRunnable = new TaskManagerMemoryConfigurator( false , false , false );
}

void TaskManager::addTask( bool _canTaskManagerFreeScheduler , bool _canTaskManagerFreeRunnable , TaskManagerScheduler* taskManagerScheduler , Runnable* runnable )
{
	TaskManagerMemoryConfigurator* memConf;

	if( _canTaskManagerFreeScheduler && _canTaskManagerFreeRunnable )
		memConf = memConfFreeSchedulerFreeRunnable;
	else
	if( _canTaskManagerFreeScheduler && !_canTaskManagerFreeRunnable )
		memConf = memConfFreeSchedulerLeaveRunnable;
	else
	if( !_canTaskManagerFreeScheduler && _canTaskManagerFreeRunnable )
		memConf = memConfLeaveSchedulerFreeRunnable;
	else
		memConf = memConfLeaveSchedulerLeaveRunnable;

	addTask( memConf , taskManagerScheduler , runnable );
}

void TaskManager::addTask( TaskManagerMemoryConfigurator* taskManagerMemoryConfigurator , TaskManagerScheduler* taskManagerScheduler , Runnable* runnable )
{
	TaskManagerRecord* record = new TaskManagerRecord( taskManagerMemoryConfigurator , taskManagerScheduler , runnable );

	if( !tasksQueueA->isEmpty() )
		tasksQueueA->push( record );
	else
		tasksQueueB->push( record );
}

void TaskManager::execute()
{
	if( taskManagerStatistics != NULL )
	{
		taskManagerStatistics->beforeTaskQueue();

		int executedTasksCountInThisIteration = executeTasksQueue();

		unsigned long checkedTasksCountInThisIteration = tasksQueueA->count() + tasksQueueB->count();
		taskManagerStatistics->afterTaskQueue( checkedTasksCountInThisIteration, executedTasksCountInThisIteration , checkedTasksCountInThisIteration-executedTasksCountInThisIteration );
	}
	else
		executeTasksQueue();
}

int TaskManager::executeTasksQueue()
{
	int executedTasksCount = 0;

	QueueList<TaskManagerRecord*>* fromQueue;
	QueueList<TaskManagerRecord*>* toQueue;

	if( !tasksQueueA->isEmpty() )
	{
		fromQueue = tasksQueueA;
		toQueue = tasksQueueB;
	}
	else
	{
		fromQueue = tasksQueueB;
		toQueue = tasksQueueA;
	}

	while( !fromQueue->isEmpty() )
	{
		TaskManagerRecord* taskManagerTaskRecord = fromQueue->pop();

		if( taskManagerTaskRecord->taskManagerScheduler->canExecute() )
		{
			taskManagerTaskRecord->runnable->run();
			executedTasksCount++;
		}

		if( taskManagerTaskRecord->taskManagerScheduler->canRemoveFromTaskManager() )
			delete( taskManagerTaskRecord );
		else
			toQueue->push( taskManagerTaskRecord );
	}

	return executedTasksCount;
}

TaskManager::~TaskManager()
{
	delete( memConfFreeSchedulerFreeRunnable );
	delete( memConfFreeSchedulerLeaveRunnable );
	delete( memConfLeaveSchedulerFreeRunnable );
	delete( memConfLeaveSchedulerLeaveRunnable );

	while( !tasksQueueA->isEmpty() ) delete( tasksQueueA->pop() );
	while( !tasksQueueB->isEmpty() ) delete( tasksQueueA->pop() );

	delete( tasksQueueA );
	delete( tasksQueueB );
}
