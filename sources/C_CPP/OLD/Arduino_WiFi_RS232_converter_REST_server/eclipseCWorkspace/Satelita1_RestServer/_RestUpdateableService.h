/*
 * RestUpdateableService.h
 *
 *  Created on: 05-04-2012
 *      Author: root
 */
/*
#ifndef RESTUPDATEABLESERVICE_H_
#define RESTUPDATEABLESERVICE_H_

// =================================================

#include "RestReadOnlyService.h"

// =================================================

class RestUpdateableService : public RestReadOnlyService
{
	public:

		RestUpdateableService( const char* _name );

		bool isUpdateable();
		virtual void renderValueSetter( Stream* stream ) = 0;
};

// =================================================

#endif */ /* RESTUPDATEABLESERVICE_H_ */
