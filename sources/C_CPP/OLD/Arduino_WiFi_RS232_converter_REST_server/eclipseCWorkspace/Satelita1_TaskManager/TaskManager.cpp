/*
 * TaskManager.cpp
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

#include "TaskManager.h"

// =================================================

//const PROGMEM prog_char TaskManager::className[] = "TaskManager";

// =================================================

TaskManager::TaskManager( unsigned int _maxTasksCount , const TaskManagerRecord** _tasksArray ) : dp( PSTR( "TaskManager" ) )// , Print& _p ) //: p( _p )
{
	maxTasksCount = _maxTasksCount;
	tasksArray = _tasksArray;

	currentTasksCount = 0;
	executeFunction_executeRecompactTaskArray = 0;
}

// =================================================

bool TaskManager::add( TaskManagerRecord* taskManagerRecord )
{
	static const PROGMEM prog_char functionName[] = "add";
	//static const char prefix[] = "TaskManager:add():";

	if( taskManagerRecord == NULL || taskManagerRecord->runnable == NULL )
	{
		//warning( p << prefix << "cannot add task because taskManagerRecord or taskManagerRecord->runnable is NULL " << endl; )
		//warning( wpln( "cannot add task because taskManagerRecord or taskManagerRecord->runnable is NULL" ) )
		wln( "cannot add task because taskManagerRecord or taskManagerRecord->runnable is NULL" )

		return false;
	}
	else
	{
		if( currentTasksCount >= maxTasksCount )
		{
			//warning( p << prefix << "cannot add task, array is full, current tasks count " << currentTasksCount << ", taskManagerRecord* = " << (int)taskManagerRecord << endl; )
			//warning( wpln( "cannot add task, array is full, current tasks count  %u, taskManagerRecord* = %u" , currentTasksCount , taskManagerRecord ) )
			wln( "cannot add task, array is full, current tasks count  %u, taskManagerRecord* = %u" , currentTasksCount , taskManagerRecord )

			return false;
		}
		else
		{
			//info( p <<  prefix << "adding task under index " << currentTasksCount << ", taskManagerRecord* = " << (int)taskManagerRecord << endl; )
			//info( wpln( "adding task under index %u, taskManagerRecord* = %u" , currentTasksCount , taskManagerRecord ) )
			iln( "adding task under index %u, taskManagerRecord* = %u" , currentTasksCount , taskManagerRecord )

			tasksArray[currentTasksCount] = taskManagerRecord;

			currentTasksCount++;

			return true;
		}
	}
}

// =================================================

bool TaskManager::removeByPointer( TaskManagerRecord* ptr )
{
	static const PROGMEM prog_char functionName[] = "removeByPointer";
	//static const char prefix[] = "TaskManager:removeByPointer():";

	unsigned int index = getIndex( ptr );

	if( index < maxTasksCount )
	{
		//info( p << prefix << "removing ptr*=" << (int)ptr << ", in tasksArray index=" << index << endl; )
		//info( wpln( "removing ptr* = %u, in tasksArray index = %u" , ptr , index ) )
		iln( "removing ptr* = %u, in tasksArray index = %u" , ptr , index )

		removeByIndex( index );
		return true;
	}
	else
	{
		//warning( p << prefix << "could not find ptr*=" << (int)ptr << " in tasksArray" << endl; )
		//warning( wpln( "could not find ptr* = %u in tasksArray" , ptr ) )
		wln( "could not find ptr* = %u in tasksArray" , ptr )

		return false;
	}
}

// =================================================

unsigned int TaskManager::getIndex( TaskManagerRecord* ptr )
{
	if( ptr != NULL ) for( unsigned int i = 0 ; i < maxTasksCount ; i++ ) if( tasksArray[i] == ptr ) return i;
	return maxTasksCount; // w przypadku nie znalezienia zwraca jako indeks maxTasksCount, czyli piersza komorke poza zakresem tablicy!
}

// =================================================

const TaskManagerRecord* TaskManager::removeByIndex( unsigned int index )
{
	static const PROGMEM prog_char functionName[] = "removeByIndex";
	//static const char prefix[] = "TaskManager:removeByIndex():";

	if( index < maxTasksCount )
	{
		const TaskManagerRecord* result = tasksArray[ index ];

		//info( p << prefix << "removing index=" << index << ", tasksArray[" << index << "]=" << (int)result << endl; )
		//info( wpln( "removing index = %u, tasksArray[%u] = %u" , index , index , result ) )
		iln( "removing index = %u, tasksArray[%u] = %u" , index , index , result )

		if( result != NULL )
		{
			tasksArray[ index ] = NULL;
			recompactTaskArray();
		}

		return result;
	}
	else
	{
		//warning( p << prefix << "invalid index=" << index << ", maxTasksCount=" << maxTasksCount << endl; )
		//warning( wpln( "invalid index = %u, maxTasksCount = " , index , maxTasksCount ) )
		wln( "invalid index = %u, maxTasksCount = " , index , maxTasksCount )

		return NULL;
	}
}

// =================================================

//const char TaskManager::executeFunctionPrefix[] = "TaskManager:execute():";

void TaskManager::execute()
{
	static const PROGMEM prog_char functionName[] = "execute";

	for( executeFunction_forLoopCounter = 0 ; executeFunction_forLoopCounter < currentTasksCount ; executeFunction_forLoopCounter++ )
	{
		const TaskManagerRecord* taskManagerRecord = tasksArray[ executeFunction_forLoopCounter ];

		if( taskManagerRecord != NULL )
		{
			//all( p << executeFunctionPrefix << "executing task under index " << executeFunction_forLoopCounter << ", taskManagerRecord* = " << (int)taskManagerRecord << ", currentTasksCount = " << currentTasksCount << endl; )
			//all( wpln( "executing task under index %u, taskManagerRecord* = %u, currentTasksCount = %u" , executeFunction_forLoopCounter , taskManagerRecord , currentTasksCount ) )
			aln( "executing task under index %u, taskManagerRecord* = %u, currentTasksCount = %u" , executeFunction_forLoopCounter , taskManagerRecord , currentTasksCount )

			if( taskManagerRecord->scheduler == NULL || taskManagerRecord->scheduler->canExecute() ) taskManagerRecord->runnable->run();

			if( taskManagerRecord->scheduler != NULL && taskManagerRecord->scheduler->canRemoveFromTaskManager() )
			{
				//p << "### executeFunction_forLoopCounter=" << executeFunction_forLoopCounter << ", currentTasksCount=" << currentTasksCount << ", ptr*=" << (int)taskManagerRecord << endl;

				//info( p << executeFunctionPrefix << "task under index " << executeFunction_forLoopCounter << " wanted to be removed from TaskManager (ptr*=" << (int)taskManagerRecord << "), will be removed" << endl; )
				//info( wpln( "task under index %u wanted to be removed from TaskManager (ptr*=%u), will be removed" , executeFunction_forLoopCounter , taskManagerRecord ) )
				iln( "task under index %u wanted to be removed from TaskManager (ptr*=%u), will be removed" , executeFunction_forLoopCounter , taskManagerRecord )

				tasksArray[ executeFunction_forLoopCounter ] = NULL;
				//executeFunction_executeRecompactTaskArray = true;

				//all( p << "### executeFunction_forLoopCounter=" << executeFunction_forLoopCounter << ", currentTasksCount=" << currentTasksCount << endl; )


				if( executeFunction_forLoopCounter == currentTasksCount-1 )
				{
					currentTasksCount--;
					//all( p << executeFunctionPrefix << "task under index " << executeFunction_forLoopCounter << " was removed, currentTasksCount was decreased to " << currentTasksCount << endl; )
					//all( wpln( "task under index %u was removed, currentTasksCount was decreased to %u" , executeFunction_forLoopCounter , currentTasksCount ) )
					aln( "task under index %u was removed, currentTasksCount was decreased to %u" , executeFunction_forLoopCounter , currentTasksCount )
				}
				else
				{
					executeFunction_executeRecompactTaskArray = true;
				}
			}
		}
		else
		{
			//warning( p << executeFunctionPrefix << "cannot execute task with index " << executeFunction_forLoopCounter << " in tasksArray, task is null" << endl; )
			//warning( wpln( "cannot execute task with index %d in tasksArray, task is null" , executeFunction_forLoopCounter ) )
			wln( "cannot execute task with index %d in tasksArray, task is null" , executeFunction_forLoopCounter )

			executeFunction_executeRecompactTaskArray = true;
		}
	}

	if( executeFunction_executeRecompactTaskArray )
	{
		executeFunction_executeRecompactTaskArray = false;
		recompactTaskArray();
	}
}

// =================================================

void TaskManager::printTasksArray()
{
	static const PROGMEM prog_char functionName[] = "printTasksArray";

	//info( p << "TaskManager:printTasksArray():"; )
	/*
	info(
		wp( "" )

		for( unsigned int i = 0 ; i < maxTasksCount ; i++ )
		{
			wp( "[%u]=%u" , i , tasksArray[i] )
		}

		wpln( "" )
	)*/

	//info( wp( "" ) )
	//info( wp( "" ) )
	i( "" )

	for( unsigned int i = 0 ; i < maxTasksCount ; i++ )
	{
		//info( p << " [" << i << "]=" << (int)tasksArray[i]; )
		//info( wp( "[%u]=%u" , i , tasksArray[i] ) )
		iln( "[%u]=%u" , i , tasksArray[i] )
	}

	//info( p << endl; )
	//info( wpln( "" ) )
	iln( "" )

	/*
	info( wp( "" ) )

	for( unsigned int i = 0 ; i < maxTasksCount ; i++ )
	{
		info( p << " [" << i << "]=" << (int)tasksArray[i]; )
	}

	info( p << endl; )*/
}

// =================================================

void TaskManager::recompactTaskArray()
{
	static const PROGMEM prog_char functionName[] = "recompactTaskArray";
	//static const char prefix[] = "TaskManager:recompactTaskArray():";

	//info( p << prefix << "recompacting taskArray" << endl; )
	//info( wpln( "recompacting taskArray" ) )
	iln( "recompacting taskArray" )

	//info( p << prefix << "old taskArray:" << endl; )
	//info( wpln( "old taskArray:" ) )
	iln( "old taskArray:" )

	printTasksArray();

	const TaskManagerRecord* newTasksArray[maxTasksCount];

	int ii = 0;
	for( unsigned int i = 0 ; i < maxTasksCount ; i++ )
	{
		if( tasksArray[ i ] != NULL )
		{
			newTasksArray[ ii ] = tasksArray[ i ];
			ii++;
		}
	}

	int prevCurrentTasksCount = currentTasksCount;
	currentTasksCount = ii;

	for( unsigned int i = 0 ; i < currentTasksCount ; i++ ) tasksArray[ i ] = newTasksArray[ i ];
	for( unsigned int i = currentTasksCount ; i < maxTasksCount ; i++ ) tasksArray[ i ] = NULL;

	//info( p << prefix << "new taskArray:" << endl; )
	//info( wpln( "new taskArray:" ) )
	iln( "new taskArray:" )

	printTasksArray();

	//info( p << prefix << "previous tasks count=" << prevCurrentTasksCount << ", new=" << currentTasksCount << endl; )
	//info( wpln( "previous tasks count=%u, new tasks cound=%u" , prevCurrentTasksCount , currentTasksCount ) )
	iln( "previous tasks count=%u, new tasks cound=%u" , prevCurrentTasksCount , currentTasksCount )
}

// =================================================

TaskManager::~TaskManager() {}

// =================================================
