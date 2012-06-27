/*
 * LedOnOffRunnable.cpp
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

#include "SampleTaskRunnable.h"

// =================================================

//const PROGMEM prog_char SampleTaskRunnable::className[] = "SampleTaskRunnable";

// =================================================

SampleTaskRunnable::SampleTaskRunnable( const PROGMEM prog_char* _str , unsigned short _sleepInMs ) : dp( PSTR( "SampleTaskRunnable" ) )//: p(_p)
{
	str =  _str;
	sleepInMs = _sleepInMs;
}

// =================================================

void SampleTaskRunnable::run()
{
	static const PROGMEM prog_char functionName[] = "run";

	//p << "SampleTaskRunnable:run():" << str << endl;

	//info( printf_P( PSTR( className ) ); printf_P( PSTR( "::" ) ); printf_P( PSTR( functionName ) ); printf_P( PSTR( "():" ) ); printf( str ); printf_P( PSTR( "\r\n" ) ); )

	if( dp.level <= DEBUG_LEVEL_INFO || CURRENT_DEBUG_LEVEL <= DEBUG_LEVEL_INFO  )
	{
		dp.preMacro( dp.debugLevelPrefixForINFO , functionName );
		/*printf_P( dp.debugLevelPrefixForINFO );

		printf_P( dp.className );

		printf_P( dp.classNameAndFunctionNameSpacer );

		printf_P( functionName );

		printf_P( dp.functionNamePostfix );*/

		//printf_P( dp.className );
		//printf_P( PSTR( "::" ) );
		//printf_P( functionName );
		//printf_P( PSTR( "():" ) );
		printf_P( str );
		//printf_P( PSTR( "\r\n" ) );

		printf_P( dp.newLine );
	}

	delay( sleepInMs );
}

// =================================================

//SampleTaskRunnable::~SampleTaskRunnable() {}

// =================================================

