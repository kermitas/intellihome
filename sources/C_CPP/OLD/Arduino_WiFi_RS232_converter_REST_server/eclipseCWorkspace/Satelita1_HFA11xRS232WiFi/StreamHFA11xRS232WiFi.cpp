/*
 * StreamHFA11xRS232WiFi.cpp
 *
 *  Created on: 11-05-2012
 *      Author: root
 */

// =================================================

#include "StreamHFA11xRS232WiFi.h"

// =================================================

StreamHFA11xRS232WiFi::StreamHFA11xRS232WiFi( AnyBuffer< byte , byte >* _inputBuffer , AnyBuffer< byte , byte >* _outputBuffer , RWStateMachine* _rwStateMachine ) : dp( PSTR( "StreamHFA11xRS232WiFi" ) )
{
	inputBuffer = _inputBuffer;
	outputBuffer = _outputBuffer;
	rwStateMachine = _rwStateMachine;
}

// =================================================

int StreamHFA11xRS232WiFi::read()
{
	if( inputBuffer->getRemaining() == 0 ) rwStateMachine->doFullReadCycle();

	if( inputBuffer->getRemaining() > 0 )
	{
		return inputBuffer->get();
	}
	else
	{
		return -1;
	}
}

// =================================================

int StreamHFA11xRS232WiFi::peek()
{
	if( inputBuffer->getRemaining() == 0 ) rwStateMachine->doFullReadCycle();

	if( inputBuffer->getRemaining() > 0 )
	{
		return inputBuffer->array[ inputBuffer->position ];
	}
	else
	{
		return -1;
	}
}

// =================================================

void StreamHFA11xRS232WiFi::flush()
{
	//while( outputBuffer->limit != 0 ) rwStateMachine->doFullSendCycle();
	while( outputBuffer->getRemaining() > 0 ) rwStateMachine->doFullSendCycle();

	//if( outputBuffer->getRemaining() > 0 ) rwStateMachine->doFullSendCycle();
}

// =================================================

size_t StreamHFA11xRS232WiFi::write( uint8_t b )
{
	while( outputBuffer->getUnusedSpace() == 0 ) rwStateMachine->doFullSendCycle();

	outputBuffer->array[ outputBuffer->limit++ ] = b;

	return 1;

	/*
	if( outputBuffer->getUnusedSpace() == 0 ) rwStateMachine->doFullSendCycle();

	if( outputBuffer->getUnusedSpace() > 0 )
	{
		outputBuffer->array[ outputBuffer->limit++ ] = b;

		return 1;
	}
	else
	{
		return 0;
	}
	*/
}

// =================================================

size_t StreamHFA11xRS232WiFi::write( const uint8_t* buffer , size_t size )
{
	size_t oryginalSize = size;

	while( size > 0 )
	{
		while( outputBuffer->getUnusedSpace() == 0 ) rwStateMachine->doFullSendCycle();

		byte sizeToWrite = min( outputBuffer->getUnusedSpace() , size );

		byte positionBefore = outputBuffer->position;

		outputBuffer->setPositionAndLimit( outputBuffer->limit , outputBuffer->limit + sizeToWrite );

		outputBuffer->put( (byte*)buffer , sizeToWrite );

		outputBuffer->setPosition( positionBefore );

		size -= sizeToWrite;
	}

	return oryginalSize;

	/*
	if( outputBuffer->getUnusedSpace() == 0 ) rwStateMachine->doFullSendCycle();

	if( outputBuffer->getUnusedSpace() == 0 )
	{
		byte sizeToWrite = min( outputBuffer->getUnusedSpace() , size );

		byte positionBefore = outputBuffer->position;

		outputBuffer->setPositionAndLimit( outputBuffer->limit , outputBuffer->limit + sizeToWrite );

		outputBuffer->put( (byte*)buffer , sizeToWrite );

		outputBuffer->setPosition( positionBefore );

		return sizeToWrite;
	}
	else
		return 0;
	*/
	/*
	if( outputBuffer->getUnusedSpace() == 0 ) rwStateMachine->doFullSendCycle();

	size_t countToWrite = min( size , outputBuffer->getUnusedSpace() );

	memcpy( outputBuffer->array+outputBuffer->limit , buffer , countToWrite );

	outputBuffer->limit += countToWrite;

	return countToWrite;
	*/
}

// =================================================

int StreamHFA11xRS232WiFi::available()
{
	return inputBuffer->getRemaining();
}

// =================================================