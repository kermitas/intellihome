/*
 * HtmlOrJsonGenerationTimeRestService.cpp
 *
 *  Created on: 26-04-2012
 *      Author: root
 */

// =================================================

#include "ResponseGenerationTimeRestService.h"

// =================================================

ResponseGenerationTimeRestService::ResponseGenerationTimeRestService( unsigned char _id , const char* _name , TimeMeasurement* _pageRendererTimeMeasurement ) : RestService( _id , _name , REST_SERVICE_TYPE_READ_ONLY )
{
	pageRendererTimeMeasurement = _pageRendererTimeMeasurement;
}

// =================================================

void ResponseGenerationTimeRestService::writeValueToStream( Stream* stream )
{
	stream->print( pageRendererTimeMeasurement->getTimePeriod() );
}

// =================================================


