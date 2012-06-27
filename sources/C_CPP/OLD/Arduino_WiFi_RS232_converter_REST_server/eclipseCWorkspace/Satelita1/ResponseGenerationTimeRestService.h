/*
 * HtmlOrJsonGenerationTimeRestService.h
 *
 *  Created on: 26-04-2012
 *      Author: root
 */

#ifndef HTMLORJSONGENERATIONTIMERESTSERVICE_H_
#define HTMLORJSONGENERATIONTIMERESTSERVICE_H_

// =================================================

#include "RestService.h"
#include "TimeMeasurement.h"

// =================================================

class ResponseGenerationTimeRestService: public RestService
{
	public:

		ResponseGenerationTimeRestService( unsigned char _id , const char* _name , TimeMeasurement* _pageRendererTimeMeasurement );
		void writeValueToStream( Stream* stream );

	protected:

		TimeMeasurement* pageRendererTimeMeasurement;
};

// =================================================

#endif /* HTMLORJSONGENERATIONTIMERESTSERVICE_H_ */
