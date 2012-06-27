/*
 * TaskManagerTaskRecord.h
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

#ifndef BASICTASKMANAGERSCHEDULER_H_
#define BASICTASKMANAGERSCHEDULER_H_

// =================================================

#include "TaskManagerScheduler.h"

// =================================================

class BasicTaskManagerScheduler : public TaskManagerScheduler
{
	public:
		BasicTaskManagerScheduler( bool _canExecute , bool _canRemoveFromTaskManager );

		bool canExecute();
		bool canRemoveFromTaskManager();

		void setCanExecute( bool _canExecute );
		void setCanRemoveFromTaskManager( bool _canRemoveFromTaskManager );

		//virtual ~BasicTaskManagerScheduler();

	protected:

		bool canExecuteValue;
		bool canRemoveFromTaskManagerValue;
};

// =================================================

#endif /* BASICTASKMANAGERSCHEDULER_H_ */
