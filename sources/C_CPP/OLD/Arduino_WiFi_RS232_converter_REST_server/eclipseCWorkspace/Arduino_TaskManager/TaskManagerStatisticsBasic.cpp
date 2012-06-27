/*
 * TaskManagerStatisticsBasic.cpp
 *
 *  Created on: 08-01-2012
 *      Author: root
 */

#include "TaskManagerStatisticsBasic.h"

#include "Streaming.h"
#include "MemoryFree.h"

const char TaskManagerStatisticsBasic::prefix[] = "TM STAT:";

TaskManagerStatisticsBasic::TaskManagerStatisticsBasic( Print& _p , unsigned long _statisticsCreationIntervalInMs ) : p(_p)
{
	statisticsCreationIntervalInMs = _statisticsCreationIntervalInMs;

	//p = new PrinterDebug( ps , "TM STAT" );
	//Print& p1;
	//Print* p1;

	//p1 = &Serial;
	//p = *p1;
	//pr( "TM STAT:");
	//pr = ("ab");
	//char a[] = "abc";

	//char aprefix[] = { 'T' , 'M' , ' ' , 'S' , 'T' , 'A' , 'T' , ':' };

	//prefix = a;

	resetStatistics();
}

void TaskManagerStatisticsBasic::beforeTaskQueue()
{
	executionOfMainLoopStartTime = millis();
}

void TaskManagerStatisticsBasic::afterTaskQueue( unsigned long howManyTasksWereCheckedInThisIteration , unsigned long howManyTasksWereExecutedInThisIteration , unsigned long howManyTasksWereNotExecutedInThisIteration )
{
	timeSum += millis() - executionOfMainLoopStartTime;

	mainLoopExecutionsCount++;

	checkedTasksSum += howManyTasksWereCheckedInThisIteration;
	executedTasksSum += howManyTasksWereExecutedInThisIteration;
	notExecutedTasksSum += howManyTasksWereNotExecutedInThisIteration;

	if( millis() - testStartTime > statisticsCreationIntervalInMs )
	{
		printStatistics( howManyTasksWereCheckedInThisIteration );
		resetStatistics();
	}
}

void TaskManagerStatisticsBasic::printStatistics( unsigned long howManyTasksWereCheckedInThisIteration )
{
	//char prefix[] = { 'T' , 'M' , ' ' , 'S' , 'T' , 'A' , 'T' , ':' };

	p << prefix << hl;
	p << prefix << "freeRamMemory()=" << freeRamMemory() << " B" << endl;
	p << prefix << "millis()=" << millis() << endl;

	p << prefix << "statisticsCreationIntervalInMs=" << statisticsCreationIntervalInMs << endl;

	p << prefix << "timeSum" << timeSum << endl;
	p << prefix << "mainLoopExecutionsCount=" << mainLoopExecutionsCount << endl;

	float f1 = timeSum;
	float f2 = mainLoopExecutionsCount;
	float f = f1/f2;
	p << prefix << "timeSum/mainLoopExecutionsCount=" << f << endl;

	p << prefix << "checkedTasksSum=" << checkedTasksSum << endl;
	p << prefix << "executedTasksSum=" << executedTasksSum << endl;
	p << prefix << "notExecutedTasksSum=" << notExecutedTasksSum << endl;
	p << prefix << "tasks queued in task manager=" << howManyTasksWereCheckedInThisIteration << endl;

	p << prefix << hl;

	/*
	p->ps->printHorizontalLine();

	p->p( "freeRamMemory()=" ); Serial.print( freeRamMemory() ); Serial.println( " B" );
	p->p( "millis()=" ); Serial.println( millis() );

	p->p( "statisticsCreationIntervalInMs=" ); Serial.println( statisticsCreationIntervalInMs );

	p->p( "timeSum=" ); Serial.println( timeSum );
	p->p( "mainLoopExecutionsCount=" ); Serial.println( mainLoopExecutionsCount );

	p->p( "timeSum/mainLoopExecutionsCount=" );
	float f1 = timeSum;
	float f2 = mainLoopExecutionsCount;
	float f = f1/f2;
	Serial.println( f );

	p->p( "checkedTasksSum=" ); Serial.println( checkedTasksSum );
	p->p( "executedTasksSum=" ); Serial.println( executedTasksSum );
	p->p( "notExecutedTasksSum=" ); Serial.println( notExecutedTasksSum );
	p->p( "tasks queued in task manager=" ); Serial.println( howManyTasksWereCheckedInThisIteration );

	p->ps->printHorizontalLine();
	*/
}

void TaskManagerStatisticsBasic::resetStatistics()
{

	executionOfMainLoopStartTime = 0;
	timeSum = 0;

	checkedTasksSum = 0;
	executedTasksSum = 0;
	notExecutedTasksSum = 0;

	testStartTime = millis();
}

TaskManagerStatisticsBasic::~TaskManagerStatisticsBasic()
{
	//delete( p );
}

