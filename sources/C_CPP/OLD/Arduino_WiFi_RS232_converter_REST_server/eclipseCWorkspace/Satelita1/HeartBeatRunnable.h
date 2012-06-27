/*
 * HeartBeatRunnable.h
 *
 *  Created on: 03-04-2012
 *      Author: root
 */

#ifndef HEARTBEATRUNNABLE_H_
#define HEARTBEATRUNNABLE_H_

// =================================================

#include <Arduino.h>
//#include <Print.h>

// =================================================

#include "DebugPrinter.h"
//#include "Configuration.c"
#include "PinHighLowRunnable.h"
//#include "Streaming.h"

// =================================================

class HeartBeatRunnable : public Runnable
{
	public:

		HeartBeatRunnable( PinHighLowRunnable* _ledRunnable , bool _isLedOn , PinHighLowRunnable* _buzzerRunnable , bool _isBuzzerOn );
		void run();
		void setLedOn( bool on );
		//bool getLedOn();
		void setBuzzerOn( bool on );
		//bool getBuzzerOn();
		//virtual ~HeartBeatRunnable();

		bool isLedOn;
		bool isBuzzerOn;

	protected:

		//Print& p;
		DebugPrinter dp;

		PinHighLowRunnable* ledRunnable;
		//bool isLedOn;
		PinHighLowRunnable* buzzerRunnable;
		//bool isBuzzerOn;
};

// =================================================

#endif /* HEARTBEATRUNNABLE_H_ */
