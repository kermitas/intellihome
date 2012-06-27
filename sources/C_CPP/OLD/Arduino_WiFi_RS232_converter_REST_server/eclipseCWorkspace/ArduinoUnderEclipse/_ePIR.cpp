/*
 * ePIR.cpp
 *
 *  Created on: 07-01-2012
 *      Author: root
 */

/*
#include "ePIR.h"

#include <Arduino.h>

ePIR::ePIR( HardwareSerial* _serial , unsigned int _blockingOperationCheckIntervalInMs )
{
	serial = _serial;
	blockingOperationCheckIntervalInMs = _blockingOperationCheckIntervalInMs;

	//serial->begin( 4800 );
	serial->begin( 9600 );
}

void ePIR::writeCommand( uint8_t command )
{
	//Serial.print( "before commandd = " );
	//Serial.println( command );

	//int c = command;
	//char c = command;

	while( serial->available() ) serial->read();

	serial->write( command );
	serial->flush();



	//uint8_t ack = 0;
	//serial->print( '\r' );
	//serial->println( ack );

	//Serial.println( "after" );
}

uint8_t ePIR::readMotionStatus()
{
	writeCommand( 'a' );
	//uint8_t c = 97;
	//serial->write( c );

	return blockingReadOneByte();
}

uint8_t ePIR::readApplicationRevision()
{
	writeCommand( 105 );
	//uint8_t c = 105;

	//serial->println( c );
	//char = 'i';
	//Serial.print( "sizeof = " );
	//Serial.println( sizeof("i") );

	//serial->print( "i" );
	int result = blockingReadOneByte();
	blockingReadOneByte();
	return result;
}

uint8_t ePIR::readePirEngineRevision()
{
	writeCommand( 'i' );
	//int command = 'i';
	//serial->print(  "i" );
	blockingReadOneByte();
	return blockingReadOneByte();
}

uint8_t ePIR::readCurrentLightGateInputLevel()
{
	writeCommand( 'b' );
	return blockingReadOneByte();
}

uint8_t ePIR::readMotionDetectionActivationTime()
{
	writeCommand( 'd' );
	return blockingReadOneByte();
}

bool ePIR::readExtendedRangeSetting()
{
	writeCommand( 'e' );
	return blockingReadOneByte() == 89;
}

ePirOperationResult* ePIR::writeExtendedRangeSetting( bool isOn )
{
	return set( 'E' , ( isOn ? 'Y' : 'N' ) );
}

bool ePIR::readReadMotionDetectedUnsolicitedMode()
{
	writeCommand( 'm' );
	return blockingReadOneByte();
}

ePirOperationResult* ePIR::writeReadMotionDetectedUnsolicitedMode( bool isOn )
{
	return set( 'M' , ( isOn ? 'Y' : 'N' ) );
}

uint8_t ePIR::readPulseCount()
{
	writeCommand( 'p' );
	return blockingReadOneByte();
}

ePirOperationResult* ePIR::writePulseCount( bool ifFalseThenOneIfTrueThenTwo )
{
	return set( 'P' , ( ifFalseThenOneIfTrueThenTwo ? 2 : 1 ) );
}

uint8_t ePIR::readDirection()
{
	writeCommand( 'v' );
	return blockingReadOneByte();
}

uint8_t ePIR::readSensivity()
{
	writeCommand( 's' );
	return blockingReadOneByte();
}

ePirOperationResult* ePIR::writeSensivity( uint8_t newValue )
{
	return set( 'S' , newValue );
}


uint8_t ePIR::readLightGateThreshold()
{
	writeCommand( 'l' );
	return blockingReadOneByte();
}

ePirOperationResult* ePIR::writeMotionDetectionActivationTime( uint8_t newValue )
{
	return set( 'D' , newValue );
}

ePirOperationResult* ePIR::writeLightGateThreshold( uint8_t newValue )
{
	return set( 'L' , newValue );
}

uint8_t ePIR::readPin5Mode()
{
	writeCommand( 'c' );
	return blockingReadOneByte();
}

ePirOperationResult* ePIR::setPin5Mode( bool ifTrueThenWorkAsOutputElectricalyMotionDetectionIfFalseThenWorkAsInputReset )
{
	//uint8_t setValue = 'R';

	return set( 'C' , ( ifTrueThenWorkAsOutputElectricalyMotionDetectionIfFalseThenWorkAsInputReset ? 'M' : 'R' ) );
}

void ePIR::printAvailableBuffer()
{
	Serial.print( "serial->available()=" );
	Serial.println( serial->available() );

	while( serial->available()>0 )
	{
		uint8_t b = serial->read();

		Serial.print( " " );
		Serial.println( b );
	}
}

ePirOperationResult* ePIR::set( uint8_t command , uint8_t newValue )
{
	writeCommand( command );

	uint8_t oldValue = blockingReadOneByte();

	writeCommand( newValue );

	return new ePirOperationResult( blockingReadConfirmation() , oldValue , newValue );
}

uint8_t ePIR::blockingReadOneByte()
{
	while( true )
	{
		unsigned int a = serial->available();

		if( a>=1 )
		{
			return serial->read();
		}

		delay( blockingOperationCheckIntervalInMs );
	}

	return 0;
}

bool ePIR::blockingReadConfirmation()
{
	while( true )
	{
		uint8_t b = blockingReadOneByte();

		if( b == 6 )
			return true;
		else
		if( b == 21 )
			return false;
	}

	return 0;
}

ePIR::~ePIR()
{
}
*/
