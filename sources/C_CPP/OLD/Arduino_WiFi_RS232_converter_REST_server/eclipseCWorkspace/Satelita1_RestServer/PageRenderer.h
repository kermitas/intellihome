/*
 * PageRenderer.h
 *
 *  Created on: 12-04-2012
 *      Author: root
 */

#ifndef PAGERENDERER_H_
#define PAGERENDERER_H_

// =================================================

#include <Stream.h>

// =================================================

class PageRenderer
{
	public:

		virtual void renderHttpHeader( Stream* stream ) = 0;

		virtual void renderPageTop( Stream* stream  ) = 0;

		virtual void renderBeforeRestService( Stream* stream ) = 0;
		virtual void renderAfterRestService( Stream* stream ) = 0;

		virtual void renderPageBottom( Stream* stream ) = 0;

};

// =================================================

#endif /* PAGERENDERER_H_ */
