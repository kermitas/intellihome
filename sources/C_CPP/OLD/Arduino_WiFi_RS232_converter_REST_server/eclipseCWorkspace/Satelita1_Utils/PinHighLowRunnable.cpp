/*
 * LedOnOffRunnable.cpp
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

// =================================================

#include "PinHighLowRunnable.h"
//#include <Arduino.h>

// =================================================

//const PROGMEM prog_char PinHighLowRunnable::className[] = "PinHighLowRunnable";

// =================================================

PinHighLowRunnable::PinHighLowRunnable( unsigned char _pin , bool isStartStateHigh ) : dp( PSTR( "PinHighLowRunnable" ) )//: p(_p)
{
	pin = _pin;

	if( isStartStateHigh )
		state = HIGH;
	else
		state = LOW;

	pinMode( pin , OUTPUT );
	digitalWrite( pin , state );
}

// =================================================

void PinHighLowRunnable::run()
{
	static const PROGMEM prog_char functionName[] = "sendReceiveDataRequest";

	//all( p << "PinHighLowRunnable:run(): changing state of pin " << pin << " from " << ( state ? "HIGH" : "LOW" ) << " to " << ( state ? "LOW" : "HIGH" ) << endl; )
	//all( wpln( "changing state of pin %u from %u to %u" , pin , state , !state ) )
	aln( "changing state of pin %u from %u to %u" , pin , state , !state )

	if( state == HIGH )
		state = LOW;
	else
		state = HIGH;

	digitalWrite( pin , state );
}

// =================================================

unsigned char PinHighLowRunnable::getPin()
{
	return pin;
}

// =================================================

void PinHighLowRunnable::setPin( unsigned char newPin )
{
	static const PROGMEM prog_char functionName[] = "setPin";

	//warning( p << "PinHighLowRunnable:setPin(): this function is not implemented yet! could not set current pin (" << pin << ") to new pin " << newPin << endl; )
	//warning( wpln( "this function is not implemented yet! could not set current pin (%u) to new pin %u" , pin , newPin ) )
	wln( "this function is not implemented yet! could not set current pin (%u) to new pin %u" , pin , newPin )
}

// =================================================

/*int PinHighLowRunnable::getPin()
{
	return pin;
}*/

// =================================================

//PinHighLowRunnable::~PinHighLowRunnable() {}

// =================================================



