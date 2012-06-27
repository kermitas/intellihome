/*
 * HeartBeatSpeedRestService.h
 *
 *  Created on: 24-04-2012
 *      Author: root
 */

#ifndef HeartBeatSpeedRestService_H_
#define HeartBeatSpeedRestService_H_

// =================================================

#include <Arduino.h>
//#include <Print.h>

// =================================================

#include "RestService.h"
//#include "Streaming.h"

//#include "ValueSetterHTMLGenerator.h"

// =================================================

class HeartBeatSpeedRestService: public RestService
{
	public:

		HeartBeatSpeedRestService( unsigned char _id , const char* _name , unsigned long* _heartBeatTimeIntervals , unsigned char _indexInArray );
		void writeValueToStream( Stream* stream );
		void setIntValue( int newValue );
		int getIntMinValue();
		int getIntMaxValue();

	protected:

		//Print& p;

		unsigned long* heartBeatTimeIntervals;
		unsigned char indexInArray;
		//ValueSetterHTMLGenerator* valueSetterHTMLGenerator;
};

// =================================================

#endif /* HeartBeatSpeedRestService_H_ */
