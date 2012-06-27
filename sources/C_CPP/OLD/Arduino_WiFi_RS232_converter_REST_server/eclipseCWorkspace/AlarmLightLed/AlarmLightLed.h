/*
 * AlarmLightLed.h
 *
 *  Created on: 31-12-2011
 *      Author: as
 */

#ifndef ALARMLIGHTLED_H_
#define ALARMLIGHTLED_H_

#include <Arduino.h>

class AlarmLightLed
{

	public:
		AlarmLightLed(int _pin);
		virtual ~AlarmLightLed();
		void dot();

	private:
		int pin;

};

#endif /* ALARMLIGHTLED_H_ */

