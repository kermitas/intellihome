/*
 * SettableRestUpdateableService.cpp
 *
 *  Created on: 12-04-2012
 *      Author: root
 */
/*
// =================================================

#include "SettableRestUpdateableService.h"

// =================================================

SettableRestUpdateableService::SettableRestUpdateableService( Print& _p , const char* _name , const char* _value , ValueSetterHTMLGenerator* _valueSetterHTMLGenerator ) : RestUpdateableService( _name ) , p(_p)
{
	value = _value;
	valueSetterHTMLGenerator = _valueSetterHTMLGenerator;
}

// =================================================

void SettableRestUpdateableService::writeValueToStream( Stream* stream )
{
	stream->write( value );
}

// =================================================

void SettableRestUpdateableService::renderValueSetter( Stream* stream )
{
	//stream.write( "&nbsp;&nbsp;New value: " );
	//stream.write( "<input type='text' name='" );
	//stream.write( name );
	//stream.write( "' value='" );
	//getValue( stream );
	//stream.write( "'/>" );

	valueSetterHTMLGenerator->generateForText( stream , name );
}

// =================================================
*/

