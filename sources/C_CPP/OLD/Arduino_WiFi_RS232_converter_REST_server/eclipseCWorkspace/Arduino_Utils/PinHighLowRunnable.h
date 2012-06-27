/*
 * LedOnOffRunnable.h
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

#ifndef PINHIGHLOWRUNNABLE_H_
#define PINHIGHLOWRUNNABLE_H_

#include <Arduino.h>
#include "Runnable.h"

class PinHighLowRunnable : public Runnable
{
	public:
		PinHighLowRunnable( unsigned int _pin , bool isStartStateHigh );
		void run();
		virtual ~PinHighLowRunnable();

	protected:
		unsigned int pin;
		unsigned int ledState;
};

#endif /* PINHIGHLOWRUNNABLE_H_ */
