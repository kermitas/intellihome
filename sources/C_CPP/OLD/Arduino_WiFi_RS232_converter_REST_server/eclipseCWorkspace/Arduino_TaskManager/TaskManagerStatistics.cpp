/*
 * TaskManagerStatistics.cpp
 *
 *  Created on: 08-01-2012
 *      Author: root
 */

#include "TaskManagerStatistics.h"

TaskManagerStatistics::TaskManagerStatistics() {}

void TaskManagerStatistics::beforeTaskQueue()
{
}

void TaskManagerStatistics::afterTaskQueue( unsigned long howManyTasksWereCheckedInThisIteration , unsigned long howManyTasksWereExecutedInThisIteration , unsigned long howManyTasksWereNotExecutedInThisIteration )
{
}

TaskManagerStatistics::~TaskManagerStatistics() {}

