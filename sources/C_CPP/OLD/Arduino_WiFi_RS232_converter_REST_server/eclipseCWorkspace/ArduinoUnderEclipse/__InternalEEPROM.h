/*
 * InternalEEPROM.h
 *
 *  Created on: 10-01-2012
 *      Author: root
 */

#ifndef INTERNALEEPROM_H_
#define INTERNALEEPROM_H_

//#include </home/as/ARDUINO/arduino-1.0-IDE/libraries/EEPROM/EEPROM.h>
#include <EEPROM.h>
//#include "EEPROMData.h"

#include "QueueList.h"
#include "InternalEEPROMMemoryMapRecord.h"
#include "InternalEEPROMDataToWrite.h"

// [seprator][[data][seprator]...[data][seprator]][seprator]
// dane zaczynaja sie wiec od adresu nr 1
// sekcja [data] nie moze byc pusta (length=0) oraz nie moze posiadac w soibe znaczka [separator]

/*
class InternalEEPROM
{
	public:
		InternalEEPROM( unsigned int _maxSize , uint8_t _dataSeparator );

		void clear();
		unsigned int getFreeSpace();
		unsigned int getUsedSpace();
		unsigned int getStoredDatasCount(); // zwraca ile jest zapisanych sekcji data (pozniej do kazdej mozna sie odwolad podajac jej index
		//
		//unsigned int getDataLength( unsigned int index ); // jesli zwroci 0 to znaczy, ze cos jest nie tak, gdyz nie ma u nas "zerowych" danych

		InternalEEPROMMemoryMapRecord* read( unsigned int index );
		bool write( unsigned int dataLength , uint8_t* data );

		bool write( QueueList<InternalEEPROMDataToWrite*>* queue );

		//unsigned int* getAllStatingAddresses();
		QueueList<InternalEEPROMMemoryMapRecord*>* getMemoryMap();

		bool remove( unsigned int index ); // true jesli znalazl i usunal, false jesli nie znalazl

		void printMemeory();

		virtual ~InternalEEPROM();

	protected:
		unsigned int maxSize;
		uint8_t dataSeparator;

		bool isMemoryIsUsedForTheFirstTime();
		void formatMemory();
		unsigned int getFirstFreeAddress(); // jesli zwroci 0 to oznacza, ze juz nie ma wolnego miejsca
		unsigned int getNearestSeparatorAddress( unsigned int startAddress );
		unsigned int getDataAddress( unsigned int index ); // jesli zwroci 0 to znaczy, ze cos poszlo nie tak, nie znalazl

		bool checkDataToWrite( unsigned int dataLength , uint8_t* data );
		bool checkFreeSpaceForData( unsigned int firstFreeAddress , unsigned int dataLength );

		//void moveMemorySegment( unsigned int startWriteAddress , unsigned int startReadAddress , unsigned int stopReadAddress );
};

#endif*/ /* INTERNALEEPROM_H_ */
