/*
 * DebugPrinter.h
 *
 *  Created on: 15-05-2012
 *      Author: root
 */

#ifndef DEBUGPRINTER_H_
#define DEBUGPRINTER_H_

// =================================================

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <stdarg.h>

// =================================================

#include "Configuration.c"

// =================================================

// w przyszlosci pozamieniac na nazwy typu DEBUG_LEVEL_*

#define DEBUG_LEVEL_ALL 10
#define DEBUG_LEVEL_INFO 20
#define DEBUG_LEVEL_WARNING 30
#define DEBUG_LEVEL_ERROR 40

// =================================================

#define a( str , varargs... )   { if( dp.level <= DEBUG_LEVEL_ALL ) { dp.preMacro( dp.debugLevelPrefixForALL , functionName ); printf_P( PSTR( str ) , ##varargs ); } }
#define aln( str , varargs... ) { if( dp.level <= DEBUG_LEVEL_ALL ) { dp.preMacro( dp.debugLevelPrefixForALL , functionName ); printf_P( PSTR( str ) , ##varargs ); printf_P( dp.newLine ); } }

#define i( str , varargs... )   { if( dp.level <= DEBUG_LEVEL_INFO ) { dp.preMacro( dp.debugLevelPrefixForINFO , functionName ); printf_P( PSTR( str ) , ##varargs ); } }
#define iln( str , varargs... ) { if( dp.level <= DEBUG_LEVEL_INFO ) { dp.preMacro( dp.debugLevelPrefixForINFO , functionName ); printf_P( PSTR( str ) , ##varargs ); printf_P( dp.newLine ); } }

#define w( str , varargs... )   { if( dp.level <= DEBUG_LEVEL_WARNING ) { dp.preMacro( dp.debugLevelPrefixForWARNING , functionName ); printf_P( PSTR( str ) , ##varargs ); } }
#define wln( str , varargs... ) { if( dp.level <= DEBUG_LEVEL_WARNING ) { dp.preMacro( dp.debugLevelPrefixForWARNING , functionName ); printf_P( PSTR( str ) , ##varargs ); printf_P( dp.newLine ); } }

#define e( str , varargs... )   { if( dp.level <= DEBUG_LEVEL_ERROR ) { dp.preMacro( dp.debugLevelPrefixForERROR , functionName ); printf_P( PSTR( str ) , ##varargs ); } }
#define eln( str , varargs... ) { if( dp.level <= DEBUG_LEVEL_ERROR ) { dp.preMacro( dp.debugLevelPrefixForERROR , functionName ); printf_P( PSTR( str ) , ##varargs ); printf_P( dp.newLine ); } }

// =================================================

class DebugPrinter
{
	public:

		static const PROGMEM prog_char newLine[];

		static const PROGMEM prog_char classNameAndFunctionNameSpacer[];
		static const PROGMEM prog_char functionNamePostfix[];

		static const PROGMEM prog_char debugLevelPrefixForALL[];
		static const PROGMEM prog_char debugLevelPrefixForINFO[];
		static const PROGMEM prog_char debugLevelPrefixForWARNING[];
		static const PROGMEM prog_char debugLevelPrefixForERROR[];

		const prog_char* className;

		byte level;

		DebugPrinter( const prog_char* _className );
		DebugPrinter( const prog_char* _className , byte _level );

		void setLevel( byte _level );
		void preMacro( const prog_char* debugLevelPrefix , const prog_char* functionName );

	//protected:

};

// =================================================

#endif /* DEBUGPRINTER_H_ */

