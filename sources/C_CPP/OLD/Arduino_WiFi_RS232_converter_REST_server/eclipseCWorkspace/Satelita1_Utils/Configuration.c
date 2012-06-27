
#ifndef CONFIGURATION_FILE_C_
#define CONFIGURATION_FILE_C_

// =================================================

#include <stdio.h>
#include <avr/pgmspace.h>

// =================================================
// definitions

/*
// w przyszlosci to wywalic, gdyz to juz jest w DebugPrinter
#define DEBUG_LEVEL_ALL 10
#define DEBUG_LEVEL_INFO 20
#define DEBUG_LEVEL_wARNING 30
#define DEBUG_LEVEL_ERROR 40
*/

// =================================================
// configuration

#define CURRENT_DEBUG_LEVEL 20

#define MAXIMUM_TASKS_IN_TASK_MANAGER_COUNT 5
#define DEFAULT_OUTPUT Serial
#define CURRENT_RAM_SIZE 8*1024

//#define LISTENING_TCP_IP_PORT 80

#define HEART_BEAT_LED_PIN 13
#define IS_HEART_BEAT_LED_INITIALLY_ON true
#define HEART_BEAT_BUZZER_PIN 8
#define IS_HEART_BEAT_BUZZER_INITIALLY_ON false

//#define LEDS_PIN 7
//#define ONE_WIRE_PIN 2

//#define MAC_ADDRESS 0x90,0xA2,0xDA,0x00,0x9B,0xDA
//#define IP_ADDRESS 192,168,2,20
//#define GATEWAY_ADDRESS 192,168,2,1
//#define SUBNET_MASK 255,255,255,0

#define BLOCK_UNTIL_FINISH_PROCESSING_INCOMMING_REQUEST false
#define HTML_FORMS_GET_OR_POST_METHOD true

#define SPEED_OF_SERIAL_FOR_CONSOLE_CONNECTION 115200 // 300, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, or 115200

#define SERIAL_FOR_WIFI_CONNECTION Serial3
#define SPEED_OF_SERIAL_FOR_WIFI_CONNECTION 115200 // 300, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, or 115200

//#define INCOMMING_BUFFER_SIZE_FOR_COMMUNICATION_WITH_RS232_WIFI 100
//#define OUTGOING_BUFFER_SIZE_FOR_COMMUNICATION_WITH_RS232_WIFI 120 // przy 18 dziala przy predkosci 9600, 19 juz nie, 18@19200 ok , 19@19200 err :(

// 19 @ 19200 zadzialalo z problemami

// konsola 115200 , wifi 115200, buffer dla wifi outgoing 150 incomming 50, buffer dla chunked 140
// konsola 115200 , wifi 115200, buffer dla wifi outgoing 160 incomming 50, buffer dla chunked 150
// konsola 115200 , wifi 115200, buffer dla wifi outgoing 200 incomming 50, buffer dla chunked 190 dziala ale strona sie sypie, cos nie dochodzi itp
// konsola 115200 , wifi 115200, buffer dla wifi outgoing 180 incomming 50, buffer dla chunked 170 czasem dziala
// konsola 115200 , wifi 115200, buffer dla wifi outgoing 180 incomming 90 oraz 80 oraz 60, buffer dla chunked 170 jest jakby gluchy na request z przegadarki www, w ogole nic, cisza

//DZIALA: konsola 115200 , wifi 115200, buffer dla wifi outgoing 110 incomming 50, buffer dla chunked 100

// =================================================
//macros

// w przyszlosci to wywalic, gdyz to juz jest w DebugPrinter
/*
#define all( x ) if( CURRENT_DEBUG_LEVEL <= DEBUG_LEVEL_ALL ) x
#define info( y ) if( CURRENT_DEBUG_LEVEL <= DEBUG_LEVEL_INFO ) y
#define warning( z ) if( CURRENT_DEBUG_LEVEL <= DEBUG_LEVEL_wARNING ) z
#define error( w ) if( CURRENT_DEBUG_LEVEL <= DEBUG_LEVEL_ERROR ) w
*/
// =================================================
//macros
/*
// w przyszlosci to wywalic, gdyz to juz jest w DebugPrinter

// printf_P with prefix className + "::" + functionName + "():"
#define pfp( className , functionName , str , varargs... )   { printf_P( PSTR( className ) ); printf_P( PSTR( "::" ) ); printf_P( PSTR( functionName ) ); printf_P( PSTR( "():" ) ); printf_P( PSTR( str ) , ##varargs ); }

// same as pfp() + new_line
#define pfpln( className , functionName , str , varargs... ) { printf_P( PSTR( className ) ); printf_P( PSTR( "::" ) ); printf_P( PSTR( functionName ) ); printf_P( PSTR( "():" ) ); printf_P( PSTR( str ) , ##varargs ); printf_P( PSTR( "\r\n" ) ); }

// printf_P with prefix className + "::" + functionName
// className should be available in scope, best way is to declare it like this:
// - in .h static const PROGMEM prog_char className[];
// - in .cpp const PROGMEM prog_char HFA11xRS232WiFiCRC::className[] = "your_class_name";
// functionName should be available in scope, best way is to declare it in current function static const PROGMEM prog_char functionName[] = "your_function_name";
#define wp( str , varargs... ) { printf_P( className ); printf_P( PSTR( "::" ) ); printf_P( functionName ); printf_P( PSTR( "():" ) ); printf_P( PSTR( str ) , ##varargs ); }

// same as wp() + new_line
#define wpln( str , varargs... ) { printf_P( className ); printf_P( PSTR( "::" ) ); printf_P( functionName ); printf_P( PSTR( "():" ) ); printf_P( PSTR( str ) , ##varargs ); printf_P( PSTR( "\r\n" ) ); }
*/
// =================================================

#endif /* CONFIGURATION_FILE_C_ */
