/*
 * HeartBeatSpeedRestService.cpp
 *
 *  Created on: 24-04-2012
 *      Author: root
 */

// =================================================

#include "HeartBeatSpeedRestService.h"

// =================================================

HeartBeatSpeedRestService::HeartBeatSpeedRestService( unsigned char _id , const char* _name , unsigned long* _heartBeatTimeIntervals , unsigned char _indexInArray ) : RestService( _id , _name , REST_SERVICE_TYPE_UPDATEABLE_INT ) //, p(_p)
{
	heartBeatTimeIntervals = _heartBeatTimeIntervals;
	indexInArray = _indexInArray;
	//valueSetterHTMLGenerator = _valueSetterHTMLGenerator;
}

// =================================================

void HeartBeatSpeedRestService::writeValueToStream( Stream* stream )
{
	stream->print( heartBeatTimeIntervals[ indexInArray ] );
}

// =================================================

void HeartBeatSpeedRestService::setIntValue( int newValue )
{
	unsigned long newValueAsLong = newValue;

	heartBeatTimeIntervals[ indexInArray ] = newValueAsLong;
}

// =================================================

int HeartBeatSpeedRestService::getIntMinValue()
{
	return 25;
}

// =================================================

int HeartBeatSpeedRestService::getIntMaxValue()
{
	return 32767;
}

// =================================================


