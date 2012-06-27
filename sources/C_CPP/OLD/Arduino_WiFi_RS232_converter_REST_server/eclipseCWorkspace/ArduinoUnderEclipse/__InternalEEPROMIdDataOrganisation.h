/*
 * InternalEEPROMIdDataOrganisation.h
 *
 *  Created on: 10-01-2012
 *      Author: root
 */
/*
#ifndef INTERNALEEPROMIDDATAORGANISATION_H_
#define INTERNALEEPROMIDDATAORGANISATION_H_

#include "InternalEEPROM.h"

class InternalEEPROMIdDataOrganisation
{
	public:
		InternalEEPROMIdDataOrganisation( InternalEEPROM* _ieeprom );

		bool contains( uint8_t dataId );
		bool remove( uint8_t dataId ); // true jesli znalazl i usunal, false jesli nie znalazl

		bool write( uint8_t dataId , int dataLength , uint8_t* data );
		InternalEEPROMMemoryMapRecord* read( uint8_t dataId );

		virtual ~InternalEEPROMIdDataOrganisation();

	protected:
		InternalEEPROM* ieeprom;

		InternalEEPROMMemoryMapRecord* getMemoryRecord( uint8_t dataId ); // jesli zwrocil NULL to znaczy, ze nie znalazl
};

#endif *//* INTERNALEEPROMIDDATAORGANISATION_H_ */
