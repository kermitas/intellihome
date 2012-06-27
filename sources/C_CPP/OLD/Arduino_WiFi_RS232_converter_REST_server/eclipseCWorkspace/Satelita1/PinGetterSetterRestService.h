/*
 * PinGetterSetterRestService.h
 *
 *  Created on: 28-04-2012
 *      Author: root
 */

#ifndef PINGETTERSETTERRESTSERVICE_H_
#define PINGETTERSETTERRESTSERVICE_H_

// =================================================

#include <Arduino.h>
//#include <Print.h>

// =================================================

#include "RestService.h"
//#include "Streaming.h"
#include "PinGetterSetter.h"

// =================================================

class PinGetterSetterRestService: public RestService
{
	public:

		PinGetterSetterRestService( unsigned char _id , const char* _name , PinGetterSetter* _pinGetterSetter , unsigned char _minimalPinValue , unsigned char _maximalPinValue );
		void writeValueToStream( Stream* stream );
		int getIntMinValue();
		int getIntMaxValue();

	protected:

		//Print& p;

		PinGetterSetter* pinGetterSetter;
		unsigned char minimalPinValue;
		unsigned char maximalPinValue;
};

// =================================================

#endif /* PINGETTERSETTERRESTSERVICE_H_ */
