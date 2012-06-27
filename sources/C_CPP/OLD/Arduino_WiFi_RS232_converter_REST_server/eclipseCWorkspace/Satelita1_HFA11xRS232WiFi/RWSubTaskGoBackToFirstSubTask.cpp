/*
 * RWSubTaskGoBackToFirstSubTask.cpp
 *
 *  Created on: 22-05-2012
 *      Author: root
 */

// =================================================

#include "RWSubTaskGoBackToFirstSubTask.h"

// =================================================

//RWSubTaskGoBackToFirstSubTask::RWSubTaskGoBackToFirstSubTask()
//{
//}

// =================================================

char* RWSubTaskGoBackToFirstSubTask::getSubTaskName()
{
	return "GoBackToFirstSubTask";
}

// =================================================

void RWSubTaskGoBackToFirstSubTask::resetInternalState()
{

}

// =================================================

unsigned long RWSubTaskGoBackToFirstSubTask::getStateTimeout()
{
	return 0;
}

// =================================================

RWSubTask* RWSubTaskGoBackToFirstSubTask::getStateAfterTimeout()
{
	return NULL;
}

// =================================================

RWSubTask* RWSubTaskGoBackToFirstSubTask::executeSubTask()
{
	return NULL;
}

// =================================================


