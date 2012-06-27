/*
 * DebugPrinter.h
 *
 *  Created on: 08-01-2012
 *      Author: root
 */

/*
#ifndef DEBUGPRINTER_H_
#define DEBUGPRINTER_H_

#include <Arduino.h>
#include "PrinterSimple.h"

class PrinterDebug
{
	public:

		PrinterSimple* ps;

		PrinterDebug( PrinterSimple* _printerSimple , const char* _prefix );

		void p( const char* str );
		void pln( const char* str );

		virtual ~PrinterDebug();

	protected:
		const char* prefix;
};

#endif*/ /* DEBUGPRINTER_H_ */
