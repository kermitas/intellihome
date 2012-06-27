/*
 * TaskManagerABLogicTaskExecutionInfo.cpp
 *
 *  Created on: 06-01-2012
 *      Author: root
 */

#include "TaskManagerSchedulerOneAfterOne.h"

TaskManagerSchedulerOneAfterOne::TaskManagerSchedulerOneAfterOne( QueueList<TaskManagerScheduler*>* _tasks )
{
	tasks = _tasks;

	currentTask = tasks->peek();

	backupQueue = new QueueList<TaskManagerScheduler*>();
}

bool TaskManagerSchedulerOneAfterOne::canExecute()
{
	bool result = currentTask->canExecute();

	if( result )
	{
		backupQueue->push( tasks->pop() );
		if( tasks->isEmpty() ) while( !backupQueue->isEmpty() ) tasks->push( backupQueue->pop() );
		currentTask = tasks->peek();
	}

	return result;
}

bool TaskManagerSchedulerOneAfterOne::canRemoveFromTaskManager()
{
	return currentTask->canRemoveFromTaskManager();
}

TaskManagerSchedulerOneAfterOne::~TaskManagerSchedulerOneAfterOne()
{
	delete( backupQueue );
}

