/*
 * AlarmLightLed.cpp
 *
 *  Created on: 31-12-2011
 *      Author: as
 */

//#include "WProgram.h"
#include <Arduino.h>
#include "AlarmLightLed.h"

AlarmLightLed::AlarmLightLed(int _pin)
{
	pin = _pin;
	pinMode(pin, OUTPUT);
}

void AlarmLightLed::dot()
{
  digitalWrite(pin, HIGH);
  delay(250);
  digitalWrite(pin, LOW);
  delay(250);
}

AlarmLightLed::~AlarmLightLed()
{

}

