/*
 * PinGetterSetterRestService.cpp
 *
 *  Created on: 28-04-2012
 *      Author: root
 */

// =================================================

#include "PinGetterSetterRestService.h"

// =================================================

PinGetterSetterRestService::PinGetterSetterRestService( unsigned char _id , const char* _name , PinGetterSetter* _pinGetterSetter , unsigned char _minimalPinValue , unsigned char _maximalPinValue ) : RestService( _id , _name , REST_SERVICE_TYPE_UPDATEABLE_INT )
{
	pinGetterSetter = _pinGetterSetter;
	minimalPinValue = _minimalPinValue;
	maximalPinValue = _maximalPinValue;
}

// =================================================

void PinGetterSetterRestService::writeValueToStream( Stream* stream )
{
	stream->print( pinGetterSetter->getPin() );
}

// =================================================

int PinGetterSetterRestService::getIntMinValue()
{
	return minimalPinValue;
}

// =================================================

int PinGetterSetterRestService::getIntMaxValue()
{
	return maximalPinValue;
}

// =================================================


