/*
 * ConfigureePirRunnable.cpp
 *
 *  Created on: 08-01-2012
 *      Author: root
 */

/*
#include "ePirConfigureRunnable.h"

const char ePirConfigureRunnable::prefix[] = "ePirConf:";

ePirConfigureRunnable::ePirConfigureRunnable(  Print& _p , ePIR* _epir ) : p(_p)
{
	epir = _epir;

	//p = new PrinterDebug( ps , "ePirConf" );
}

void ePirConfigureRunnable::printSetStatus( ePirOperationResult* operationResult , const char* settingName  )
{
	p << prefix << settingName << " [" << (operationResult->isSuccessful?"OK":"ERR") << "] : oldValue=" << operationResult->oldValue << ", newValue=" << operationResult->oldValue << endl;

}

void ePirConfigureRunnable::run()
{
	p << prefix << hl;

	p << prefix << "readApplicationRevision=" << epir->readApplicationRevision() <<  endl;
	p << prefix << "readePirEngineRevision=" << epir->readePirEngineRevision() <<  endl;
	p << prefix << "readCurrentLightGateInputLevel=" << epir->readCurrentLightGateInputLevel() <<  endl;
	p << prefix << "readMotionStatus=" << epir->readMotionStatus() <<  endl;

	p << prefix << "readLightGateThreshold=" << epir->readLightGateThreshold() <<  endl;
	p << prefix << "readPin5Mode=" << epir->readPin5Mode() <<  endl;
	p << prefix << "readMotionDetectionActivationTime=" << epir->readMotionDetectionActivationTime() <<  endl;
	p << prefix << "readExtendedRangeSetting=" << epir->readExtendedRangeSetting() <<  endl;
	p << prefix << "readPulseCount=" << epir->readPulseCount() <<  endl;
	p << prefix << "readSensivity=" << epir->readSensivity() <<  endl;
	p << prefix << "readDirection=" << epir->readDirection() <<  endl;
	p << prefix << "readReadMotionDetectedUnsolicitedMode=" << epir->readReadMotionDetectedUnsolicitedMode() <<  endl;

	p << prefix << hl;

	{
		bool newValue = true;
		ePirOperationResult* operationResult = epir->writeReadMotionDetectedUnsolicitedMode( newValue );
		printSetStatus( operationResult , "writeReadMotionDetectedUnsolicitedMode" );
		delete( operationResult );
	}

	{
		bool newValue = true;
		ePirOperationResult* operationResult = epir->setPin5Mode( newValue );
		printSetStatus( operationResult , "setPin5Mode" );
		delete( operationResult );
	}

	{
		uint8_t newValue = 50;
		ePirOperationResult* operationResult = epir->writeSensivity( newValue );
		printSetStatus( operationResult , "writeSensivity" );
		delete( operationResult );
	}

	{
		bool newValue = true;
		ePirOperationResult* operationResult = epir->writePulseCount( newValue );
		printSetStatus( operationResult , "writePulseCount" );
		delete( operationResult );
	}

	{
		uint8_t newValue = 100;
		ePirOperationResult* operationResult = epir->writeLightGateThreshold( newValue );
		printSetStatus( operationResult , "writeLightGateThreshold" );
		delete( operationResult );
	}

	{
		uint8_t newValue = 1;
		ePirOperationResult* operationResult = epir->writeMotionDetectionActivationTime( newValue );
		printSetStatus( operationResult , "writeMotionDetectionActivationTime" );
		delete( operationResult );
	}

	{
		bool newValue = true;
		ePirOperationResult* operationResult = epir->writeExtendedRangeSetting( newValue );
		printSetStatus( operationResult , "writeExtendedRangeSetting" );
		delete( operationResult );
	}

	p << prefix << hl;
	//p->ps->printHorizontalLine();
}

ePirConfigureRunnable::~ePirConfigureRunnable()
{
	//delete( p );
}
*/

