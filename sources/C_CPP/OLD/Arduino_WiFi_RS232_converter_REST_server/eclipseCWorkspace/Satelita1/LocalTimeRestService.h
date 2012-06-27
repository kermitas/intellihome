/*
 * LocalTimeRestService.h
 *
 *  Created on: 24-04-2012
 *      Author: root
 */

#ifndef LocalTimeRestService_H_
#define LocalTimeRestService_H_

// =================================================

#include <Arduino.h>
//#include <Print.h>

// =================================================

#include "RestService.h"
//#include "Streaming.h"

// =================================================

class LocalTimeRestService: public RestService
{
	public:

		LocalTimeRestService( unsigned char _id , const char* _name , bool _printAsDdHhMmSs );
		void writeValueToStream( Stream* stream );

	protected:

		//Print& p;
		bool printAsDdHhMmSs;
};

// =================================================

#endif /* LocalTimeRestService_H_ */
