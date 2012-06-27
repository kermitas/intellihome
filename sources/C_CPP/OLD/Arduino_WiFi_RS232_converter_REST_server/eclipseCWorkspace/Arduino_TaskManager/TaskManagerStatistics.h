/*
 * TaskManagerStatistics.h
 *
 *  Created on: 08-01-2012
 *      Author: root
 */

#ifndef TASKMANAGERSTATISTICS_H_
#define TASKMANAGERSTATISTICS_H_

class TaskManagerStatistics
{
	public:
		TaskManagerStatistics();

		virtual void beforeTaskQueue();
		virtual void afterTaskQueue( unsigned long howManyTasksWereCheckedInThisIteration , unsigned long howManyTasksWereExecutedInThisIteration , unsigned long howManyTasksWereNotExecutedInThisIteration );

		virtual ~TaskManagerStatistics();
};

#endif /* TASKMANAGERSTATISTICS_H_ */
