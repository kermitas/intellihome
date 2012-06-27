/*
 * TaskManager.h
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

#ifndef TASKMANAGER_H_
#define TASKMANAGER_H_

// =================================================

#include <Arduino.h>
//#include <Print.h>

// =================================================

//#include "Configuration.c"
#include "DebugPrinter.h"
//#include "Streaming.h"
#include "TaskManagerRecord.h"

// =================================================

class TaskManager
{
	public:

		TaskManager( unsigned int _maxTasksCount , const TaskManagerRecord** _tasksArray );//, Print& _p );
		bool add( TaskManagerRecord* taskManagerRecord );
		void execute();
		const TaskManagerRecord* removeByIndex( unsigned int index );
		bool removeByPointer( TaskManagerRecord* ptr );
		unsigned int getIndex( TaskManagerRecord* ptr );
		virtual ~TaskManager();

	protected:

		//Print& p;
		DebugPrinter dp;
		//static const PROGMEM prog_char className[];

		unsigned int maxTasksCount;
		unsigned int currentTasksCount;
		const TaskManagerRecord** tasksArray;


		void recompactTaskArray();
		void printTasksArray();

	private:

		static const char executeFunctionPrefix[];
		unsigned int executeFunction_forLoopCounter;
		bool executeFunction_executeRecompactTaskArray;
};

// =================================================

#endif /* TASKMANAGER_H_ */
