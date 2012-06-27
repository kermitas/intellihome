/*
 * RestServerSubTask.h
 *
 *  Created on: 05-04-2012
 *      Author: root
 */

#ifndef RestServerSubTask_H_
#define RestServerSubTask_H_

// =================================================

class RestServerSubTask
{
	public:

		virtual char* getSubTaskName() = 0;
		virtual void resetInternalState() = 0;
		virtual RestServerSubTask* executeSubTask( Stream* stream ) = 0;
};

// =================================================

#endif /* RestServerSubTask_H_ */
