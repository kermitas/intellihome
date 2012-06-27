/*
 * ConfigureePirRunnable.h
 *
 *  Created on: 08-01-2012
 *      Author: root
 */

/*
#ifndef EPIRCONFIGURERUNNABLE_H_
#define EPIRCONFIGURERUNNABLE_H_

#include "Runnable.h"
#include "ePIR.h"
#include <HardwareSerial.h>
#include <Arduino.h>
//#include "PrinterDebug.h"
#include "ePirOperationResult.h"
#include "Streaming.h"

class ePirConfigureRunnable: public Runnable
{
	public:
		ePirConfigureRunnable(  Print& _p , ePIR* _epir );
		void run();
		virtual ~ePirConfigureRunnable();

		static const char prefix[];

	protected:
		ePIR* epir;
		//PrinterDebug* p;
		Print& p;

		//void printSetStatus( ePirOperationResult* operationResult , const char* settingName , uint8_t newValue );
		//void printSetStatus( ePirOperationResult* operationResult , const char* settingName , bool newValue );
		void printSetStatus( ePirOperationResult* operationResult , const char* settingName );
};

#endif */ /* EPIRCONFIGURERUNNABLE_H_ */
