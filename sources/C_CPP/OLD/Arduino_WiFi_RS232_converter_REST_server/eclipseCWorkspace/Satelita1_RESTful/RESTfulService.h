/*
 * RESTfulService.h
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

#ifndef RESTFULSERVICE_H_
#define RESTFULSERVICE_H_

// =================================================

class RESTfulService
{
	public:

		//RESTfulService();

		virtual const char* getName() = 0;
		virtual bool isUpdateable() = 0;

		virtual int getValue() = 0;
		virtual bool setValue( int newValue ) = 0; // return true if real update was made

		virtual int getMinValue() = 0;
		virtual int getMaxValue() = 0;

		//~RESTfulService();
};

// =================================================

#endif /* RESTFULSERVICE_H_ */
