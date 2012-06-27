/*
 * TaskManagerTaskMemoryInfo.cpp
 *
 *  Created on: 06-01-2012
 *      Author: root
 */

#include "TaskManagerMemoryConfigurator.h"

TaskManagerMemoryConfigurator::TaskManagerMemoryConfigurator( bool _canTaskManagerFreeScheduler , bool _canTaskManagerFreeRunnable , bool _canTaskManagerFreeMemoryConfigurator )
{
	this->_canTaskManagerFreeScheduler = _canTaskManagerFreeScheduler;
	this->_canTaskManagerFreeRunnable = _canTaskManagerFreeRunnable;
	this->_canTaskManagerFreeMemoryConfigurator = _canTaskManagerFreeMemoryConfigurator;
}

bool TaskManagerMemoryConfigurator::canTaskManagerFreeScheduler()
{
	return _canTaskManagerFreeScheduler;
}

bool TaskManagerMemoryConfigurator::canTaskManagerFreeRunnable()
{
	return _canTaskManagerFreeRunnable;
}

bool TaskManagerMemoryConfigurator::canTaskManagerFreeMemoryConfigurator()
{
	return _canTaskManagerFreeMemoryConfigurator;
}

TaskManagerMemoryConfigurator::~TaskManagerMemoryConfigurator() {}


