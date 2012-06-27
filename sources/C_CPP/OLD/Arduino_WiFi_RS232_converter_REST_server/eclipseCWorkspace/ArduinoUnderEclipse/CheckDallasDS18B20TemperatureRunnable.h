/*
 * LedOnOffRunnable.h
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

#ifndef CheckDallasDS18B20TemperatureRunnable_H_
#define CheckDallasDS18B20TemperatureRunnable_H_

#include <Arduino.h>
#include "Runnable.h"
#include "Streaming.h"
#include "OneWire.h"
#include "DallasTemperature.h"

class CheckDallasDS18B20TemperatureRunnable : public Runnable
{
	public:
		CheckDallasDS18B20TemperatureRunnable( OneWire* _oneWire , Print& _p );
		void run();
		virtual ~CheckDallasDS18B20TemperatureRunnable();

		static const char prefix[];

	protected:
		//unsigned int digitalOneWirePinNumber;
		Print& p;
		OneWire* oneWire;
		DallasTemperature* sensors;
		DeviceAddress deviceAddress;
		//uint8_t* deviceAddress[];
};

#endif /* CheckDallasDS18B20TemperatureRunnable_H_ */
