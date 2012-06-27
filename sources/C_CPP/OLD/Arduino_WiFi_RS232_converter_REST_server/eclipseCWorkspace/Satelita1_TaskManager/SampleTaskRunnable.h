/*
 * LedOnOffRunnable.h
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

#ifndef SampleTaskRunnable_H_
#define SampleTaskRunnable_H_

// =================================================

#include <Arduino.h>
//#include <Print.h>

// =================================================

//#include "Configuration.c"
#include "DebugPrinter.h"
#include "Runnable.h"
//#include "Streaming.h"

// =================================================

class SampleTaskRunnable : public Runnable
{
	public:

		SampleTaskRunnable( const PROGMEM prog_char* _str , unsigned short _sleepInMs );
		void run();
		//~SampleTaskRunnable();

	protected:

		//Print& p;
		DebugPrinter dp;
		//static const PROGMEM prog_char className[];

		const PROGMEM prog_char* str;
		unsigned short sleepInMs;
};

// =================================================

#endif /* SampleTaskRunnable_H_ */
