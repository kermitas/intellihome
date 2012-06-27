/*
 * RestService.h
 *
 *  Created on: 05-01-2012
 *      Author: root
 */

#ifndef RestService_H_
#define RestService_H_

// =================================================

#define REST_SERVICE_TYPE_READ_ONLY 0
#define REST_SERVICE_TYPE_UPDATEABLE_BY_MYSELF 1 // function renderValueSetter() of RestService will be executed to generate whole <form> .. </form> by itself
#define REST_SERVICE_TYPE_UPDATEABLE_TEXT 2
#define REST_SERVICE_TYPE_UPDATEABLE_BOOLEAN 3
#define REST_SERVICE_TYPE_UPDATEABLE_BOOLEAN_ONOFF 4
#define REST_SERVICE_TYPE_UPDATEABLE_BOOLEAN_ONE_TIME_EXECUTION 5 // this pseudo updateable task, button "execute" will be generated to execute some one-time action
#define REST_SERVICE_TYPE_UPDATEABLE_INT 6

// =================================================

#include <Stream.h>

// =================================================

class RestService
{
	public:

		RestService( unsigned char _id , const char* _name , unsigned char _type );

		virtual void writeValueToStream( Stream* stream );
		virtual void renderValueSetter( Stream* stream , bool useGETHttpMethodInForms ); // override this if type is updateable_by_myself

		virtual bool getBooleanValue(); // override this if type is updateable_boolean (or updateable_boolean sub-class)
		virtual void setBooleanValue( bool newValue ); // override this if type is updateable_boolean (or updateable_boolean sub-class)

		virtual void setTextValue( unsigned char* newValue ); // override this if type is updateable_by_myself or updateable_text

		virtual void setIntValue( int newValue ); // override this if type is updateable_int
		virtual int getIntMinValue(); // override this if type is updateable_int
		virtual int getIntMaxValue(); // override this if type is updateable_int

		unsigned char id;
		const char* name;
		unsigned char type;
};

// =================================================

#endif /* RestService_H_ */
