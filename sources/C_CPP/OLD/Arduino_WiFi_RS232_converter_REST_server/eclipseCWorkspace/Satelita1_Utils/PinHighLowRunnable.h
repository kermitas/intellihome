/*
 * LedOnOffRunnable.h
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

#ifndef PINHIGHLOWRUNNABLE_H_
#define PINHIGHLOWRUNNABLE_H_

// =================================================

#include <Arduino.h>
//#include <Print.h>

// =================================================

//#include "Configuration.c"
#include "DebugPrinter.h"
#include "Runnable.h"
//#include "Streaming.h"
#include "PinGetterSetter.h"

// =================================================

class PinHighLowRunnable : public Runnable , public PinGetterSetter
{
	public:
		PinHighLowRunnable( unsigned char _pin , bool isStartStateHigh );
		void run();
		unsigned char getPin();
		void setPin( unsigned char newPin );
		//virtual ~PinHighLowRunnable();

	protected:
		//Print& p;
		DebugPrinter dp;
		//static const PROGMEM prog_char className[];

		unsigned char pin;
		unsigned int state;
};

// =================================================

#endif /* PINHIGHLOWRUNNABLE_H_ */
