/*
 * LedOnOffRunnable.cpp
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

#include "PinHighLowRunnable.h"

PinHighLowRunnable::PinHighLowRunnable( unsigned int _pin , bool isStartStateHigh )
{
	pin = _pin;

	if( isStartStateHigh )
		ledState = HIGH;
	else
		ledState = LOW;

	pinMode( pin , OUTPUT );
	digitalWrite( pin , ledState );
}

void PinHighLowRunnable::run()
{
	if( ledState == HIGH )
		ledState = LOW;
	else
		ledState = HIGH;

	digitalWrite( pin , ledState );
}

PinHighLowRunnable::~PinHighLowRunnable()
{

}


