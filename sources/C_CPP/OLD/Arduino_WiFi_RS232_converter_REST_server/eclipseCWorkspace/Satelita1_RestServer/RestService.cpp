/*
 * RestService.cpp
 *
 *  Created on: 12-04-2012
 *      Author: root
 */

// =================================================

#include "RestService.h"

// =================================================

RestService::RestService( unsigned char _id , const char* _name , unsigned char _type )
{
	id = _id;
	name = _name;
	type = _type;
}

// =================================================

void RestService::writeValueToStream( Stream* stream ) {}

// =================================================

void RestService::renderValueSetter( Stream* stream , bool useGETHttpMethodInForms ) {}

// =================================================

bool RestService::getBooleanValue() { return false; }

// =================================================

void RestService::setTextValue( unsigned char* newValue ) {}

// =================================================

void RestService::setBooleanValue( bool newValue ) {}

// =================================================

void RestService::setIntValue( int newValue ) {}

// =================================================

int RestService::getIntMinValue() { return 0; }

// =================================================

int RestService::getIntMaxValue() { return 1; }

// =================================================



