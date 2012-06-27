/*
 * BasicHTMLRenderer.h
 *
 *  Created on: 11-04-2012
 *      Author: root
 */
/*
#ifndef BASICHTMLRESTSERVICERENDERER_H_
#define BASICHTMLRESTSERVICERENDERER_H_

// =================================================

#include <Stream.h>

// =================================================

#include "HTMLRestServiceRenderer.h"

// =================================================

class BasicHTMLRestServiceRenderer : public HTMLRestServiceRenderer
{
	public:

		BasicHTMLRestServiceRenderer( bool _useGETHttpMethodInForms );

		void renderGetValue( Stream& stream , RestReadOnlyService* restReadOnlyService , bool renderForJSON );
		void renderValueSetter( Stream& stream , RestUpdateableService* restUpdateableService );
		void renderMetadescription( Stream& stream , RestReadOnlyService* restReadOnlyService );

	protected:

		bool useGETHttpMethodInForms;
};

// =================================================

#endif *//* BASICHTMLRESTSERVICERENDERER_H_ */
