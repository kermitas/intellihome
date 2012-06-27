/*
 * TimeIntervalTaskManagerTaskExecutionInfo.cpp
 *
 *  Created on: 06-01-2012
 *      Author: root
 */

#include "TaskManagerSchedulerTimeIntervals.h"

TaskManagerSchedulerTimeIntervals::TaskManagerSchedulerTimeIntervals( QueueList<unsigned long>* _timeIntervalsInMs , bool _isCyclic , bool _shouldIFreeQueue )
{
	queueA = _timeIntervalsInMs;
	isCyclic = _isCyclic;
	shouldIFreeQueue = _shouldIFreeQueue;

	queueB = new QueueList<unsigned long>();

	wasWholeQueueExecuted = false;
	lastExecutionTime = 0;
}

void TaskManagerSchedulerTimeIntervals::setCyclic( bool _isCyclic )
{
	isCyclic = _isCyclic;
}

bool TaskManagerSchedulerTimeIntervals::canExecute()
{
	unsigned long currentMillis = millis();

	if( currentMillis - lastExecutionTime > queueA->peek() )
	{
		lastExecutionTime = currentMillis;

		queueB->push( queueA->pop() );

		if( queueA->isEmpty() )
	    {
			while( !queueB->isEmpty() ) queueA->push( queueB->pop() );

			if( !isCyclic ) wasWholeQueueExecuted = true;
	    }

		return true;
	}
	else
		return false;
}

bool TaskManagerSchedulerTimeIntervals::canRemoveFromTaskManager()
{
	//return !isCyclic && wasExecuted;
	return wasWholeQueueExecuted;
}

TaskManagerSchedulerTimeIntervals::~TaskManagerSchedulerTimeIntervals()
{
	//while( !queueB->isEmpty() ) delete( queueB->pop() );
	delete( queueB );

	if( shouldIFreeQueue )
	{
		//while( !queueA->isEmpty() ) delete( queueA->pop() );
		delete( queueA );
	}
}

