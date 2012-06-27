/*
 * JsonRestServiceRenderer.cpp
 *
 *  Created on: 07-05-2012
 *      Author: root
 */

// =================================================

#include "JsonRestServiceRenderer.h"

// =================================================

JsonRestServiceRenderer::JsonRestServiceRenderer()
{

}

// =================================================

void JsonRestServiceRenderer::renderBeforeRestService( Stream* stream )
{
	stream->write( "{\r\n" );
}

// =================================================

void JsonRestServiceRenderer::renderSpaceBetweenRestServicePatrs( Stream* stream )
{

}

// =================================================

void JsonRestServiceRenderer::renderGetValue( Stream* stream , RestService* restService)
{
	stream->write( "\"" );
	stream->write( restService->name );
	stream->write( "\":\"" );
	restService->writeValueToStream( stream );
	stream->write( "\"" );
}

// =================================================

void JsonRestServiceRenderer::renderValueSetter( Stream* stream , RestService* restService )
{

}

// =================================================

void JsonRestServiceRenderer::renderAfterRestService( Stream* stream )
{
	stream->write( "\r\n}\r\n" );
}

// =================================================



