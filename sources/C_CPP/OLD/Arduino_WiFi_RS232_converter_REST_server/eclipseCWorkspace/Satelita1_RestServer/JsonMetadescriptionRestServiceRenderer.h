/*
 * JsonMetadescriptionRestServiceRenderer.h
 *
 *  Created on: 07-05-2012
 *      Author: root
 */

#ifndef JSONMETADESCRIPTIONRESTSERVICERENDERER_H_
#define JSONMETADESCRIPTIONRESTSERVICERENDERER_H_

// =================================================

#include <Stream.h>

// =================================================

#include "RestServiceRenderer.h"

// =================================================

class JsonMetadescriptionRestServiceRenderer : public RestServiceRenderer
{
	public:

		JsonMetadescriptionRestServiceRenderer();

		void renderBeforeRestService( Stream* stream );

		void renderSpaceBetweenRestServicePatrs( Stream* stream );

		void renderGetValue( Stream* stream , RestService* restService );
		void renderValueSetter( Stream* stream , RestService* restService );

		void renderAfterRestService( Stream* stream );

	protected:

		void renderMetadescriptionTypeDescription( Stream* stream , unsigned char type );
};

// =================================================

#endif /* JSONMETADESCRIPTIONRESTSERVICERENDERER_H_ */
