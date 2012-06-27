/*
 * TaskManagerTaskInfo.cpp
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

// =================================================

#include "BasicTaskManagerScheduler.h"

// =================================================

BasicTaskManagerScheduler::BasicTaskManagerScheduler( bool _canExecute , bool _canRemoveFromTaskManager )
{
	canExecuteValue = _canExecute;
	canRemoveFromTaskManagerValue = _canRemoveFromTaskManager;
}

// =================================================

bool BasicTaskManagerScheduler::canExecute()
{
	return canExecuteValue;
}

// =================================================

bool BasicTaskManagerScheduler::canRemoveFromTaskManager()
{
	return canRemoveFromTaskManagerValue;
}

// =================================================

void BasicTaskManagerScheduler::setCanExecute( bool _canExecute )
{
	canExecuteValue = _canExecute;
}

// =================================================

void BasicTaskManagerScheduler::setCanRemoveFromTaskManager( bool _canRemoveFromTaskManager )
{
	canRemoveFromTaskManagerValue = _canRemoveFromTaskManager;
}

// =================================================

//BasicTaskManagerScheduler::~BasicTaskManagerScheduler() {}

// =================================================
