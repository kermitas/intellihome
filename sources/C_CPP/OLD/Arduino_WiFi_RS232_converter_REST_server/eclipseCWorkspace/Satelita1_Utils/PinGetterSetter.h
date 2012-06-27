/*
 * PinGetterSetter.h
 *
 *  Created on: 28-04-2012
 *      Author: root
 */

#ifndef PINGETTERSETTER_H_
#define PINGETTERSETTER_H_

// =================================================

class PinGetterSetter
{
	public:
		virtual unsigned char getPin() = 0;
		virtual void setPin( unsigned char newPin ) = 0;
};

// =================================================

#endif /* PINGETTERSETTER_H_ */
