/*
 * JSONPageRenderer.h
 *
 *  Created on: 07-05-2012
 *      Author: root
 */

/*
#ifndef JSONPAGERENDERER_H_
#define JSONPAGERENDERER_H_

// =================================================

#include <Stream.h>

// =================================================

class JSONPageRenderer
{
	public:

		virtual void renderHttpHeader( Stream* stream ) = 0;

		virtual void renderPageTop( Stream* stream ) = 0;

		virtual void renderBeforeRestService( Stream* stream ) = 0;
		virtual void renderAfterRestService( Stream* stream ) = 0;

		virtual void renderPageBottom( Stream* stream ) = 0;

};

// =================================================

#endif*/ /* JSONPAGERENDERER_H_ */
