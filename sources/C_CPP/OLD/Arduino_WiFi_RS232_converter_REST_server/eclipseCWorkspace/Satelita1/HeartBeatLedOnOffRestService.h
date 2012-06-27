/*
 * HeartBeatLedOnOffRestService.h
 *
 *  Created on: 26-04-2012
 *      Author: root
 */

#ifndef HEARTBEATLEDONOFFRESTSERVICE_H_
#define HEARTBEATLEDONOFFRESTSERVICE_H_

// =================================================

#include <Arduino.h>
//#include <Print.h>

// =================================================

#include "RestService.h"
//#include "Streaming.h"
#include "HeartBeatRunnable.h"

// =================================================

class HeartBeatLedOnOffRestService: public RestService
{
	public:

		HeartBeatLedOnOffRestService( unsigned char _id , const char* _name , HeartBeatRunnable* _heartBeatRunnable );
		void writeValueToStream( Stream* stream );
		bool getBooleanValue();
		void setBooleanValue( bool newValue );

	protected:

		//Print& p;

		HeartBeatRunnable* heartBeatRunnable;
};

// =================================================

#endif /* HEARTBEATLEDONOFFRESTSERVICE_H_ */