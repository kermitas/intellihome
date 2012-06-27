/*
 * Renderer.h
 *
 *  Created on: 11-04-2012
 *      Author: root
 */

#ifndef RESTSERVICERENDERER_H_
#define RESTSERVICERENDERER_H_

// =================================================

#include <Stream.h>

// =================================================

#include "RestService.h"

// =================================================

class RestServiceRenderer
{
	public:

		virtual void renderBeforeRestService( Stream* stream ) = 0;

		virtual void renderSpaceBetweenRestServicePatrs( Stream* stream ) = 0;

		virtual void renderGetValue( Stream* stream , RestService* restService ) = 0;
		virtual void renderValueSetter( Stream* stream , RestService* restService ) = 0;

		//virtual void renderMetadescription( Stream* stream ) = 0;

		virtual void renderAfterRestService( Stream* stream ) = 0;
};

// =================================================

#endif /* RESTSERVICERENDERER_H_ */
