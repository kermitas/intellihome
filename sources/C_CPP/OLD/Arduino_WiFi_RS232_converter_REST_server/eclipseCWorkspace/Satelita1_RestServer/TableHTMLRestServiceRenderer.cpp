/*
 * TableHTMLRestServiceRenderer.cpp
 *
 *  Created on: 23-04-2012
 *      Author: root
 */

// =================================================

#include "TableHTMLRestServiceRenderer.h"

// =================================================

TableHTMLRestServiceRenderer::TableHTMLRestServiceRenderer( bool _useGETHttpMethodInForms )
{
	useGETHttpMethodInForms = _useGETHttpMethodInForms;
}

// =================================================

void TableHTMLRestServiceRenderer::renderBeforeRestService( Stream* stream )
{

}

// =================================================

void TableHTMLRestServiceRenderer::renderSpaceBetweenRestServicePatrs( Stream* stream )
{

}

// =================================================

void TableHTMLRestServiceRenderer::renderGetValue( Stream* stream , RestService* restService )
{
	stream->write( "<td style='text-align:center;font-weight:bold;'>" );
	stream->print( restService->id );
	stream->write( "</td>" );

	stream->write( "<td>" );
	stream->write( restService->name );
	stream->write( "</td>" );

	stream->write( "<td>" );
	restService->writeValueToStream(stream);
	stream->write( "</td>" );
}

// =================================================

void TableHTMLRestServiceRenderer::renderValueSetter( Stream* stream , RestService* restService )
{
	stream->write( "<td>" );

	if( restService->type == REST_SERVICE_TYPE_READ_ONLY )
	{
		stream->write( "&nbsp;" );
	}
	else
	{
		if( restService->type == REST_SERVICE_TYPE_UPDATEABLE_BY_MYSELF )
		{
			restService->renderValueSetter( stream , useGETHttpMethodInForms );
		}
		else
		if( restService->type == REST_SERVICE_TYPE_UPDATEABLE_TEXT )
		{
			stream->write( "<form style='display:inline;' action='' method='" );
			stream->write( useGETHttpMethodInForms ? "GET" : "POST" );
			stream->write( "'>" );

			stream->write( "<input type='text' name='" );
			stream->write( restService->name );
			stream->write( "' />" );

			stream->write( "&nbsp;&nbsp;<input type='submit' value='Set' /></form>" );
		}
		else
		if( restService->type == REST_SERVICE_TYPE_UPDATEABLE_BOOLEAN )
		{
			bool booleanValue = restService->getBooleanValue();

			stream->write( "<form style='display:inline;' action='' method='" );
			stream->write( useGETHttpMethodInForms ? "GET" : "POST" );
			stream->write( "'>" );

			stream->write( "<input type='hidden' name='" );
			stream->write( restService->name );
			stream->write( "' value='" );
			stream->write( booleanValue ? "0" : "1" );
			stream->write( "' />" );

			stream->write( "<input type='submit' value='" );
			stream->write( booleanValue ? "FALSE" : "TRUE" );
			stream->write( "'" );
			stream->write( " />" );

			stream->write( "</form>" );
		}
		else
		if( restService->type == REST_SERVICE_TYPE_UPDATEABLE_BOOLEAN_ONOFF )
		{
			bool booleanValue = restService->getBooleanValue();

			stream->write( "<form style='display:inline;' action='' method='" );
			//stream->write( "<form style='display:inline;' method='" );
			stream->write( useGETHttpMethodInForms ? "GET" : "POST" );
			stream->write( "'>" );

			stream->write( "<input type='hidden' name='" );
			//stream->write( "<input type='text' name='" ); // todo spowrotem zrobic hidden
			stream->write( restService->name );
			stream->write( "' value='" );
			stream->write( booleanValue ? "0" : "1" );
			stream->write( "' />" );

			//stream->write( "&nbsp;&nbsp;<input type='submit' value='Set123' /></form>" );

			stream->write( "<input type='submit' value='" );
			stream->write( booleanValue ? "OFF" : "ON" );
			stream->write( "'" );
			stream->write( " />" );

			stream->write( "</form>" );
		}
		else
		if( restService->type == REST_SERVICE_TYPE_UPDATEABLE_INT )
		{
			stream->write( "<form style='display:inline;' action='' method='" );
			stream->write( useGETHttpMethodInForms ? "GET" : "POST" );
			stream->write( "'>" );

			stream->write( "<input type='text' name='" );
			stream->write( restService->name );
			stream->write( "' />" );

			stream->write( "&nbsp;&nbsp;<input type='submit' value='Set' /></form>" );

			stream->write( "<br /><font size='-1'>(min: " );
			stream->print( restService->getIntMinValue() );
			stream->write( ", max: " );
			stream->print( restService->getIntMaxValue() );
			stream->write( ")</font>" );
		}
		else
		if( restService->type == REST_SERVICE_TYPE_UPDATEABLE_BOOLEAN_ONE_TIME_EXECUTION )
		{
			stream->write( "<form style='display:inline;' action='' method='" );
			stream->write( useGETHttpMethodInForms ? "GET" : "POST" );
			stream->write( "'>" );

			stream->write( "<input type='hidden' name='" );
			stream->write( restService->name );
			stream->write( "' value='0'/>" );

			stream->write( "<input type='submit' value='EXECUTE' /></form>" );
		}
		else
		{
			stream->write( "<b>Unsupported updateable rest service type " );
			stream->print( restService->type );
			stream->write( "!</b>" );
		}
	}

	stream->write( "</td>" );
}

// =================================================

void TableHTMLRestServiceRenderer::renderAfterRestService( Stream* stream )
{

}

// =================================================
/*
void TableHTMLRestServiceRenderer::renderMetadescription( Stream* stream , RestService* restService )
{
	stream->write( "{" );

	stream->write( "\r\n\"id\":\"" );
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
		stream->write( "\"," );
	}

	stream->write( "\r\n}" );

	stream->write( "\r\n" );
}

// =================================================

void TableHTMLRestServiceRenderer::renderMetadescriptionTypeDescription( Stream* stream , unsigned char type )
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
*/
// =================================================



