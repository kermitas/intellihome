/*
 * TimeATimeBTaskManagerTaskInfo.cpp
 *
 *  Created on: 05-01-2012
 *      Author: root
 */
/*
#include <Arduino.h>
#include "TimeATimeBTaskManagerTaskExecutionInfo.h"

TimeATimeBTaskManagerTaskExecutionInfo::TimeATimeBTaskManagerTaskExecutionInfo( unsigned int _timeAinMs , unsigned int _timeBinMs , bool _isCyclic ) //: TaskManagerTaskExecutionInfo()//( _canTaskManagerFreeTaskManagerTaskInfo , _canTaskManagerFreeRunnable )
{
	timeAinMs = _timeAinMs;
	timeBinMs = _timeBinMs;
	isCyclic = _isCyclic;

	lastExecutionTime = 0;
	isStateA = false;
	wasExecuted = false;
}

bool TimeATimeBTaskManagerTaskExecutionInfo::canExecute()
{
	bool result = false;

	unsigned long currentMillis = millis();

	if (
			(!isStateA && (currentMillis - lastExecutionTime) > timeBinMs) ||
			(isStateA && (currentMillis - lastExecutionTime) > timeAinMs)
		)
	{
		lastExecutionTime = currentMillis;
		isStateA = !isStateA;

		wasExecuted = true;
		result = true;
	}

	return result;
}

bool TimeATimeBTaskManagerTaskExecutionInfo::canRemoveFromTaskManager()
{
	return !isCyclic && wasExecuted;
}

TimeATimeBTaskManagerTaskExecutionInfo::~TimeATimeBTaskManagerTaskExecutionInfo()
{
}
*/
