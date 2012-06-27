/*
 * HeartBeatBuzzerOnOffRestService.h
 *
 *  Created on: 26-04-2012
 *      Author: root
 */

#ifndef HEARTBEATBUZZERONOFFRESTSERVICE_H_
#define HEARTBEATBUZZERONOFFRESTSERVICE_H_

// =================================================

#include <Arduino.h>
//#include <Print.h>

// =================================================

#include "RestService.h"
//#include "Streaming.h"
#include "HeartBeatRunnable.h"

// =================================================

class HeartBeatBuzzerOnOffRestService: public RestService
{
	public:

		HeartBeatBuzzerOnOffRestService( unsigned char _id , const char* _name , HeartBeatRunnable* _heartBeatRunnable );
		void writeValueToStream( Stream* stream );
		bool getBooleanValue();
		void setBooleanValue( bool newValue );

	protected:

		//Print& p;

		HeartBeatRunnable* heartBeatRunnable;
};

// =================================================

#endif /* HEARTBEATBUZZERONOFFRESTSERVICE_H_ */
