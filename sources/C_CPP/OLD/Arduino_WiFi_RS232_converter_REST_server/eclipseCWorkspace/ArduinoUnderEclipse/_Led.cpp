/*
 * AlarmLightLed.cpp
 *
 *  Created on: 31-12-2011
 *      Author: as
 */

/*
#include <Arduino.h>
#include "Led.h"
#include "LedDotLoopTask.h"
//#include <stdlib.h>

Led::Led(int _pin)
{
	Serial.print( "new pin=" );
	Serial.print( _pin );

	Serial.print( " prev pin=" );
	Serial.println( pin );



	pin = _pin;
	pinMode(pin, OUTPUT);

	loopTask = 0;

}

void Led::dot( int onTimeInMs , int offTimeInMs )
{


	if( loopTask != NULL )
	{
		Serial.println( "wykonuje DELETE/FREE!!" );
		delete loopTask;
	}

	//Serial.println( sizeof(loopTask) );

	LedDotLoopTask *task = new LedDotLoopTask( pin , onTimeInMs , offTimeInMs );
	loopTask = task;



}

void Led::executeLoopTask()
{

	if( loopTask != NULL ) loopTask->executeLoopTask();
}

Led::~Led()
{
	if( loopTask != NULL ) delete loopTask;
}
*/

