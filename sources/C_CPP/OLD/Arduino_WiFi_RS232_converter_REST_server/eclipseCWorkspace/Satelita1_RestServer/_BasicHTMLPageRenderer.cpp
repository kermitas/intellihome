/*
 * BasicHTMLHeaderRenderer.cpp
 *
 *  Created on: 11-04-2012
 *      Author: root
 */
/*
// =================================================

#include "BasicHTMLPageRenderer.h"

// =================================================

void BasicHTMLPageRenderer::renderHtmlHeader( Stream& stream , bool renderForJSON )
{
	if( renderForJSON )
	{
		stream.write( "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n" );
	}
	else
	{
		pageGenerationStartTime = millis();
		stream.write( "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" );
	}
}

// =================================================

void BasicHTMLPageRenderer::renderPageTop( Stream& stream , bool renderForJSON )
{
	if( renderForJSON )
	{
		stream.write( "[\r\n" );
	}
	else
	{
		stream.write( "<html><body>" );

		stream.write( "Current time: " );
		stream.print( millis()/1000 );
		stream.write( "s.<hr />" );
	}
}

// =================================================

void BasicHTMLPageRenderer::renderSpaceBetweenRestServiceParts( Stream& stream )
{

}

// =================================================

void BasicHTMLPageRenderer::renderSpaceBetweenRestServices( Stream& stream )
{
	stream.write( "<br />" );
}

// =================================================

void BasicHTMLPageRenderer::renderPageBottom( Stream& stream , bool renderForJSON )
{
	if( renderForJSON )
	{
		stream.write( "\r\n]" );
	}
	else
	{
		stream.write( "<hr />" );

		stream.write( "Page generated in " );
		stream.print( millis()-pageGenerationStartTime );
		stream.write( "ms." );

		stream.write( "</body></html>" );
		stream.write( "\r\n\r\n\r\n" );
	}

}
*/
// =================================================
