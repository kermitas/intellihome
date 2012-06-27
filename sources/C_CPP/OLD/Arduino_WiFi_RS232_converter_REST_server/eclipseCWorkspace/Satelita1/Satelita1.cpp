#include "Satelita1.h"

// =================================================

void setup()
{
	static const PROGMEM prog_char functionName[] = "setup";

	// ---------------------------------------------

	DEFAULT_OUTPUT.begin( SPEED_OF_SERIAL_FOR_CONSOLE_CONNECTION );

	fdev_setup_stream( &redirectedOut , redirectedOutPrintFunction , NULL , _FDEV_SETUP_WRITE );

	stdout = &redirectedOut ;

	//static const char prefix[] = "setup():";

	// ---------------

	heartBeatBuzzerRunnable.run();
	delay( 2 );
	heartBeatBuzzerRunnable.run();

	// ---------------

	//info( p << satelita1prefix << prefix << hl; )
	iln( "=============" )

	//p << satelita1prefix << prefix << "START (current debug level = " << CURRENT_DEBUG_LEVEL << ")" << endl;
	iln( "START (current debug level = %u)" , CURRENT_DEBUG_LEVEL )

	printReport();

	// ---------------

	//info( p << satelita1prefix << prefix << "entering userSetup()..." << endl; )
	iln( "entering userSetup()..." )

	userSetup();

	//info( p << satelita1prefix << prefix << "leaving userSetup()..." << endl; )
	iln( "leaving userSetup()..." )

	// ---------------

	printReport();

	// ---------------

	heartBeatBuzzerRunnable.run();
	delay( 2 );
	heartBeatBuzzerRunnable.run();

	// ---------------
}

// =================================================

void userSetup()
{
	// ---------------
	static const PROGMEM prog_char functionName[] = "userSetup";
	//static const char prefix[] = "userSetup():";

	// ---------------

	//analogReference( DEFAULT );

	/*
	static const PROGMEM prog_char functionName[] = "userSetup";
	//dp.aln( functionName , PSTR( "test11" ) );
	aln( "test222" );

	int i = 10;
	aln( "int 10 ze zmiennej %%u %u" , i );
	aln( "int 10 wpisany %%u %u" , 10 );
	aln( "int 10 ze zmiennej %%i %i" , i );
	aln( "int 10 wpisany %%i %i" , 10 );

	int i1 = -10;
	aln( "int -10 ze zmiennej %%u %u" , i1 );
	aln( "int -10 wpisany %%u %u" , -10 );
	aln( "int -10 ze zmiennej %%i %i" , i1 );
	aln( "int -10 wpisany %%i %i" , -10 );

	unsigned int i2 = 20;
	aln( "unsigned int 20 ze zmiennej %%u %u" , i2 );
	aln( "unsigned int 20 wpisany %%u %u" , 20 );

	unsigned long l = millis();
	aln( "unsigned long %%u %u" , l );
	l = millis();
	aln( "unsigned long %%u %u" , l );
	l = millis();
	aln( "unsigned long %%i %i" , l );*/

	// ---------------

	{
		addTaskToTaskManager( &heartBeatLEDTaskManagerRecord , "heartBeatLED" );
	}

	// ---------------

	{
		addTaskToTaskManager( &sampleTaskManagerRecord , "sampleTask" );
	}

	// ---------------

	//taskManager.removeByIndex( 3 );
	//taskManager.removeByIndex( 0 );
	//taskManager.removeByPointer( sampleTaskManagerRecordPtr );

	// ---------------

	//info( p << satelita1prefix << prefix << "Dallas DS18B20 bus initialization ..." << endl; )
	//dallasDS18B20Temperature.begin();

	// ---------------

	//info( p << satelita1prefix << prefix << "ethernet: initialization..." << endl; )
	//Ethernet.begin( mac , ip , gateway , subnet );

	//info( p << satelita1prefix << prefix << "ethernet: start listening for incomming connection..." << endl; )
	//serverSocket.begin();

	// ---------------

	/*
	{
		TaskManagerRecord* acceptIncommingConnectionTaskManagerRecordPtr = &acceptIncommingConnectionTaskManagerRecord;
		info( p << satelita1prefix << prefix << "adding sample task to taskManager, acceptIncommingConnectionTaskManagerRecord* = " << (int)acceptIncommingConnectionTaskManagerRecordPtr << endl )
		addTaskToTaskManager( acceptIncommingConnectionTaskManagerRecordPtr );
	}
	*/

	// ---------------

	{
		//addTaskToTaskManager( &restServerTaskManagerRecord , prefix , "restServerTask" );
	}

	// ---------------

	{
		//addTaskToTaskManager( &singleEthernetConnectionRestServerTaskManagerRecord , prefix , "singleEthernetConnectionRestServerTask" );
	}

	// ---------------

	{

		SERIAL_FOR_WIFI_CONNECTION.begin( SPEED_OF_SERIAL_FOR_WIFI_CONNECTION );

		//setSerial1( SPEED_OF_SERIAL_FOR_WIFI_CONNECTION , 'o' , 8 , 2 );

		//streamHFA11xRS232WiFiABC.resetInternalState();
		streamHFA11xRS232WiFi.resetInternalState();

		//UCSR3C = ( UCSR3C & ~_BV(UPM00) | _BV(UPM01) );

		//setSerial1( SPEED_OF_SERIAL_FOR_WIFI_CONNECTION , 'o' , 8 , 2 );

		//port1.begin( SPEED_OF_SERIAL_FOR_WIFI_CONNECTION , SP_8_BIT_CHAR | SP_2_STOP_BIT | SP_EVEN_PARITY );

		{
			//incommingByteBufferForStreamHFA11xRS232WiFi.printReport( "incommingByteBufferForStreamHFA11xRS232WiFi FROM Satelita1" ); // todo tmp
			//outgoingByteBufferForStreamHFA11xRS232WiFi.printReport( "outgoingByteBufferForStreamHFA11xRS232WiFi FROM Satelita1" ); // todo tmp

			//addTaskToTaskManager( &rwStateMachineTaskManagerRecord , "RS232ToWiFi_state_machine" );
		}

		{
			//rs232ToWiFiTask.setStream( &streamHFA11xRS232WiFi );
			addTaskToTaskManager( &rs232ToWiFiTaskManagerRecord , "rs232ToWiFiTask" );
		}
	}

	// ---------------

	/*
	{
		SERIAL_FOR_WIFI_CONNECTION.begin( SPEED_OF_SERIAL_FOR_WIFI_CONNECTION );

		//Serial1.begin( 57600 );
		//Serial2.begin( SPEED_OF_SERIAL_FOR_WIFI_CONNECTION );
		//Serial1.begin( 9600 );
		//Serial1.begin( 19200 );

		//streamConsolePrinter.setStream( &Serial2 );

		rs232ToWiFiTask.setStream( &streamConsolePrinter );
		//rs232ToWiFiTask.setStream( &SERIAL_FOR_WIFI_CONNECTION );

		addTaskToTaskManager( &rs232ToWiFiTaskManagerRecord , "rs232ToWiFiTask" );
	}*/

	/*{

		{
			Serial.println( "przed zdefiniowaniem tablicy uchar na 8B" );

			uint8_t * heapptr, * stackptr;

			stackptr = (uint8_t *)malloc(4);          // use stackptr temporarily
			heapptr = stackptr;                     // save value of heap pointer
			free(stackptr);      // free up the memory again (sets stackptr to 0)
			stackptr =  (uint8_t *)(SP);           // save value of stack pointer

			Serial.write( "heap=" ); Serial.println( (unsigned int)heapptr );
			Serial.write( "stack=" ); Serial.println( (unsigned int)stackptr );
		}

		{
			unsigned char commandRECEIVEoutgoingBuffer[ 8 ];


			//commandRECEIVEoutgoingBuffer[0] = '+';
			//commandRECEIVEoutgoingBuffer[1] = '+';
			//commandRECEIVEoutgoingBuffer[2] = '+';


			commandRECEIVEoutgoingBuffer[0] = 2;
			commandRECEIVEoutgoingBuffer[1] = 0;
			commandRECEIVEoutgoingBuffer[2] = 0;
			commandRECEIVEoutgoingBuffer[3] = 0;
			commandRECEIVEoutgoingBuffer[4] = 50;
			commandRECEIVEoutgoingBuffer[5] = 0;
			commandRECEIVEoutgoingBuffer[6] = 203;
			commandRECEIVEoutgoingBuffer[7] = 255;

			{
				Serial.println( "przed stream->write" );

				uint8_t * heapptr, * stackptr;

				stackptr = (uint8_t *)malloc(4);          // use stackptr temporarily
				heapptr = stackptr;                     // save value of heap pointer
				free(stackptr);      // free up the memory again (sets stackptr to 0)
				stackptr =  (uint8_t *)(SP);           // save value of stack pointer

				Serial.write( "heap=" ); Serial.println( (unsigned int)heapptr );
				Serial.write( "stack=" ); Serial.println( (unsigned int)stackptr );
			}

			for( byte i = 0 ; i < 8 ; i++ )
			{
				iln( "write byte %u" , commandRECEIVEoutgoingBuffer[i] )
				//wifiStream->write( commandRECEIVEoutgoingBuffer[i] );
				streamConsolePrinter.testWrite( commandRECEIVEoutgoingBuffer[i] );
			}
		}

		//stream->flush();

		delay( 500 );

		for( byte i = 0 ; i < 8 ; i++ )
		{
			//iln( "stream->available() = %i" , streamConsolePrinter.available() )
			//wifiStream->available();

			while( wifiStream->available() > 0 )
			{
				//iln( "read byte = %i" , streamConsolePrinter.read() )
				wifiStream->read();
			}

			delay( 1000 );
		}
	}*/

	// ---------------
}

// =================================================

void setSerial1( unsigned long baud , char parity , int wordlength , int stop )
{
	SERIAL_FOR_WIFI_CONNECTION.begin( baud );

	//set parity
	if ((parity == 'O')|(parity == 'o'))
	  {
	    UCSR3C = UCSR3C | B00110000;
	  }
	else if ((parity == 'E')|(parity == 'e'))
	  {
	    UCSR3C = UCSR3C | B00100000;
	  }
	else // ((parity == 'N')|(parity == 'n')))
	  {
	    UCSR3C = UCSR3C | B00000000;
	  }

	//set word length
	if (wordlength == 5)
	  {
	    UCSR3C = UCSR3C | B00000000;
	  }
	else if (wordlength == 6)
	  {
	    UCSR3C = UCSR3C | B00000010;
	   }
	else if (wordlength == 7)
	  {
	    UCSR3C = UCSR3C | B00000100;
	  }
	else if (wordlength == 9)
	  {
	    UCSR3C = UCSR3C | B00000110;
	    UCSR0B = UCSR0B | B00000100;
	  }
	else // (wordlength == 8)
	  {
	    UCSR3C = UCSR3C | B00000110;
	  }

	//set stop bits
	if (stop == 1)
	  {
	    UCSR3C = UCSR3C | B00000100;
	  }
	else // (stop == 2)
	  {
	    UCSR3C = UCSR3C | B00000000;
	  }
}

// =================================================

void loop()
{
	// ------------

	//all( p << satelita1prefix << "loop():executing taskManager.execute()..." << endl; )
	//aln( "loop():executing taskManager.execute()..." )

	taskManager.execute();

	// ------------
}

// =================================================

void addTaskToTaskManager( TaskManagerRecord* ptr , const char* desrtiption )//, const char* desrtiption )
{
	static const PROGMEM prog_char functionName[] = "addTaskToTaskManager";

	//info( p << satelita1prefix << "addTaskToTaskManager():" << "adding task '" << desrtiption << "' to taskManager, task ptr* = " << (int)ptr << ", executed from '" << prefix << "'" << endl; )
	iln( "adding task '%s' to taskManager, task ptr* = %u" , desrtiption , ptr )

	if( !taskManager.add( ptr ) )
	{
		//error( p << satelita1prefix << "addTaskToTaskManager():could not add taks!! ptr*=" << (int)ptr << endl; )
		eln( "addTaskToTaskManager():could not add taks!! ptr*=%u" , ptr )

		delay( 10 * 1000 );
		hardReset();
	}
}

// =================================================

void printReport()
{
	static const PROGMEM prog_char functionName[] = "printReport";
	//static const char* prefix = "printReport():";

	wln( "-------------" )

	wln( "freeRamMemory() = %i B, used RAM = %i B" , freeRamMemory() , ( CURRENT_RAM_SIZE - freeRamMemory() ) )
	wln( "millis() = %u" , millis() )

	wln( "-------------" )

	/*
	warning( p << satelita1prefix << prefix << hl; )

	warning( p << satelita1prefix << prefix << "freeRamMemory()=" << freeRamMemory() << ", used RAM = " << ( CURRENT_RAM_SIZE - freeRamMemory() ) << "B" << endl; )

	warning( p << satelita1prefix << prefix << "millis()=" << millis() << endl; )
	warning( p << satelita1prefix << prefix << "sizeof(void*)=" << sizeof(void*) << endl; )
	warning( p << satelita1prefix << prefix << hl; )
	*/
}

// =================================================

void hardReset()
{
	static const PROGMEM prog_char functionName[] = "hardReset";

	//error( p << satelita1prefix << "hardReset(): HARD RESET..." << endl; )
	eln( "hardReset(): HARD RESET..." )

	delay( 2 * 1000 );

	// TODO jakis sposob na zresetowanie sie tutaj zawrzec, prawdopodobnie ten z wyslanie pradu na odpowiedni pin, ktory bedzie polaczony ze zlaczem reset na plytce
}

// =================================================

static int redirectedOutPrintFunction( char c , FILE *stream )
{
	DEFAULT_OUTPUT.write(c) ;
    //return 0; // <-- powinno tu byc ale zablokowalem, moze to cos przyspieszy??
}

// =================================================

