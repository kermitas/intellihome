/*
 * LedDotLoopTask.cpp
 *
 *  Created on: 01-01-2012
 *      Author: as
 */
/*
#include <Arduino.h>
#include "LedDotLoopTask.h"

LedDotLoopTask::LedDotLoopTask(unsigned int _pin , unsigned int _onTimeInMs , unsigned int _offTimeInMs , unsigned int _maximumBlinkCount )
{
	pin = _pin;
	onTimeInMs = _onTimeInMs;
	offTimeInMs = _offTimeInMs;
	maximumBlinkCount = _maximumBlinkCount;

	lastExecutionTime = 0;
	ledState = LOW;
	blinkCount = 0;

	pinMode(pin, OUTPUT);

	//executeLoopTask();
}

bool LedDotLoopTask::executeLoopTask()
{
	unsigned long currentMillis = millis();

	bool result = true;

	if ( ledState == LOW && (currentMillis - lastExecutionTime) > offTimeInMs )
	{
		lastExecutionTime = currentMillis;
		ledState = HIGH;
		digitalWrite( pin , ledState );
	}
	else
	if ( ledState == HIGH && (currentMillis - lastExecutionTime) > onTimeInMs )
	{
		lastExecutionTime = currentMillis;
		ledState = LOW;
		digitalWrite( pin , ledState );

		if( maximumBlinkCount>0 )
		{
			blinkCount++;
			result = blinkCount<maximumBlinkCount;
		}
	}

	return result;


}

LedDotLoopTask::~LedDotLoopTask()
{
	// TODO Auto-generated destructor stub
}
*/
