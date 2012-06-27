/*
 * HeartBeatLedOnOffRestService.cpp
 *
 *  Created on: 26-04-2012
 *      Author: root
 */

// =================================================

#include "HeartBeatLedOnOffRestService.h"

// =================================================

HeartBeatLedOnOffRestService::HeartBeatLedOnOffRestService( unsigned char _id , const char* _name , HeartBeatRunnable* _heartBeatRunnable ) : RestService( _id , _name , REST_SERVICE_TYPE_UPDATEABLE_BOOLEAN_ONOFF ) //, p(_p)
{
	heartBeatRunnable = _heartBeatRunnable;
}

// =================================================

void HeartBeatLedOnOffRestService::writeValueToStream( Stream* stream )
{
	stream->print( heartBeatRunnable->isLedOn ? "on" : "off" );
}

// =================================================

bool HeartBeatLedOnOffRestService::getBooleanValue()
{
	return heartBeatRunnable->isLedOn;
}

// =================================================

void HeartBeatLedOnOffRestService::setBooleanValue( bool newValue )
{
	if( heartBeatRunnable->isLedOn != newValue ) heartBeatRunnable->setLedOn( newValue );
}

// =================================================


