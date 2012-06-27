/*
 * JsonPageRenderer.h
 *
 *  Created on: 07-05-2012
 *      Author: root
 */

#ifndef JSONPAGERENDERER_H_
#define JSONPAGERENDERER_H_

// =================================================

#include <Arduino.h>
#include <Stream.h>

// =================================================

#include "PageRenderer.h"
//#include "RestService.h"
#include "RestServerCommon.h"
#include "TimeMeasurement.h"

// =================================================

class JsonPageRenderer : public PageRenderer
{
	public:

		JsonPageRenderer( TimeMeasurement* _pageRendererTimeMeasurement );

		void renderHttpHeader( Stream* stream );

		void renderPageTop( Stream* stream );

		void renderBeforeRestService( Stream* stream );
		void renderAfterRestService( Stream* stream );

		void renderPageBottom( Stream* stream );

	protected:

		TimeMeasurement* pageRendererTimeMeasurement;
};

// =================================================

#endif /* JSONPAGERENDERER_H_ */
