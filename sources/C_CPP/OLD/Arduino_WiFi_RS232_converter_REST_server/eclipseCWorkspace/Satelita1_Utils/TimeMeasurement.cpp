/*
 * TimeMeasurement.cpp
 *
 *  Created on: 26-04-2012
 *      Author: root
 */

// =================================================

#include "TimeMeasurement.h"

// =================================================

void TimeMeasurement::saveTime()
{
	savedTime = millis();
}

// =================================================

unsigned long TimeMeasurement::getTimePeriod()
{
	return millis() - savedTime;
}

// =================================================



