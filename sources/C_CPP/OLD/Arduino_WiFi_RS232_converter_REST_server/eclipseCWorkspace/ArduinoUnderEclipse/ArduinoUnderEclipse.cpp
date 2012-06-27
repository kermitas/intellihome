#include "ArduinoUnderEclipse.h"
#include <Arduino.h>
//#include "LoopTaskInterface.h"
//#include "LedDotLoopTask.h"
//#include "TimeATimeBTaskManagerTaskExecutionInfo.h"
//#include "TaskManagerMemoryConfigurator.h"
#include "TaskManagerSchedulerTimeIntervals.h"
#include "TaskManagerSchedulerAndOr.h"
#include "TaskManagerSchedulerOneAfterOne.h"
#include "PinHighLowRunnable.h"
//#include "QueueList.h"
//#include "TaskManager.h"
//#include <stdlib.h>
#include "MemoryFree.h"
//#include "ePIR.h"
#include "TaskManagerStatisticsBasic.h"
//#include "ePIRCheckMotionDetectionRunnable.h"
//#include "ePirConfigureRunnable.h"
#include "TaskManagerSchedulerOneExecution.h"
//#include "PrinterSimple.h"
//#include "PrinterDebug.h"
//#include "InternalEEPROM.h"
//#include "EEPROMData.h"
//#include "InternalEEPROMIdDataOrganisation.h"

//#include "/home/as/ARDUINO/arduino-1.0-IDE/libraries/Streaming4/Streaming.h"
#include "Streaming.h"
//#include "OptexMX40PTCheckRunnable.h"
#include "CheckDallasDS18B20TemperatureRunnable.h"
//#include "SdFat/SdFat.h"
#include "SD.h"

// =============================

void setup()
{
	// ---------------

	Serial.begin(9600);

	char prefix[] = "setup():";

	Print& p = Serial;

	// ---------------

	uint8_t digitalOneWirePinNumber = 2;
	OneWire* oneWire = new OneWire( digitalOneWirePinNumber );

	// ---------------

	p << prefix << hl;

	delay( 2 * 1000 );

	p << prefix << "START" << endl;

	p << prefix << "freeRamMemory()=" << freeRamMemory() << endl;
	p << prefix << "millis()=" << millis() << endl;
	p << prefix << hl;

	// ---------------

	TaskManagerStatisticsBasic* taskManagerStatisticsBasic = new TaskManagerStatisticsBasic( p , 10 * 1000 );
	taskManager = new TaskManager( taskManagerStatisticsBasic );

	// ---------------

	setup2( p , oneWire );

	// ---------------

	p << prefix << "freeRamMemory()=" << freeRamMemory() << endl;
	p << prefix << "millis()=" << millis() << endl;
	p << prefix << "END" << endl << hl;

	// ---------------
}

// =============================

void setup2( Print& p , OneWire* oneWire )
{
	// ---------------

	analogReference( DEFAULT );

	// ---------------

	//TaskManagerSchedulerOneExecution* taskSchedulerOneExecution = new TaskManagerSchedulerOneExecution();
	//TaskManagerMemoryConfigurator* taskMemoryConfFreeRunnable = new TaskManagerMemoryConfigurator( false , true , false );
	//TaskManagerMemoryConfigurator* taskMemoryConfFreeSchedulerAndRunnable = new TaskManagerMemoryConfigurator( false , true , false );

	//TaskManagerSchedulerOneExecution taskSchedulerOneExecution();
	//TaskManagerMemoryConfigurator taskMemoryConfOnlyFreeRunnable( false , true , false );

	// ---------------

	/*{
		QueueList<unsigned long>* queue = new QueueList<unsigned long>();
		queue->push( 200 );

		TaskManagerSchedulerTimeIntervals* taskScheduler = new TaskManagerSchedulerTimeIntervals( queue , true , true );

		uint8_t alarmInputPin = 22;//0;
		uint8_t sabotageInputPin = 23;//1;

		uint8_t ledDigitalPin = 7;
		uint8_t buzzerDigitalPin = 8;

		unsigned long alarmOffTimeFromLastMotionDetection = 5 * 1000;

		OptexMX40PTCheckRunnable* runnable = new OptexMX40PTCheckRunnable( p , taskManager , alarmInputPin , sabotageInputPin , ledDigitalPin , buzzerDigitalPin , alarmOffTimeFromLastMotionDetection );

		taskManager->addTask( taskMemoryConfFreeSchedulerAndRunnable , taskScheduler , runnable );
	}*/

	// ---------------

	/*{
		QueueList<unsigned long>* queue = new QueueList<unsigned long>();
		queue->push( 1000 );
		queue->push( 10 );

		TaskManagerSchedulerTimeIntervals* taskScheduler = new TaskManagerSchedulerTimeIntervals( queue , true , true );

		uint8_t ledDigitalPin = 13;

		PinHighLowRunnable* runnable = new PinHighLowRunnable( ledDigitalPin , false );

		taskManager->addTask( true , true , taskScheduler , runnable );
	}*/

	// ---------------
	/*
	{
		char prefix1[] = "setupSDcard:";

		p << prefix1 << "Initializing SD card..." << endl;

		uint8_t chipSelect = SS_PIN;
		SdFat sd;

		char name[] = "APPEND.TXT";

		if (!sd.init(SPI_HALF_SPEED, chipSelect))
		{
			p << prefix1 << "Problem while initializing SD :(" << endl;
		}
		else
		{
			p << prefix1 << "SD initialized :)" << endl;

			ofstream sdout(name, ios::out | ios::app);

			if (!sdout)
			{
				p << prefix1 << "Problem while oppening file on SD card :(" << endl;
			}
			else
			{
				p << prefix1 << "File on SD card oppened :)" << endl;

				sdout.close();
			}
		}
	}*/

	// ---------------

	{
		char prefix1[] = "setupSDcard:";

		p << prefix1 << "Initializing SD card BEGIN..." << endl;

		uint8_t chipSelect = 10;
		pinMode( chipSelect , OUTPUT );


		if (!SD.begin(chipSelect))
		{
			p << prefix1 << "Problem while initializing SD :(" << endl;
		}
		else
		{
			p << prefix1 << "SD initialized :)" << endl;
		}

		p << prefix1 << "Initializing SD card END..." << endl;
	}

	// ---------------

	{
		QueueList<unsigned long>* queue = new QueueList<unsigned long>();
		queue->push( 1000 );

		TaskManagerSchedulerTimeIntervals* taskScheduler = new TaskManagerSchedulerTimeIntervals( queue , true , true );

		CheckDallasDS18B20TemperatureRunnable* runnable = new CheckDallasDS18B20TemperatureRunnable( oneWire , p );

		taskManager->addTask( true , true , taskScheduler , runnable );
	}

	// ---------------

}

// =============================

void loop()
{
	// ------------

	taskManager->execute();

	// ------------
}

// =============================

