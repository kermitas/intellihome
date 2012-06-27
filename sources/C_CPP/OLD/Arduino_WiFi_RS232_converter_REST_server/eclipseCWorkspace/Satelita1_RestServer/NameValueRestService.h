/*
 * NameValueRestService.h
 *
 *  Created on: 10-04-2012
 *      Author: root
 */

#ifndef NameValueRestService_H_
#define NameValueRestService_H_

// =================================================

#include <Arduino.h>
//#include <Print.h>

// =================================================

#include "RestService.h"
//#include "Streaming.h"

// =================================================

class NameValueRestService : public RestService
{
	public:

		NameValueRestService( unsigned char _id , const char* _name , const char* _value );
		void writeValueToStream( Stream* stream );

	protected:

		//Print& p;
		const char* value;
};

// =================================================

#endif /* NameValueRestService_H_ */
