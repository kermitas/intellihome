// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef ArduinoUnderEclipse_H_
#define ArduinoUnderEclipse_H_
#include "Arduino.h"

//add your includes for the project ArduinoUnderEclipse here

	#include "TaskManager.h"
	#include "OneWire.h"

//end of add your includes here

#ifdef __cplusplus
	extern "C"
	{
#endif

		void setup();
		void loop();

#ifdef __cplusplus
	} // extern "C"
#endif

//add your function definitions for the project ArduinoUnderEclipse here

	TaskManager* taskManager;

	void setup2( Print& p , OneWire* oneWire );

	//const char prefix11[] = "setup():";

//Do not add code below this line

#endif /* ArduinoUnderEclipse_H_ */
