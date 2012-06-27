/*
 * ePIR.h
 *
 *  Created on: 07-01-2012
 *      Author: root
 */

/*
#ifndef EPIR_H_
#define EPIR_H_

#include <HardwareSerial.h>
#include "ePirOperationResult.h"
//#include <Arduino.h>

class ePIR
{
	public:
		HardwareSerial* serial;

		ePIR( HardwareSerial* _serial , unsigned int _blockingOperationCheckIntervalInMs );

		//HardwareSerial* getSerial();

		uint8_t readMotionStatus();
		uint8_t readApplicationRevision();
		uint8_t readePirEngineRevision();
		uint8_t readCurrentLightGateInputLevel();

		bool readReadMotionDetectedUnsolicitedMode();
		ePirOperationResult* writeReadMotionDetectedUnsolicitedMode( bool isOn );

		bool readExtendedRangeSetting();
		ePirOperationResult* writeExtendedRangeSetting( bool isOn );

		uint8_t readMotionDetectionActivationTime();
		ePirOperationResult* writeMotionDetectionActivationTime( uint8_t newValue );

		uint8_t readLightGateThreshold();
		ePirOperationResult* writeLightGateThreshold( uint8_t newValue );

		uint8_t readDirection();

		uint8_t readSensivity();
		ePirOperationResult* writeSensivity( uint8_t newValue );

		uint8_t readPulseCount();
		ePirOperationResult* writePulseCount( bool ifFalseThenOneIfTrueThenTwo );

		uint8_t readPin5Mode();
		ePirOperationResult* setPin5Mode( bool ifTrueThenWorkAsOutputElectricalyMotionDetectionIfFalseThenWorkAsInputReset );

		void printAvailableBuffer();

		virtual ~ePIR();

	protected:

		unsigned int blockingOperationCheckIntervalInMs;

		void writeCommand( uint8_t command );
		uint8_t blockingReadOneByte();
		bool blockingReadConfirmation();
		ePirOperationResult* set( uint8_t command , uint8_t newValue );
};


#endif *//* EPIR_H_ */
