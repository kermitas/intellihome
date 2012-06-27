/*
 * TableHTMLPageRenderer.cpp
 *
 *  Created on: 23-04-2012
 *      Author: root
 */

// =================================================

#include "TableHTMLPageRenderer.h"

// =================================================

TableHTMLPageRenderer::TableHTMLPageRenderer( ServiceDescription** _serviceDescrptions , unsigned char _serviceDescrptionsCount , TimeMeasurement* _pageRendererTimeMeasurement )
{
	serviceDescrptions = _serviceDescrptions;
	serviceDescrptionsCount = _serviceDescrptionsCount;
	pageRendererTimeMeasurement = _pageRendererTimeMeasurement;

	generateLighterRowBackground = true;
}

// =================================================

void TableHTMLPageRenderer::renderHttpHeader( Stream* stream )
{
	if( pageRendererTimeMeasurement != NULL ) pageRendererTimeMeasurement->saveTime();

	//stream->write( "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n" );
	//stream->write( "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: keep-alive\r\nKeep-Alive: timeout=10, max=1\r\n\r\n" );

	//stream->write( "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nTransfer-Encoding: chunked\r\n\r\n" );

	stream->write( "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nTransfer-Encoding: chunked\r\nConnection: close\r\n\r\n" );
	//stream->write( "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nTransfer-Encoding: chunked\r\nConnection: keep-alive\r\n\r\n" );
}

// =================================================

void TableHTMLPageRenderer::renderPageTop( Stream* stream )
{
	stream->write( "<html><body style='background-color:#dbdbdb;'>" );
	stream->write( "<table width='100%' style='border-width:1px;background-color:#efeee5;border-style:solid;border-color:#000000;'><tr style='background-color:#dbeeff;text-align:center;font-weight:bold;'><td>ID</td><td>NAME</td><td>VALUE</td><td>SET NEW VALUE</td></tr>" );
}

// =================================================

void TableHTMLPageRenderer::renderBeforeRestService( Stream* stream )
{
	if( generateLighterRowBackground )
		stream->write( "<tr style='background-color:#f7f6ec;'>" );
	else
		stream->write( "<tr>" );

	generateLighterRowBackground = !generateLighterRowBackground;
}

// =================================================

void TableHTMLPageRenderer::renderAfterRestService( Stream* stream )
{
	stream->write( "</tr>" );
}

// =================================================

void TableHTMLPageRenderer::renderPageBottom( Stream* stream )
{
	stream->write( "</table>" );

	// ---------

	stream->write( "<hr />" );

	generateHelp( stream );

	stream->write( "<hr />" );

	stream->write( "<table width='100%'><tr><td style='text-align:right;'><font size='-1'>Artur Stanek 2012</font></td></tr></table>" );

	stream->write( "</body></html>" );

	//stream->write( "\r\n\r\n" );
	//stream->write( "\r\n\r\n" );
	//stream->write( "\r\n\r\n" );

	//stream->write( "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\nContent-length: 0\r\n\r\n" );
}

// =================================================

void TableHTMLPageRenderer::generateHelp( Stream* stream )
{
	// ---------

	stream->write( "<font size='+1' style='font-family:Arial,Helvetica,Verdana,sans-serif;'><b>Useful links:</b></font><br />" );

	stream->write( "Show data normally:&nbsp;" );

	stream->write( "<a href='/'>all</a>,&nbsp;" );

	stream->write( "<a href='" );
	generateReadOnlyOrUpdateableServicesNamesForLink( stream , true );
	stream->write( "'>read only</a>,&nbsp;" );

	stream->write( "<a href='" );
	generateReadOnlyOrUpdateableServicesNamesForLink( stream , false );
	stream->write( "'>updateable</a>, or in JSON:&nbsp;" );

	// ---------

	stream->write( "<a href='/j'>all</a>,&nbsp;" );

	stream->write( "<a href='/j" );
	generateReadOnlyOrUpdateableServicesNamesForLink( stream , true );
	stream->write( "'>read only</a>,&nbsp;" );

	stream->write( "<a href='/j" );
	generateReadOnlyOrUpdateableServicesNamesForLink( stream , false );
	stream->write( "'>updateable</a>." );

	// ---------

	stream->write( "<br />Show metadescription:&nbsp;" );

	stream->write( "<a href='/m'>all</a>,&nbsp;" );

	stream->write( "<a href='/m" );
	generateReadOnlyOrUpdateableServicesNamesForLink( stream , true );
	stream->write( "'>read only</a>,&nbsp;" );

	stream->write( "<a href='/m" );
	generateReadOnlyOrUpdateableServicesNamesForLink( stream , false );
	stream->write( "'>updateable</a>." );

	// ---------

	//stream->write( "<hr width='40%'/>" );
	stream->write( "<hr />" );

	// ---------

	stream->write( "<font size='+1' style='font-family:Arial,Helvetica,Verdana,sans-serif;'><b>Help:</b></font><br />" );

	stream->write( "&nbsp;-&nbsp;ask about services using '*', for example asking for all services starting with 'soft' and 'tim' will be <font color='#000083'>http://192.168.1.10/<b>soft*</b>/<b>tim*</b></font>" );

	stream->write( "<br />" );

	stream->write( "&nbsp;-&nbsp;ask about services in JSON using '/j' prefix, for example <font color='#000083'>http://192.168.1.10/<b>j</b>/soft*/tim*</font>" );

	stream->write( "<br />" );

	stream->write( "&nbsp;-&nbsp;ask about services metadescription (it is always in JSON) '/m' prefix, for example <font color='#000083'>http://192.168.1.10/<b>m</b>/soft*/tim*</font>" );

	// ---------
}

// =================================================

void TableHTMLPageRenderer::generateReadOnlyOrUpdateableServicesNamesForLink( Stream* stream , bool generateReadOnly )
{
	for( unsigned int i = 0 ; i < serviceDescrptionsCount - 2 ; i++ )
	{
		if( generateReadOnly && serviceDescrptions[i]->restService->type == 0 )
		{
			stream->write( "/" );
			stream->write( serviceDescrptions[i]->restService->name );
		}
		else
		if( !generateReadOnly && serviceDescrptions[i]->restService->type > 0 )
		{
			stream->write( "/" );
			stream->write( serviceDescrptions[i]->restService->name );
		}
	}
}

// =================================================
