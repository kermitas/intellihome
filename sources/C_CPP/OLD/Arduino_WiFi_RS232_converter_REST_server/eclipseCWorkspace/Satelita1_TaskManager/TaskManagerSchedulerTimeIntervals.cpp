/*
 * TimeIntervalTaskManagerTaskExecutionInfo.cpp
 *
 *  Created on: 06-01-2012
 *      Author: root
 */

#include "TaskManagerSchedulerTimeIntervals.h"

// =================================================

//const PROGMEM prog_char TaskManagerSchedulerTimeIntervals::className[] = "TaskManagerSchedulerTimeIntervals";

// =================================================

TaskManagerSchedulerTimeIntervals::TaskManagerSchedulerTimeIntervals( unsigned long* _timeIntervalsInMs , unsigned char _timeIntervalsCount , bool _isCyclic ) : dp( PSTR( "TaskManagerSchedulerTimeIntervals" ) )//: p(_p)
{
	timeIntervalsInMs = _timeIntervalsInMs;
	timeIntervalsCount = _timeIntervalsCount;
	isCyclic = _isCyclic;

	resetState();
}

// =================================================

void TaskManagerSchedulerTimeIntervals::resetState()
{
	lastExecutionTime = 0;
	executionTaskCounter = -1;
	wasAllTasksExecuted = false;
}

// =================================================

bool TaskManagerSchedulerTimeIntervals::canExecute()
{
	static const PROGMEM prog_char functionName[] = "canExecute";

	unsigned long currentMillis = millis();

	if( executionTaskCounter < 0 || currentMillis - lastExecutionTime >= timeIntervalsInMs[ executionTaskCounter ] )
	{
		lastExecutionTime = currentMillis;

		executionTaskCounter++;

		if( executionTaskCounter >= timeIntervalsCount )
		{
			executionTaskCounter = 0;

			if( !isCyclic ) wasAllTasksExecuted = true;
		}

		//all( p << "TaskManagerSchedulerTimeIntervals:canExecute(): returning TRUE, next execution in " << timeIntervalsInMs[ executionTaskCounter ] << "ms, (wasAllTasksExecuted=" << wasAllTasksExecuted << ")" << endl )

		//all( p << "TaskManagerSchedulerTimeIntervals:canExecute(): returning TRUE, "; )
		//all( wp( "returning TRUE," )  )
		a( "returning TRUE," )

			//p << "TaskManagerSchedulerTimeIntervals:canExecute(): returning TRUE, ";

			if( wasAllTasksExecuted )
			{
				//all( p << "will not be executed again, will request to be removed from TaskManager"; )
				//all( wp( "will not be executed again, will request to be removed from TaskManager" )  )
				a( "will not be executed again, will request to be removed from TaskManager" )
			//	;
			}
			else
			{
				//all( p << " will be executed again in " << timeIntervalsInMs[ executionTaskCounter ] << "ms"; )
				//all( wp( " will be executed again in %ums" , timeIntervalsInMs[ executionTaskCounter ] )  )
				a( " will be executed again in %ums" , timeIntervalsInMs[ executionTaskCounter ] )
			//	;
			}

		//{};
			//all( p << endl; )
			//all( wpln( "" )  )
			aln( "" )
		//)

		//all( p << ( wasAllTasksExecuted ? ( " will not be executed again, will request to be removed from TaskManager" ) : ( " will be executed again in " << timeIntervalsInMs[ executionTaskCounter ] << "ms" ) ) )

		//all( p << endl )

		return true;
	}
	else
		return false;
}

// =================================================

bool TaskManagerSchedulerTimeIntervals::canRemoveFromTaskManager()
{
	static const PROGMEM prog_char functionName[] = "canRemoveFromTaskManager";

	//all( p << "TaskManagerSchedulerTimeIntervals:canRemoveFromTaskManager(): returning " << wasAllTasksExecuted << endl; )
	//all( wpln( "returning %u" , wasAllTasksExecuted ) )
	aln( "returning %u" , wasAllTasksExecuted )

	if( wasAllTasksExecuted )
	{
		resetState();
		return true;
	}
	else
		return false;
}

// =================================================

//TaskManagerSchedulerTimeIntervals::~TaskManagerSchedulerTimeIntervals() {}

// =================================================

