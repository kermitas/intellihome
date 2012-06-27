/*
 * ePIRCheckMotionDetectionRunnable.cpp
 *
 *  Created on: 08-01-2012
 *      Author: root
 */

/*
#include "ePIRCheckMotionDetectionRunnable.h"

const char ePIRCheckMotionDetectionRunnable::prefix[] = "ePIRCheckMotionDetectionRunnable:";

ePIRCheckMotionDetectionRunnable::ePIRCheckMotionDetectionRunnable( Print& _p , ePIR* _epir , TaskManager* _taskManager , unsigned int _sleepTime ) : p(_p)
{
	epir = _epir;
	taskManager = _taskManager;
	sleepTime = _sleepTime;

	sleepUntil = 0;

}

void ePIRCheckMotionDetectionRunnable::motionDetected()
{
	p << prefix << "MOTION DETECTED!!" << endl;

	{
		PinHighLowRunnable* ledOnOff = new PinHighLowRunnable( 9 , false );

		TaskManagerMemoryConfigurator* taskMemoryConf = new TaskManagerMemoryConfigurator( true , true , true );

		QueueList<unsigned long>* queue = new QueueList<unsigned long>();
		queue->push( 1 );
		queue->push( sleepTime-10 );

		TaskManagerSchedulerTimeIntervals* taskScheduler = new TaskManagerSchedulerTimeIntervals( queue , false , true );

		taskManager->addTask( taskMemoryConf , taskScheduler , ledOnOff );
	}

	{
		PinHighLowRunnable* beepOnOff = new PinHighLowRunnable( 7 , false );

		TaskManagerMemoryConfigurator* taskMemoryConf = new TaskManagerMemoryConfigurator( true , true , true );

		QueueList<unsigned long>* queue = new QueueList<unsigned long>();
		queue->push( 1 );
		queue->push( 5 );

		TaskManagerSchedulerTimeIntervals* taskScheduler = new TaskManagerSchedulerTimeIntervals( queue , false , true );

		taskManager->addTask( taskMemoryConf , taskScheduler , beepOnOff );
	}
}

void ePIRCheckMotionDetectionRunnable::run()
{
	//Serial.print( "readMotionStatus=" );

	//uint8_t motionStatus = epir->readMotionStatus(); // odbierze 89 jesli ruch

	//uint8_t available = epir->serial->available();

	//bool motionDetected = false;

	while( epir->serial->available() > 0 )
	{
		if( epir->serial->read() == 77 )
		{
			//motionDetected = true;

			if( sleepUntil == 0) motionDetected();

			sleepUntil = millis() + sleepTime;
		}
	}

	if( sleepUntil <= millis() ) sleepUntil = 0;

	//uint8_t readByte = ( available > 0 ? epir->serial->read() : 0 );

	//p << prefix << "available=" << available << ", readByte=" << readByte << endl;

	//p << prefix << "motionDetected=" << motionDetected << ", sleepUntil=" << sleepUntil << ", sleepUntil-millis()=" << sleepUntil-millis() << endl;
	p << prefix << ", sleepUntil=" << sleepUntil << ", sleepUntil-millis()=" << sleepUntil-millis() << endl;

}

ePIRCheckMotionDetectionRunnable::~ePIRCheckMotionDetectionRunnable()
{

}
*/

