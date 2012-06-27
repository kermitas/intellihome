/*
 * HFA11xRS232WiFiCRCStateMachine.cpp
 *
 *  Created on: 21-05-2012
 *      Author: root
 */

// =================================================

#include "RWStateMachine.h"

// =================================================

RWStateMachine::RWStateMachine( AnyBuffer< byte , byte >* _inputBuffer , AnyBuffer< byte , byte >* _outputBuffer , Stream* stream )
	: dp( PSTR( "RWStateMachine" ) ) ,
	  //inputBuffer( _inputBuffer ) ,
	  //outputBuffer( _outputBuffer ) ,
	  crcStream( stream ) ,
	  rwSubTaskWaitForData( stream ) ,
	  rwSubTaskReadSENDACKCommand( _outputBuffer ,  &crcStream , &rwCommandSerialNumber , &rwSubTaskGoBackToFirstSubTask , &rwSubTaskGoBackToFirstSubTask ) ,
	  rwSubTaskSendSENDCommand( _outputBuffer , &crcStream , &rwCommandSerialNumber , &rwSubTaskWaitForData , &rwSubTaskReadSENDACKCommand , &rwSubTaskGoBackToFirstSubTask ) ,
	  rwSubTaskDecideToSendOutgoingData( _outputBuffer , &rwSubTaskSendSENDCommand , &rwSubTaskGoBackToFirstSubTask , 15 ) ,
	  rwSubTaskReadRECVACKCommandData( _inputBuffer , &crcStream , &rwCommandSerialNumber , &rwSubTaskDecideToSendOutgoingData , &rwSubTaskDecideToSendOutgoingData ) ,
	  rwSubTaskReadRECVACKCommandHeader( _inputBuffer , &crcStream , &rwCommandSerialNumber , &rwSubTaskWaitForData , &rwSubTaskReadRECVACKCommandData , &rwSubTaskDecideToSendOutgoingData ) ,
	  rwSubTaskSendRECVCommand( _inputBuffer , &crcStream , &rwCommandSerialNumber , &rwSubTaskWaitForData , &rwSubTaskReadRECVACKCommandHeader , &rwSubTaskDecideToSendOutgoingData ) ,
	  rwSubTaskDecideToReadIncommingData( _inputBuffer , &rwSubTaskSendRECVCommand , &rwSubTaskDecideToSendOutgoingData )
{
	// ---

	_inputBuffer->setPositionAndLimit( 0 , 0 );
	_outputBuffer->setPositionAndLimit( 0 , 0 );

	//rwSubTaskReadSENDACKCommand->setSubTaskOnRetry( &rwSubTaskSendSENDCommand );

	currentState = &rwSubTaskDecideToReadIncommingData;
	goToState( currentState );
}

// =================================================

void RWStateMachine::goToStateWithVerbose( RWSubTask* nextState )
{
	static const PROGMEM prog_char functionName[] = "goToState";

	aln( "current state '%s' will be replaced by '%s'" , currentState->getSubTaskName() , nextState->getSubTaskName() )

	goToState( nextState );

	if( stateTimeoutTime > 0 )
	{
		RWSubTask* stateAfterTimeout = currentState->getStateAfterTimeout();

		aln( "current (new) state '%s' has set timeout to %lums (on timeout will be replaced by '%s')" , currentState->getSubTaskName() , currentState->getStateTimeout() , ( stateAfterTimeout !=NULL ? stateAfterTimeout->getSubTaskName() : "-null-" ) )
	}
}

// =================================================

void RWStateMachine::goToState( RWSubTask* nextState )
{
	currentState = nextState;
	currentState->resetInternalState();

	unsigned long stateTimeout = currentState->getStateTimeout();

	if( stateTimeout > 0 )
	{
		stateTimeoutTime = millis() + stateTimeout;
	}
	else
	{
		stateTimeoutTime = 0;
	}
}

// =================================================

void RWStateMachine::run()
{
	static const PROGMEM prog_char functionName[] = "run";

	if( stateTimeoutTime > 0 && millis() >= stateTimeoutTime )
	{
		wln( "timeout of state '%s'" , currentState->getSubTaskName() )
		RWSubTask* stateAfterTimeout = currentState->getStateAfterTimeout();

		if( stateAfterTimeout == NULL || stateAfterTimeout == &rwSubTaskGoBackToFirstSubTask )
		{
			stateAfterTimeout = &rwSubTaskDecideToReadIncommingData;
		}

		goToStateWithVerbose( stateAfterTimeout != NULL ? stateAfterTimeout : &rwSubTaskDecideToReadIncommingData );
	}
	else
	{
		RWSubTask* nextState = currentState->executeSubTask();

		if( nextState != NULL )
		{
			/*if( nextState == &rwSubTaskGoBackToFirstSubTask )
			{
				goToStateWithVerbose( &rwSubTaskDecideToReadIncommingData );
			}
			else
			{
				goToStateWithVerbose( nextState );
			}*/

			goToStateWithVerbose( nextState == &rwSubTaskGoBackToFirstSubTask ? &rwSubTaskDecideToReadIncommingData : nextState );
		}
		else
		{
			aln( "current state '%s' will be executed in future" , currentState->getSubTaskName() )
		}
	}
}

// =================================================

void RWStateMachine::doFullReadCycle()
{
	// to jest pelny cykl czytajacy
	// otwarty jest od rwSubTaskDecideToReadIncommingData do rwSubTaskDecideToSendOutgoingData

	bool isCycleOpen = false;

	while( true )
	{
		if( !isCycleOpen )
		{
			if( currentState == &rwSubTaskDecideToReadIncommingData ) isCycleOpen = true;
		}
		else
		{
			if( currentState == &rwSubTaskDecideToSendOutgoingData ) return;
		}

		run();
	}
}

// =================================================

void RWStateMachine::doFullSendCycle()
{
	// to jest pelny cykl wysylajacy
	// otwarty jest od rwSubTaskDecideToSendOutgoingData do rwSubTaskDecideToReadIncommingData

	bool isCycleOpen = false;

	while( true )
	{
		if( !isCycleOpen )
		{
			if( currentState == &rwSubTaskDecideToSendOutgoingData ) isCycleOpen = true;
		}
		else
		{
			if( currentState == &rwSubTaskDecideToReadIncommingData ) return;
		}

		run();
	}
}

// =================================================


