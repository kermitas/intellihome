/*
 * ErrorSubTask.h
 *
 *  Created on: 22-04-2012
 *      Author: root
 */

#ifndef ERRORSUBTASK_H_
#define ERRORSUBTASK_H_

// =================================================

#include <Arduino.h>

// =================================================

#include "RestServerSubTask.h"

// =================================================

class ErrorSubTask : public RestServerSubTask
{
	public:

		char* getSubTaskName();
		void resetInternalState();
		RestServerSubTask* executeSubTask( Stream* stream );

};

// =================================================

#endif /* ERRORSUBTASK_H_ */
