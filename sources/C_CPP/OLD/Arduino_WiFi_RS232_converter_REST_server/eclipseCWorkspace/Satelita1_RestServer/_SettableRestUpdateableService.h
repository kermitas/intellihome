/*
 * SettableRestUpdateableService.h
 *
 *  Created on: 12-04-2012
 *      Author: root
 */
/*
#ifndef SETTABLERESTUPDATEABLESERVICE_H_
#define SETTABLERESTUPDATEABLESERVICE_H_

// =================================================

#include <Arduino.h>
#include <Print.h>

// =================================================

#include "RestUpdateableService.h"
#include "Streaming.h"

#include "ValueSetterHTMLGenerator.h"
// =================================================

class SettableRestUpdateableService: public RestUpdateableService
{
	public:

		SettableRestUpdateableService( Print& _p , const char* _name , const char* _value , ValueSetterHTMLGenerator* _valueSetterHTMLGenerator );
		void writeValueToStream( Stream* stream );
		void renderValueSetter( Stream* stream );

	protected:

		Print& p;
		const char* value;
		ValueSetterHTMLGenerator* valueSetterHTMLGenerator;
};

// =================================================

#endif */ /* SETTABLERESTUPDATEABLESERVICE_H_ */
