/*
 * LocalTimeRestService.cpp
 *
 *  Created on: 24-04-2012
 *      Author: root
 */

// =================================================

#include "LocalTimeRestService.h"

// =================================================

LocalTimeRestService::LocalTimeRestService( unsigned char _id , const char* _name , bool _printAsDdHhMmSs ) : RestService( _id , _name , REST_SERVICE_TYPE_READ_ONLY )
{
	printAsDdHhMmSs = _printAsDdHhMmSs;
}

// =================================================

void LocalTimeRestService::writeValueToStream( Stream* stream )
{
	if( printAsDdHhMmSs )
	{
		static const unsigned long day = 86400000; // 86400000 milliseconds in a day
		static const unsigned long hour = 3600000; // 3600000 milliseconds in an hour
		static const unsigned long minute = 60000; // 60000 milliseconds in a minute
		static const unsigned long second =  1000; // 1000 milliseconds in a second

		unsigned long timeNow = millis();

		unsigned int days = timeNow / day ;                                //number of days
		unsigned int hours = (timeNow % day) / hour;                       //the remainder from days division (in milliseconds) divided by hours, this gives the full hours
		unsigned int minutes = ((timeNow % day) % hour) / minute ;         //and so on...
		unsigned int seconds = (((timeNow % day) % hour) % minute) / second;

		stream->print( days , DEC );

		stream->write( ":" );

		stream->print( hours , DEC );

		stream->write( ":" );

		stream->print( minutes , DEC );

		stream->write( ":" );

		stream->print( seconds , DEC );
	}
	else
	{
		stream->print( millis() );
	}
}

// =================================================


