/*
 * ResetRestService.cpp
 *
 *  Created on: 28-04-2012
 *      Author: root
 */

// =================================================

#include "ResetRestService.h"

// =================================================

ResetRestService::ResetRestService( unsigned char _id , const char* _name ) : dp( PSTR( "ResetRestService" ) ) , RestService( _id , _name , REST_SERVICE_TYPE_UPDATEABLE_BOOLEAN_ONE_TIME_EXECUTION )
{

}

// =================================================

void ResetRestService::setBooleanValue( bool newValue )
{
	static const PROGMEM prog_char functionName[] = "setBooleanValue";

	//warning( p << "ResetRestService:setBooleanValue():" << "RESETTING DEVICE!" << endl; )
	wln( "RESETTING DEVICE!" )

	// TODO : zresetowanie
}

// =================================================


