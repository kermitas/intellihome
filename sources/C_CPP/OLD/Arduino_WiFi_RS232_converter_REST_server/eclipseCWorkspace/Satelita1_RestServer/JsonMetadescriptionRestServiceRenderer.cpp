/*
 * JsonMetadescriptionRestServiceRenderer.cpp
 *
 *  Created on: 07-05-2012
 *      Author: root
 */

// =================================================

#include "JsonMetadescriptionRestServiceRenderer.h"

// =================================================

JsonMetadescriptionRestServiceRenderer::JsonMetadescriptionRestServiceRenderer()
{

}

// =================================================

void JsonMetadescriptionRestServiceRenderer::renderBeforeRestService( Stream* stream )
{
	stream->write( "{\r\n" );
}

// =================================================

void JsonMetadescriptionRestServiceRenderer::renderSpaceBetweenRestServicePatrs( Stream* stream )
{

}

// =================================================

void JsonMetadescriptionRestServiceRenderer::renderGetValue( Stream* stream , RestService* restService)
{
	stream->write( "\"id\":\"" );
	stream->print( restService->id );
	stream->write( "\"," );

	stream->write( "\r\n\"name\":\"" );
	stream->write( restService->name );
	stream->write( "\"," );

	stream->write( "\r\n\"type\":\"" );
	renderMetadescriptionTypeDescription( stream , restService->type );
	stream->write( "\"" );

	if( restService->type == REST_SERVICE_TYPE_UPDATEABLE_INT )
	{
		stream->write( "\r\n\"minValue\":\"" );
		stream->print( restService->getIntMinValue() );
		stream->write( "\"," );

		stream->write( "\r\n\"maxValue\":\"" );
		stream->print( restService->getIntMaxValue() );
	}
}

// =================================================

void JsonMetadescriptionRestServiceRenderer::renderValueSetter( Stream* stream , RestService* restService )
{

}

// =================================================

void JsonMetadescriptionRestServiceRenderer::renderAfterRestService( Stream* stream )
{
	stream->write( "\r\n}\r\n" );
}

// =================================================

void JsonMetadescriptionRestServiceRenderer::renderMetadescriptionTypeDescription( Stream* stream , unsigned char type )
{
	if( type == REST_SERVICE_TYPE_READ_ONLY )
	{
		stream->write( "read_only" );
	}
	else
	if( type == REST_SERVICE_TYPE_UPDATEABLE_BY_MYSELF )
	{
		stream->write( "updateable" );
	}
	else
	if( type == REST_SERVICE_TYPE_UPDATEABLE_TEXT )
	{
		stream->write( "updateable-text" );
	}
	else
	if( type == REST_SERVICE_TYPE_UPDATEABLE_BOOLEAN )
	{
		stream->write( "updateable-boolean" );
	}
	else
	if( type == REST_SERVICE_TYPE_UPDATEABLE_BOOLEAN_ONOFF )
	{
		stream->write( "updateable-boolean-on_off" );
	}
	else
	if( type == REST_SERVICE_TYPE_UPDATEABLE_BOOLEAN_ONE_TIME_EXECUTION )
	{
		stream->write( "updateable-boolean-one_time_execution" );
	}
	else
	if( type == REST_SERVICE_TYPE_UPDATEABLE_INT )
	{
		stream->write( "updateable-int" );
	}
	else
	{
		stream->write( "unknown" );
	}
}

// =================================================
