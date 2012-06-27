/*
 * TaskManagerSchedulerOneExecution.cpp
 *
 *  Created on: 08-01-2012
 *      Author: root
 */

#include "TaskManagerSchedulerOneExecution.h"

TaskManagerSchedulerOneExecution::TaskManagerSchedulerOneExecution()
{
}

bool TaskManagerSchedulerOneExecution::canExecute()
{
	return true;
}

bool TaskManagerSchedulerOneExecution::canRemoveFromTaskManager()
{
	return true;
}

TaskManagerSchedulerOneExecution::~TaskManagerSchedulerOneExecution()
{

}

