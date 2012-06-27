/*
 * TaskManagerLogicTaskExecutionInfo.cpp
 *
 *  Created on: 06-01-2012
 *      Author: root
 */

#include "TaskManagerSchedulerAndOr.h"

TaskManagerSchedulerAndOr::TaskManagerSchedulerAndOr( QueueList<TaskManagerScheduler*>* _tasks , bool _ifTrueThenANDifFalseThenOR )
{
	tasks = _tasks;
	ifTrueThenANDifFalseThenOR = _ifTrueThenANDifFalseThenOR;
}

bool TaskManagerSchedulerAndOr::doAction( bool ifTrueDoCanExecuteIfFalseDoCanRemoveFromTaskManager )
{
	QueueList<TaskManagerScheduler*>* q = new QueueList<TaskManagerScheduler*>();

	bool result;

	TaskManagerScheduler* task = tasks->pop();

	if( ifTrueDoCanExecuteIfFalseDoCanRemoveFromTaskManager )
		result = task->canExecute();
	else
		result = task->canRemoveFromTaskManager();

	q->push( task );

	if( ifTrueThenANDifFalseThenOR )
	{
		while( !tasks->isEmpty() )
		{
			task = tasks->pop();

			if( ifTrueDoCanExecuteIfFalseDoCanRemoveFromTaskManager )
				result = result && task->canExecute();
			else
				result = result && task->canRemoveFromTaskManager();

			q->push( task );
		}
	}
	else
	{
		while( !tasks->isEmpty() )
		{
			task = tasks->pop();

			if( ifTrueDoCanExecuteIfFalseDoCanRemoveFromTaskManager )
				result = result || task->canExecute();
			else
				result = result || task->canRemoveFromTaskManager();

			q->push( task );
		}
	}

	while( !q->isEmpty() ) tasks->push( q->pop() );

	delete( q );

	return result;
}

bool TaskManagerSchedulerAndOr::canExecute()
{
	return doAction( true );
}

bool TaskManagerSchedulerAndOr::canRemoveFromTaskManager()
{
	return doAction( false );
}

TaskManagerSchedulerAndOr::~TaskManagerSchedulerAndOr() {}

