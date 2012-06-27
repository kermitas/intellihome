/*
 * BasicHTMLHeaderRenderer.h
 *
 *  Created on: 11-04-2012
 *      Author: root
 */
/*
#ifndef BASICHTMLPAGERENDERER_H_
#define BASICHTMLPAGERENDERER_H_

// =================================================

#include <Arduino.h>
#include <Stream.h>

// =================================================

#include "HTMLPageRenderer.h"
#include "RestReadOnlyService.h"

// =================================================

class BasicHTMLPageRenderer : public HTMLPageRenderer
{
	public:

		void renderHtmlHeader( Stream& stream , bool renderForJSON );

		void renderPageTop( Stream& stream , bool renderForJSON );

		void renderSpaceBetweenRestServiceParts( Stream& stream );
		void renderSpaceBetweenRestServices( Stream& stream );

		void renderPageBottom( Stream& stream , bool renderForJSON );

	protected:

		unsigned long pageGenerationStartTime;

};

// =================================================

#endif *//* BASICHTMLPAGERENDERER_H_ */
