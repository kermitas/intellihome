/*
 * TaskManagerTaskMemoryInfo.h
 *
 *  Created on: 06-01-2012
 *      Author: root
 */

#ifndef TASKMANAGERMEMORYCONFIGURATOR_H_
#define TASKMANAGERMEMORYCONFIGURATOR_H_

class TaskManagerMemoryConfigurator
{
	public:
		TaskManagerMemoryConfigurator( bool _canTaskManagerFreeScheduler , bool _canTaskManagerFreeRunnable , bool _canTaskManagerFreeMemoryInfo );

		bool canTaskManagerFreeScheduler();
		bool canTaskManagerFreeRunnable();
		bool canTaskManagerFreeMemoryConfigurator();

		virtual ~TaskManagerMemoryConfigurator();

	protected:
		bool _canTaskManagerFreeScheduler;
		bool _canTaskManagerFreeRunnable;
		bool _canTaskManagerFreeMemoryConfigurator;
};

#endif /* TASKMANAGERMEMORYCONFIGURATOR_H_ */
