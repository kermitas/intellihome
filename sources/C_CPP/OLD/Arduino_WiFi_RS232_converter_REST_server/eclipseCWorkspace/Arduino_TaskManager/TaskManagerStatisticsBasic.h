/*
 * TaskManagerStatisticsBasic.h
 *
 *  Created on: 08-01-2012
 *      Author: root
 */

#ifndef TASKMANAGERSTATISTICSBASIC_H_
#define TASKMANAGERSTATISTICSBASIC_H_

#include <Arduino.h>
#include <Print.h>
#include "TaskManagerStatistics.h"

//#include "PrinterSimple.h"
//#include "PrinterDebug.h"

class TaskManagerStatisticsBasic : public TaskManagerStatistics
{
	public:
		TaskManagerStatisticsBasic( Print& _p , unsigned long _statisticsCreationIntervalInMs );

		void beforeTaskQueue();
		void afterTaskQueue( unsigned long howManyTasksWereCheckedInThisIteration , unsigned long howManyTasksWereExecutedInThisIteration , unsigned long howManyTasksWereNotExecutedInThisIteration );

		virtual ~TaskManagerStatisticsBasic();

		static const char prefix[];//="a";//; = "aa";// ( "TM STAT:");// = {'A'};// = "TM STAT:";

	protected:
		//PrinterDebug* p;
		Print& p;


		unsigned long statisticsCreationIntervalInMs;

		unsigned long testStartTime;
		unsigned long executionOfMainLoopStartTime;

		unsigned long mainLoopExecutionsCount;
		unsigned long checkedTasksSum;
		unsigned long executedTasksSum;
		unsigned long notExecutedTasksSum;
		unsigned long timeSum;

		void resetStatistics();
		void printStatistics( unsigned long howManyTasksWereCheckedInThisIteration );
};


#endif /* TASKMANAGERSTATISTICSBASIC_H_ */
