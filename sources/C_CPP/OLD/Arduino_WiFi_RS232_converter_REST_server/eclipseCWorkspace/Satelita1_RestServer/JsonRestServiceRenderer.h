/*
 * JsonRestServiceRenderer.h
 *
 *  Created on: 07-05-2012
 *      Author: root
 */

#ifndef JSONRESTSERVICERENDERER_H_
#define JSONRESTSERVICERENDERER_H_

// =================================================

#include <Stream.h>

// =================================================

#include "RestServiceRenderer.h"

// =================================================

class JsonRestServiceRenderer : public RestServiceRenderer
{
	public:

		JsonRestServiceRenderer();

		void renderBeforeRestService( Stream* stream );

		void renderSpaceBetweenRestServicePatrs( Stream* stream );

		void renderGetValue( Stream* stream , RestService* restService );
		void renderValueSetter( Stream* stream , RestService* restService );

		void renderAfterRestService( Stream* stream );
};

// =================================================

#endif /* JSONRESTSERVICERENDERER_H_ */
