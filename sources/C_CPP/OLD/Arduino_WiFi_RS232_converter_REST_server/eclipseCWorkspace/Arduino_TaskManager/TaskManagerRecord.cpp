/*
 * TaskManagerTaskRecord.cpp
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

#include "TaskManagerRecord.h"

TaskManagerRecord::TaskManagerRecord( TaskManagerMemoryConfigurator* _taskManagerMemoryConfigurator , TaskManagerScheduler* _taskManagerScheduler , Runnable* _runnable )
{
	taskManagerMemoryConfigurator = _taskManagerMemoryConfigurator;
	taskManagerScheduler = _taskManagerScheduler;
	runnable = _runnable;
}

TaskManagerRecord::~TaskManagerRecord()
{
	if( taskManagerMemoryConfigurator->canTaskManagerFreeRunnable() ) delete( runnable );
	if( taskManagerMemoryConfigurator->canTaskManagerFreeScheduler() ) delete( taskManagerScheduler );

	// to zawsze na koncu
	if( taskManagerMemoryConfigurator->canTaskManagerFreeMemoryConfigurator() ) delete( taskManagerMemoryConfigurator );
}

