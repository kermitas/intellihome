/*
 * BasicHTMLRenderer.cpp
 *
 *  Created on: 11-04-2012
 *      Author: root
 */

/*
// =================================================

#include "BasicHTMLRestServiceRenderer.h"

// =================================================

BasicHTMLRestServiceRenderer::BasicHTMLRestServiceRenderer( bool _useGETHttpMethodInForms )
{
	useGETHttpMethodInForms = _useGETHttpMethodInForms;
}

// =================================================

void BasicHTMLRestServiceRenderer::renderGetValue( Stream& stream , RestReadOnlyService* restReadOnlyService , bool renderForJSON )
{
	if( renderForJSON )
	{
		stream.write( "{\r\n\"" );
		stream.write( restReadOnlyService->name );
		stream.write( "\":\"" );
		restReadOnlyService->getValue( stream );
		stream.write( "\"\r\n}" );
	}
	else
	{
		stream.write( restReadOnlyService->name );
		stream.write( " : " );
		restReadOnlyService->getValue( stream );
	}
}

// =================================================

void BasicHTMLRestServiceRenderer::renderValueSetter( Stream& stream , RestUpdateableService* restUpdateableService )
{
	//if( renderAsStandAloneForm )
	{
		stream.write( "&nbsp;&nbsp;<form style='display:inline;' action='" );
		stream.write( restUpdateableService->name );
		stream.write( "' method='" );
		stream.write( useGETHttpMethodInForms ? "GET" : "POST" );
		stream.write( "'>" );
	}

	restUpdateableService->renderValueSetter( stream );

	//if( renderAsStandAloneForm )
	{
		stream.write( "&nbsp;&nbsp;<input type='submit' value='Update!' /></form>" );
	}
}

// =================================================

void BasicHTMLRestServiceRenderer::renderMetadescription( Stream& stream , RestReadOnlyService* restReadOnlyService )
{
	stream.write( "{\r\n\"name\":\"" );
	stream.write( restReadOnlyService->name );
	stream.write( "\",\r\n\"isUpdateable\":\"" );
	stream.write( restReadOnlyService->isUpdateable() ? "true" : "false" );
	stream.write( "\"\r\n}" );
}

// =================================================
*/


