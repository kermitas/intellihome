/*
 * HeartBeatRunnable.cpp
 *
 *  Created on: 03-04-2012
 *      Author: root
 */

// =================================================

#include "HeartBeatRunnable.h"

// =================================================

HeartBeatRunnable::HeartBeatRunnable( PinHighLowRunnable* _ledRunnable , bool _isLedOn , PinHighLowRunnable* _buzzerRunnable , bool _isBuzzerOn ) : dp( PSTR( "HeartBeatRunnable" ) )
{
	ledRunnable = _ledRunnable;
	isLedOn = _isLedOn;
	buzzerRunnable = _buzzerRunnable;
	isBuzzerOn = _isBuzzerOn;
}

// =================================================

void HeartBeatRunnable::setLedOn( bool on )
{
	static const PROGMEM prog_char functionName[] = "setLedOn";

	//all( p << "HeartBeatRunnable:setLedOn():" << "setting led from " << isLedOn << " to " << on << endl; );
	aln( "setting led from %u to %u" , isLedOn , on )

	isLedOn = on;
}

// =================================================

/*
bool HeartBeatRunnable::getLedOn()
{
	return isLedOn;
}*/

// =================================================

void HeartBeatRunnable::setBuzzerOn( bool on )
{
	static const PROGMEM prog_char functionName[] = "setBuzzerOn";

	//all( p << "HeartBeatRunnable:setLedOn():" << "setting buzzer from " << isBuzzerOn << " to " << on << endl; );
	aln( "setting buzzer from %u to %u" , isBuzzerOn , on )

	isBuzzerOn = on;
}

// =================================================

/*
bool HeartBeatRunnable::getBuzzerOn()
{
	return isBuzzerOn;
}*/

// =================================================

void HeartBeatRunnable::run()
{
	static const PROGMEM prog_char functionName[] = "run";

	//all( p << "HeartBeatRunnable:run():isLedOn=" << isLedOn << ", isBuzzerOn=" << isBuzzerOn << endl; )
	aln( "isLedOn = %u, isBuzzerOn = %u" , isLedOn , isBuzzerOn )

	if( ledRunnable != NULL )
	{
		if( isLedOn || digitalRead( ledRunnable->getPin() )  == HIGH ) ledRunnable->run();
	}

	if( buzzerRunnable != NULL )
	{
		if( isBuzzerOn || digitalRead( buzzerRunnable->getPin() ) == HIGH ) buzzerRunnable->run();
	}
}

// =================================================

//HeartBeatRunnable::~HeartBeatRunnable() {}

// =================================================



