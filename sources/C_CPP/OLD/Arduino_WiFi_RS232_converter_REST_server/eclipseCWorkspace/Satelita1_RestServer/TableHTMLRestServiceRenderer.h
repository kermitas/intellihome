/*
 * TableHTMLRestServiceRenderer.h
 *
 *  Created on: 23-04-2012
 *      Author: root
 */

#ifndef TABLEHTMLRESTSERVICERENDERER_H_
#define TABLEHTMLRESTSERVICERENDERER_H_

// =================================================

#include <Stream.h>

// =================================================

#include "RestServiceRenderer.h"

// =================================================

class TableHTMLRestServiceRenderer : public RestServiceRenderer
{
	public:

		TableHTMLRestServiceRenderer( bool _useGETHttpMethodInForms );

		void renderBeforeRestService( Stream* stream );

		void renderSpaceBetweenRestServicePatrs( Stream* stream );

		void renderGetValue( Stream* stream , RestService* restService );//, bool renderForJSON );
		void renderValueSetter( Stream* stream , RestService* restService );
		//void renderMetadescription( Stream* stream , RestService* restService );

		void renderAfterRestService( Stream* stream );

	protected:

		bool useGETHttpMethodInForms;

		//void renderMetadescriptionTypeDescription( Stream* stream , unsigned char type );
};

// =================================================

#endif /* TABLEHTMLRESTSERVICERENDERER_H_ */
