/*
 * TimeMeasurement.h
 *
 *  Created on: 26-04-2012
 *      Author: root
 */

#ifndef TimeMeasurement_H_
#define TimeMeasurement_H_

// =================================================

#include <Arduino.h>

// =================================================

class TimeMeasurement
{
	public:

		void saveTime();
		unsigned long getTimePeriod();

	protected:

		unsigned long savedTime;
};

// =================================================

#endif /* TimeMeasurement_H_ */
