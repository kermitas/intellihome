/*
 * NameValueRestService.cpp
 *
 *  Created on: 10-04-2012
 *      Author: root
 */

// =================================================

#include "NameValueRestService.h"

// =================================================

NameValueRestService::NameValueRestService( unsigned char _id , const char* _name , const char* _value ) : RestService( _id , _name , REST_SERVICE_TYPE_READ_ONLY ) //, p(_p)
{
	value = _value;
}

// =================================================

void NameValueRestService::writeValueToStream( Stream* stream )
{
	stream->write( value );
}

// =================================================


