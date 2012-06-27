/*
 * Led.h
 *
 *  Created on: 31-12-2011
 *      Author: as
 */

/*
#ifndef LED_H_
#define LED_H_

//#include <Arduino.h>
#include "LoopTaskInterface.h"

class Led : public LoopTaskInterface
{

	public:
		Led(int _pin);
		virtual ~Led();
		void dot( int onTimeInMs , int offTimeInMs );
		void executeLoopTask();

	private:
		int pin;
		//int taskNumber;
		//int dotFrequency;
		LoopTaskInterface *loopTask;

};

#endif /* LED_H_ */

*/
