/*
 * TaskManagerTaskRecord.cpp
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

#include "TaskManagerRecord.h"

// =================================================

TaskManagerRecord::TaskManagerRecord( TaskManagerScheduler* _scheduler , Runnable* _runnable )
{
	scheduler = _scheduler;
	runnable = _runnable;
}

// =================================================

//TaskManagerRecord::~TaskManagerRecord() {}

// =================================================
