/*
 * OptexMX40PTCheckRunnable.cpp
 *
 *  Created on: 19-01-2012
 *      Author: root
 */

#include "OptexMX40PTCheckRunnable.h"

const char OptexMX40PTCheckRunnable::prefix[] = "OptexMX40PT:";

OptexMX40PTCheckRunnable::OptexMX40PTCheckRunnable( Print& _p , TaskManager* _taskManager , uint8_t _alarmInputPin , uint8_t _sabotageInputPin , uint8_t _ledDigitalPin , uint8_t _buzzerDigitalPin , unsigned long _alarmOffTimeFromLastMotionDetection ) : p(_p)
{
	taskManager = _taskManager;
	alarmInputPin = _alarmInputPin;
	sabotageInputPin = _sabotageInputPin;
	ledDigitalPin = _ledDigitalPin;
	buzzerDigitalPin = _buzzerDigitalPin;
	alarmOffTimeFromLastMotionDetection = _alarmOffTimeFromLastMotionDetection;

	taskMemoryConf = new TaskManagerMemoryConfigurator( true , true , false );

	/*{
		QueueList<unsigned long>* queue = new QueueList<unsigned long>();
		queue->push( 1 );
		queue->push( 1 );

		alarmBeepTaskScheduler = new TaskManagerSchedulerTimeIntervals( queue , false , false );
	}*/

	pinMode( ledDigitalPin , OUTPUT );
	pinMode( buzzerDigitalPin , OUTPUT );

	digitalWrite( ledDigitalPin , LOW );
	digitalWrite( buzzerDigitalPin , LOW );

	//pinMode( 9 , OUTPUT );

	//pinMode( 22 , INPUT );
	//digitalWrite( 22 , HIGH );

	pinMode( alarmInputPin , INPUT );
	digitalWrite( alarmInputPin , HIGH );

	pinMode( sabotageInputPin , INPUT );
	digitalWrite( sabotageInputPin , HIGH );

	stopSabotage();
	stopAlarm();

	//counter = 5;//50;

}

void OptexMX40PTCheckRunnable::run()
{
	unsigned int digitalReadSabotage = digitalRead( sabotageInputPin );

	//p << prefix << "digitalReadSabotage=" << digitalReadSabotage << endl;

	/*
	counter += 5;

	if( counter >= 230 ) counter = 5;

	analogWrite( 9 , counter );

	//delay( 200 );

	unsigned long v = 0;
	for( int i = 0 ; i < 100 ; i++ )
	{
		delay( 2 );
		v += analogRead( sabotageAnalogPin );
	}

	//counter = counter + 10;
	//if( counter > 220 ) counter = 50;

	p << prefix << "counter=" << counter << endl;

	//analogWrite( 9 , counter );

	unsigned int ncValue = 1;

	unsigned int analogReadValue = analogRead( sabotageAnalogPin );
	p << prefix << "analogRead( sabotageAnalogPin )=" << analogReadValue << " map=" << map(analogReadValue , 0 , 1023 , 0 , 255 ) << " v=" << map( v/100 , 0 , 1023 , 0 , 255 ) << endl;
	*/


	//unsigned int digitalReadValue = digitalRead( sabotageAnalogPin );
	//p << prefix << "digitalRead( sabotageAnalogPin )=" << digitalReadValue << " [HIGH=" << HIGH << ", LOW=" << LOW << "]" << endl;


	//if( analogReadValue < ncValue )
	if( digitalReadSabotage == 1 )
	{
		if( !isSabotageOn )
		{
			stopAlarm();
			startSabotage();
		}
	}
	else
	{
		if( isSabotageOn )
		{
			stopSabotage();
		}
	}

	if( !isSabotageOn )
	{
		//analogReadValue = analogRead( alarmAnalogPin );
		//p << prefix << "analogRead( alarmAnalogPin )=" << analogReadValue << endl;

		//digitalReadValue = digitalRead( alarmAnalogPin );
		//p << prefix << "digitalRead( alarmAnalogPin )=" << digitalReadValue << " [HIGH=" << HIGH << ", LOW=" << LOW << "]" << endl;

		unsigned int digitalReadAlarm = digitalRead( alarmInputPin );
		//p << prefix << "digitalReadAlarm=" << digitalReadAlarm << endl;

		if( digitalReadAlarm == 1 )
		//if( analogReadValue < ncValue )
		{
			if( !isAlarmOn )
			{
				startAlarm();
				alarmStopTime = millis() + alarmOffTimeFromLastMotionDetection;
			}
			else
			{
				alarmStopTime = millis() + alarmOffTimeFromLastMotionDetection;
			}
		}

	}

	if( isAlarmOn && alarmStopTime <= millis() )
	{
		stopAlarm();
	}
}

void OptexMX40PTCheckRunnable::startAlarm()
{
	p << prefix << "ALARM goes ON!!" << endl;
	isAlarmOn = true;

	// puscic raz mini pikniecie buzzerem
	{
		PinHighLowRunnable* beepOnOff = new PinHighLowRunnable( buzzerDigitalPin , false );

		//TaskManagerMemoryConfigurator* taskMemoryConf = new TaskManagerMemoryConfigurator( true , true , true );

		QueueList<unsigned long>* queue = new QueueList<unsigned long>();
		queue->push( 1 );
		queue->push( 1 );

		TaskManagerSchedulerTimeIntervals* alarmBeepTaskScheduler = new TaskManagerSchedulerTimeIntervals( queue , false , true );

		taskManager->addTask( taskMemoryConf , alarmBeepTaskScheduler , beepOnOff );
	}

	// wlaczyc LED na stale
	digitalWrite( ledDigitalPin , HIGH );
}

void OptexMX40PTCheckRunnable::stopAlarm()
{
	if( isAlarmOn ) p << prefix << "ALARM goes OFF!!" << endl;
	isAlarmOn = false;

	alarmStopTime = 0;

	// wylaczyc LED
	digitalWrite( ledDigitalPin , LOW );
}

void OptexMX40PTCheckRunnable::startSabotage()
{
	p << prefix << "SABOTAGE goes ON!!" << endl;

	isSabotageOn = true;

	// start uciazliwe pikanie
	{
		PinHighLowRunnable* buzzerOnOff = new PinHighLowRunnable( buzzerDigitalPin , false );

		//TaskManagerMemoryConfigurator* taskMemoryConf = new TaskManagerMemoryConfigurator( true , true , true );

		QueueList<unsigned long>* queue = new QueueList<unsigned long>();
		queue->push( 1000 );
		queue->push( 1000 );

		sabotageBuzzerTaskScheduler = new TaskManagerSchedulerTimeIntervals( queue , true , true );

		taskManager->addTask( taskMemoryConf , sabotageBuzzerTaskScheduler , buzzerOnOff );
	}

	// start szybkie puslowanie diody
	{
		PinHighLowRunnable* ledOnOff = new PinHighLowRunnable( ledDigitalPin , false );

		//TaskManagerMemoryConfigurator* taskMemoryConf = new TaskManagerMemoryConfigurator( true , true , true );

		QueueList<unsigned long>* queue = new QueueList<unsigned long>();
		queue->push( 100 );
		queue->push( 80 );

		sabotageLedTaskScheduler = new TaskManagerSchedulerTimeIntervals( queue , true , true );

		taskManager->addTask( taskMemoryConf , sabotageLedTaskScheduler , ledOnOff );
	}
}

void OptexMX40PTCheckRunnable::stopSabotage()
{
	if( isSabotageOn ) p << prefix << "SABOTAGE goes OFF!!" << endl;

	isSabotageOn = false;

	// stop buzzer
	if( sabotageBuzzerTaskScheduler != NULL )
	{
		sabotageBuzzerTaskScheduler->setCyclic( false );
		sabotageBuzzerTaskScheduler = 0;
	}

	// stop miganie diody
	if( sabotageLedTaskScheduler != NULL )
	{
		sabotageLedTaskScheduler->setCyclic( false );
		sabotageLedTaskScheduler = 0;
	}
}

OptexMX40PTCheckRunnable::~OptexMX40PTCheckRunnable()
{
	stopSabotage();
	stopAlarm();

	delete( taskMemoryConf );
}

