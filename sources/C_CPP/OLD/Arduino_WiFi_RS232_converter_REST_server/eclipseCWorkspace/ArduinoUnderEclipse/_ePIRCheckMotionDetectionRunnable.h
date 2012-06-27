/*
 * ePIRCheckMotionDetectionRunnable.h
 *
 *  Created on: 08-01-2012
 *      Author: root
 */

/*
#ifndef EPIRCHECKMOTIONDETECTIONRUNNABLE_H_
#define EPIRCHECKMOTIONDETECTIONRUNNABLE_H_

#include <Arduino.h>
#include "Runnable.h"
#include "ePIR.h"
#include "TaskManager.h"
#include "PinHighLowRunnable.h"
#include "TaskManagerMemoryConfigurator.h"
#include "QueueList.h"
#include "TaskManagerSchedulerTimeIntervals.h"
#include "Streaming.h"

class ePIRCheckMotionDetectionRunnable: public Runnable
{
	public:
		ePIRCheckMotionDetectionRunnable( Print& _p , ePIR* _epir , TaskManager* _taskManager , unsigned int _sleepTime );
		void run();
		virtual ~ePIRCheckMotionDetectionRunnable();

		static const char prefix[];

	protected:
		Print& p;
		ePIR* epir;
		TaskManager* taskManager;
		unsigned int sleepTime;
		unsigned long sleepUntil;

		void motionDetected();
};

#endif*/ /* EPIRCHECKMOTIONDETECTIONRUNNABLE_H_ */
