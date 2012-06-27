/*
 * LedOnOffRunnable.cpp
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

#include "CheckDallasDS18B20TemperatureRunnable.h"

const char CheckDallasDS18B20TemperatureRunnable::prefix[] = "DS18B20:";

CheckDallasDS18B20TemperatureRunnable::CheckDallasDS18B20TemperatureRunnable( OneWire* _oneWire , Print& _p ) : p(_p)
{
	oneWire = _oneWire;

	//oneWire = new OneWire( digitalOneWirePinNumber );

	sensors = new DallasTemperature( oneWire );



	//p << prefix << "Found " << sensors->getDeviceCount() << " devices." << endl;

	  // locate devices on the bus
	  Serial.print("Locating devices...");
	  sensors->begin();

	  Serial.print("Found ");
	  Serial.print(sensors->getDeviceCount(), DEC);
	  Serial.println(" devices.");

	// report parasite power requirements
	  Serial.print("Parasite power is: ");
	  if (sensors->isParasitePowerMode()) Serial.println("ON");
	  else Serial.println("OFF");

/*
	  DeviceAddress insideThermometer;

	  if (!sensors->getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0");

	  // show the addresses we found on the bus
	    Serial.print("Device 0 Address: ");
	    //printAddress(insideThermometer);



	    for (uint8_t i = 0; i < 8; i++)
	    {
	      if (insideThermometer[i] < 16) Serial.print("0");
	      Serial.print(insideThermometer[i], HEX);
	      deviceAddress[i]=insideThermometer[i];
	    }

	    Serial.println();
	    */

	    //Device 0 Address: 28 0C F8 55 03 00 00 46
	  //uint8_t da[8] = { 0x28, 0x0C , 0xF8, 0x55, 0x03, 0x0, 0x0, 0x46 };
	  //deviceAddress = { 0x28, 0x0C , 0xF8, 0x55, 0x03, 0x0, 0x0, 0x46 };

	    deviceAddress[0] = 0x28;
	    deviceAddress[1] = 0x0C;
	    deviceAddress[2] = 0xF8;
	    deviceAddress[3] = 0x55;
	    deviceAddress[4] = 0x03;
	    deviceAddress[5] = 0x0;
	    deviceAddress[6] = 0x0;
	    deviceAddress[7] = 0x46;

	    /*for (uint8_t i = 0; i < 8; i++)
	    {
	      //if (deviceAddress[i] < 16) Serial.print("0");
	      //Serial.print(deviceAddress[i], HEX);
	    	deviceAddress[i] = (uint8_t *) malloc( sizeof( uint8_t ) );
	    }

	    deviceAddress[0] = (uint8_t) 0x28;
	    deviceAddress[1] = 0x0C;
	    deviceAddress[2] = 0xF8;
	    deviceAddress[3] = 0x55;
	    deviceAddress[4] = 0x03;
	    deviceAddress[5] = 0x0;
	    deviceAddress[6] = 0x0;
	    deviceAddress[7] = 0x46;*/

	    //for (uint8_t i = 0; i < 8; i++)
	    //{
	    //  if (deviceAddress[i] < 16) Serial.print("0");
	    //  Serial.print(deviceAddress[i], HEX);
	    //}

	    //Serial.println();

	    sensors->setResolution(deviceAddress, 9);

	    Serial.print("Device 0 Resolution: ");
	    Serial.print(sensors->getResolution(deviceAddress), DEC);
	    Serial.println();

}

void CheckDallasDS18B20TemperatureRunnable::run()
{
	//int tempInC = 0;


	sensors->requestTemperatures();

	  //float tempInC = sensors->getTempC(deviceAddress);
	  //Serial.print("Temp C: ");
	  //Serial.println(tempC);

	  p << prefix << sensors->getTempC(deviceAddress) << " oC" << endl;
}

CheckDallasDS18B20TemperatureRunnable::~CheckDallasDS18B20TemperatureRunnable()
{

}


