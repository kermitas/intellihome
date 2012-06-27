/*
 * HeartBeatBuzzerOnOffRestService.cpp
 *
 *  Created on: 26-04-2012
 *      Author: root
 */

// =================================================

#include "HeartBeatBuzzerOnOffRestService.h"

// =================================================

HeartBeatBuzzerOnOffRestService::HeartBeatBuzzerOnOffRestService( unsigned char _id , const char* _name , HeartBeatRunnable* _heartBeatRunnable ) : RestService( _id , _name , REST_SERVICE_TYPE_UPDATEABLE_BOOLEAN_ONOFF ) //, p(_p)
{
	heartBeatRunnable = _heartBeatRunnable;
}

// =================================================

void HeartBeatBuzzerOnOffRestService::writeValueToStream( Stream* stream )
{
	stream->print( heartBeatRunnable->isBuzzerOn ? "on" : "off" );
}

// =================================================

bool HeartBeatBuzzerOnOffRestService::getBooleanValue()
{
	return heartBeatRunnable->isBuzzerOn;
}

// =================================================

void HeartBeatBuzzerOnOffRestService::setBooleanValue( bool newValue )
{
	if( heartBeatRunnable->isBuzzerOn != newValue ) heartBeatRunnable->setBuzzerOn( newValue );
}

// =================================================


