/*
 * JsonPageRenderer.cpp
 *
 *  Created on: 23-04-2012
 *      Author: root
 */

// =================================================

#include "JsonPageRenderer.h"

// =================================================

JsonPageRenderer::JsonPageRenderer( TimeMeasurement* _pageRendererTimeMeasurement )
{
	pageRendererTimeMeasurement = _pageRendererTimeMeasurement;
}

// =================================================

void JsonPageRenderer::renderHttpHeader( Stream* stream )
{
	if( pageRendererTimeMeasurement != NULL ) pageRendererTimeMeasurement->saveTime();

	//stream->write( "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nConnection: close\r\n\r\n" );
	//stream->write( "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\nContent-length: -1\r\n\r\n" );
	//stream->write( "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n" );

	stream->write( "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\nConnection: close\r\n\r\n" );
}

// =================================================

void JsonPageRenderer::renderPageTop( Stream* stream )
{
	stream->write( "[\r\n" );
}

// =================================================

void JsonPageRenderer::renderBeforeRestService( Stream* stream )
{
	//stream->write( "{\r\n" );
}

// =================================================

void JsonPageRenderer::renderAfterRestService( Stream* stream )
{
	//stream->write( "}" );
}

// =================================================

void JsonPageRenderer::renderPageBottom( Stream* stream )
{
	stream->write( "]" );

	//stream->write( "\r\n\r\n" );
	//stream->write( "\r\n\r\n" );
	//stream->write( "\r\n\r\n" );
}

// =================================================
