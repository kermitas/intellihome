/*
 * OptexMX40PTCheckRunnable.h
 *
 *  Created on: 19-01-2012
 *      Author: root
 */

#ifndef OPTEXMX40PTCHECKRUNNABLE_H_
#define OPTEXMX40PTCHECKRUNNABLE_H_

#include "Runnable.h"
#include "Streaming.h"
#include <Arduino.h>
#include "PinHighLowRunnable.h"
#include "QueueList.h"
#include "TaskManager.h"
#include "TaskManagerMemoryConfigurator.h"
#include "TaskManagerSchedulerTimeIntervals.h"

class OptexMX40PTCheckRunnable : public Runnable
{
	public:
		static const char prefix[];

		OptexMX40PTCheckRunnable( Print& _p , TaskManager* _taskManager , uint8_t _alarmInputPin , uint8_t _sabotageInputPin , uint8_t _ledDigitalPin , uint8_t _buzzerDigitalPin , unsigned long _alarmOffTimeFromLastMotionDetection );
		void run();
		virtual ~OptexMX40PTCheckRunnable();

	protected:
		Print& p;
		TaskManager* taskManager;
		uint8_t alarmInputPin;
		uint8_t sabotageInputPin;
		uint8_t ledDigitalPin;
		uint8_t buzzerDigitalPin;
		unsigned long alarmOffTimeFromLastMotionDetection;

		bool isAlarmOn;
		unsigned long alarmStopTime;

		bool isSabotageOn;
		TaskManagerSchedulerTimeIntervals* sabotageBuzzerTaskScheduler;
		TaskManagerSchedulerTimeIntervals* sabotageLedTaskScheduler;

		TaskManagerMemoryConfigurator* taskMemoryConf;
		//TaskManagerSchedulerTimeIntervals* alarmBeepTaskScheduler

		unsigned int counter;

		void startAlarm();
		void stopAlarm();
		void startSabotage();
		void stopSabotage();
};

#endif /* OPTEXMX40PTCHECKRUNNABLE_H_ */
