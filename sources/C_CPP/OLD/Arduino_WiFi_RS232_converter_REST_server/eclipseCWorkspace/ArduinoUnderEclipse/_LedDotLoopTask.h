/*
 * LedDotLoopTask.h
 *
 *  Created on: 01-01-2012
 *      Author: as
 */

/*
#ifndef LEDDOTLOOPTASK_H_
#define LEDDOTLOOPTASK_H_

//#include <Arduino.h>
#include "LoopTaskInterface.h"

class LedDotLoopTask : public LoopTaskInterface
{
	public:
		LedDotLoopTask(unsigned int _pin , unsigned int _onTimeInMs , unsigned int _offTimeInMs , unsigned int _maximumBlinkCount );
		bool executeLoopTask();
		virtual ~LedDotLoopTask();

	protected:
		unsigned int pin;
		unsigned int onTimeInMs;
		unsigned int offTimeInMs;
		unsigned int maximumBlinkCount;

		unsigned long lastExecutionTime;
		unsigned int ledState;
		unsigned int blinkCount;
};

#endif /* LEDDOTLOOPTASK_H_ */

