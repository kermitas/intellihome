/*
 * ErrorSubTask.cpp
 *
 *  Created on: 22-04-2012
 *      Author: root
 */

// =================================================

#include "ErrorSubTask.h"

// =================================================

char* ErrorSubTask::getSubTaskName()
{
	return "Error-sub-task";
}

// =================================================

void ErrorSubTask::resetInternalState() {}

// =================================================

RestServerSubTask* ErrorSubTask::executeSubTask( Stream* stream )
{
	return NULL;
}

// =================================================


