/*
 * DebugPrinter.cpp
 *
 *  Created on: 15-05-2012
 *      Author: root
 */

// =================================================

#include "DebugPrinter.h"

// =================================================

const PROGMEM prog_char DebugPrinter::classNameAndFunctionNameSpacer[] = "::";
const PROGMEM prog_char DebugPrinter::functionNamePostfix[] = "():";
const PROGMEM prog_char DebugPrinter::newLine[] = "\r\n";

const PROGMEM prog_char DebugPrinter::debugLevelPrefixForALL[] = "A:";
const PROGMEM prog_char DebugPrinter::debugLevelPrefixForINFO[] = "I:";
const PROGMEM prog_char DebugPrinter::debugLevelPrefixForWARNING[] = "W:";
const PROGMEM prog_char DebugPrinter::debugLevelPrefixForERROR[] = "E:";

// =================================================

DebugPrinter::DebugPrinter( const prog_char* _className ) //: level( CURRENT_DEBUG_LEVEL )
{
	className = _className;
	level = CURRENT_DEBUG_LEVEL;
}

// =================================================

DebugPrinter::DebugPrinter( const prog_char* _className , const byte _level ) //: level( _level )
{
	className = _className;
	level = _level;
}

// =================================================

void DebugPrinter::setLevel( byte _level )
{
	level = _level;
}

// =================================================

void DebugPrinter::preMacro( const prog_char* debugLevelPrefix , const prog_char* functionName )
{
	printf_P( debugLevelPrefix );

	printf_P( className );

	printf_P( classNameAndFunctionNameSpacer );

	printf_P( functionName );

	printf_P( functionNamePostfix );
}

// =================================================