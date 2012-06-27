/*
 * DeterminateHttpMethodSubTask.h
 *
 *  Created on: 17-04-2012
 *      Author: root
 */

#ifndef DETERMINATEHTTPMETHODSUBTASK_H_
#define DETERMINATEHTTPMETHODSUBTASK_H_

// =================================================

#include <Arduino.h>
//#include <Print.h>

// =================================================

#include "RestServerSubTask.h"
//#include "Streaming.h"
#include "DebugPrinter.h"
#include "SkipBytesUntilSequenceSubTask.h"
#include "ReadHttpPathSubTask.h"
#include "StreamReadHttpMethod.h"

// =================================================

class DeterminateHttpMethodSubTask : public RestServerSubTask
{
	public:

		DeterminateHttpMethodSubTask( RestServerSubTask* _errorSubTask , SkipBytesUntilSequenceSubTask* _skipBytesUntilSequenceSubTask , ReadHttpPathSubTask* _readHttpPathSubTask );

		char* getSubTaskName();
		void resetInternalState();
		RestServerSubTask* executeSubTask( Stream* stream );

	protected:

		//Print& p;
		DebugPrinter dp;

		RestServerSubTask* errorSubTask;
		SkipBytesUntilSequenceSubTask* skipBytesUntilSequenceSubTask;
		ReadHttpPathSubTask* readHttpPathSubTask;

		StreamReadHttpMethod streamReadHttpMethod;

};

// =================================================

#endif /* DETERMINATEHTTPMETHODSUBTASK_H_ */
