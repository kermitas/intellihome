/*
 * TableHTMLPageRenderer.h
 *
 *  Created on: 23-04-2012
 *      Author: root
 */

#ifndef TABLEHTMLPAGERENDERER_H_
#define TABLEHTMLPAGERENDERER_H_

// =================================================

#include <Arduino.h>
#include <Stream.h>

// =================================================

#include "PageRenderer.h"
//#include "RestService.h"
#include "RestServerCommon.h"
#include "TimeMeasurement.h"

// =================================================

class TableHTMLPageRenderer : public PageRenderer
{
	public:

		TableHTMLPageRenderer( ServiceDescription** _serviceDescrptions , unsigned char _serviceDescrptionsCount , TimeMeasurement* _pageRendererTimeMeasurement );

		void renderHttpHeader( Stream* stream );

		void renderPageTop( Stream* stream );

		void renderBeforeRestService( Stream* stream );
		void renderAfterRestService( Stream* stream );

		void renderPageBottom( Stream* stream );

	protected:

		ServiceDescription** serviceDescrptions;
		unsigned char serviceDescrptionsCount;
		TimeMeasurement* pageRendererTimeMeasurement;

		void generateHelp( Stream* stream );
		void generateReadOnlyOrUpdateableServicesNamesForLink( Stream* stream , bool generateReadOnly );
		//void generateTimeAsDaysHoursMinutesSeconds( Stream* stream );

		bool generateLighterRowBackground;

};

// =================================================

#endif /* TABLEHTMLPAGERENDERER_H_ */
