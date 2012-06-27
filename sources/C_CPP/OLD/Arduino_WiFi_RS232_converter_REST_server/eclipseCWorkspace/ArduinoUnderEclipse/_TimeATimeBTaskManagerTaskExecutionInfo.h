/*
 * TimeATimeBTaskManagerTaskInfo.h
 *
 *  Created on: 05-01-2012
 *      Author: root
 */
/*
#ifndef TIMEATIMEBTASKMANAGERTASKEXECUTIONINFO_H_
#define TIMEATIMEBTASKMANAGERTASKEXECUTIONINFO_H_

#include "TaskManagerTaskExecutionInfo.h"

class TimeATimeBTaskManagerTaskExecutionInfo : public TaskManagerTaskExecutionInfo
{
	public:
		TimeATimeBTaskManagerTaskExecutionInfo( unsigned int _timeAinMs , unsigned int _timeBinMs , bool _isCyclic );// : TaskManagerTaskInfo( _canTaskManagerDeleteTaskManagerTaskInfo1 , _canTaskManagerDeleteRunnable1 );//{}
		bool canExecute();
		bool canRemoveFromTaskManager();
		virtual ~TimeATimeBTaskManagerTaskExecutionInfo();

	protected:
		unsigned int timeAinMs;
		unsigned int timeBinMs;
		bool isCyclic;
		unsigned long lastExecutionTime;
		bool isStateA;
		bool wasExecuted;
};

#endif*/ /* TIMEATIMEBTASKMANAGERTASKEXECUTIONINFO_H_ */
