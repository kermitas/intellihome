/*
 * ResetRestService.h
 *
 *  Created on: 28-04-2012
 *      Author: root
 */

#ifndef RESETRESTSERVICE_H_
#define RESETRESTSERVICE_H_

// =================================================

#include <Arduino.h>
//#include <Print.h>

// =================================================

//#include "Configuration.c"
#include "RestService.h"
#include "DebugPrinter.h"
//#include "Streaming.h"

// =================================================

class ResetRestService: public RestService
{
	public:

		ResetRestService( unsigned char _id , const char* _name );
		void setBooleanValue( bool newValue );

	protected:

		//Print& p;
		DebugPrinter dp;
};

// =================================================

#endif /* RESETRESTSERVICE_H_ */
