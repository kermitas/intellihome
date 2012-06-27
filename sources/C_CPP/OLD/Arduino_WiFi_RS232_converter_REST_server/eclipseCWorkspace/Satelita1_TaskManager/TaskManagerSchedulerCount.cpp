/*
 * TaskManagerSchedulerCount.cpp
 *
 *  Created on: 06-01-2012
 *      Author: root
 */

#include "TaskManagerSchedulerCount.h"

// =================================================

//const PROGMEM prog_char TaskManagerSchedulerCount::className[] = "TaskManagerSchedulerCount";

// =================================================

TaskManagerSchedulerCount::TaskManagerSchedulerCount( unsigned long _executionCount ) : dp( PSTR( "TaskManagerSchedulerCount" ) )//: p(_p)
{
	executionCount = _executionCount;
	currentExecutionCount = 0;
}

// =================================================

bool TaskManagerSchedulerCount::canExecute()
{
	static const PROGMEM prog_char functionName[] = "canExecute";

	bool result = ++currentExecutionCount <= executionCount;

	//all( p << "TaskManagerSchedulerCount:canExecute():returning " << result << ", current exexecution number = " << currentExecutionCount << ", maximum executions count = " << executionCount << endl; )
	//all( wpln( "returning %u, current exexecution number = %u, maximum executions count = %u" , result , currentExecutionCount , executionCount ) )
	aln( "returning %u, current exexecution number = %u, maximum executions count = %u" , result , currentExecutionCount , executionCount )

	return result;
}

// =================================================

bool TaskManagerSchedulerCount::canRemoveFromTaskManager()
{
	static const PROGMEM prog_char functionName[] = "canRemoveFromTaskManager";

	if( currentExecutionCount > executionCount )
	{
		//all( p << "TaskManagerSchedulerCount:canRemoveFromTaskManager():removing" << endl; )
		//all( wpln( "removing" ) )
		aln( "removing" )

		currentExecutionCount = 0;
		return true;
	}
	else
		return false;
}

// =================================================

//TaskManagerSchedulerCount::~TaskManagerSchedulerCount() {}

// =================================================

