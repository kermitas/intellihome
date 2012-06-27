/*
 * StreamHFA11xRS232WiFi.cpp
 *
 *  Created on: 11-05-2012
 *      Author: root
 */

/*
// =================================================

#include "StreamHFA11xRS232WiFi.h"

// =================================================

StreamHFA11xRS232WiFi::StreamHFA11xRS232WiFi( AnyBuffer< byte , byte >* _inputBuffer , AnyBuffer< byte , byte >* _outputBuffer , unsigned char _numberOfRetriesWhileAskingForIncommingData , unsigned char _numberOfRetriesWhileSendingOutgoingData ) : dp( PSTR( "StreamHFA11xRS232WiFi" ) ) //, inputBufferObj( &incommingByteBufferArray[0] , (byte)25 ) , outputBufferObj( &outgoingByteBufferArray[0] , (byte)25 )
{
	inputBuffer = _inputBuffer;
	outputBuffer = _outputBuffer;

	numberOfRetriesWhileAskingForIncommingData = _numberOfRetriesWhileAskingForIncommingData;
	numberOfRetriesWhileSendingOutgoingData = _numberOfRetriesWhileSendingOutgoingData;

	resetInternalState();
}

// =================================================

void StreamHFA11xRS232WiFi::setStream( Stream* _stream )
{
	crcStream.setStream( _stream );
}

// =================================================

void StreamHFA11xRS232WiFi::resetInternalState()
{
	crcStream.resetInternalState();

	inputBuffer->clearArray( 0 , inputBuffer->capacity-1 );
	outputBuffer->clearArray( 0 , outputBuffer->capacity-1 );

	inputBuffer->setPositionAndLimit( 0 , 0 );
	outputBuffer->setPositionAndLimit( 0 , outputBuffer->capacity );

	commandSerialNumber = 0;
}

// =================================================

void StreamHFA11xRS232WiFi::sendRECVndReadRECVACK()
{
	// wchodzac do tej metody przyjmujemy, ze obecne dane znajduja sie w buforze pomiedzy 'position', a 'limit'
	// w wyniku dzialania dopisujemy nowe dane za limitem
	// a nastepnie ustawiamy position tam bedzie byl, zas stary limit powiekszamy o nowo dopisane dane

	// ---

	if( read_error != 0 ) return;

	// ---

	if( inputBuffer->getUnusedSpace() == 0 ) return;

	// ---

	static const PROGMEM prog_char functionName[] = "sendRECVndReadRECVACK";

	// ---

	if( inputBuffer->position == inputBuffer->limit == inputBuffer->capacity ) inputBuffer->setPositionAndLimit( 0 , 0 );

	for( unsigned char i = 0 ; i < numberOfRetriesWhileAskingForIncommingData ; i++ )
	{
		clearReadError();

		sendRECV();

		if( read_error == 0 )
		{
			readRECVACK();

			if( read_error == 0 )
			{
				commandSerialNumber++;
				break;
			}
			else
			{
				wln( "problem while receiving RECV ACK command, read_error code = %i, retry %u / %u" , read_error , i , numberOfRetriesWhileAskingForIncommingData )
			}
		}
		else
		{
			wln( "problem while sending RECV command, read_error code = %i, retry %u / %u" , read_error , i , numberOfRetriesWhileAskingForIncommingData )
		}
	}
}

// =================================================

void StreamHFA11xRS232WiFi::sendRECV()
{
	// ---

	crcStream.resetOutgoingState();

	// ---

	if(
		// command
		crcStream.write( (unsigned char)2 ) != 1 ||

		// sn
		crcStream.write( commandSerialNumber ) != 1 ||

		// reserved two bytes (0 and 0)
		crcStream.write( 0 ) != 1 ||
		crcStream.write( 0 ) != 1 ||

		// low byte of incomming buffer size
		crcStream.write( inputBuffer->getUnusedSpace() ) != 1 ||

		// high byte of incomming buffer size
		crcStream.write( (unsigned char)0 ) != 1 ||

		!crcStream.writeOutgoingDataCRCToStream()
	)
	{
		read_error = -1;
		return;
	}
}

// =================================================

void StreamHFA11xRS232WiFi::readRECVACK()
{
	static const PROGMEM prog_char functionName[] = "readRECVACK";

	// ---

	crcStream.resetIncommingState();

	// ---

	while( crcStream.available() < 6 ); // waiting for 1B command, 1B serial number, 2B reserved, 2B size

	// info : ufamy, ze strumien jesli zglosil, iz ma dane dostepne (available) to nie wytnie zadnego numeru
	// i nie zwroci tutaj nigdzie -1

	// ---

	// command
	if( crcStream.read() != 2 ) { read_error = -2; return; }

	// sn
	if( crcStream.read() != commandSerialNumber ) { read_error = -3; return; }

	// ---

	// reserved two bytes byte
	if( crcStream.read() != 0 ) { read_error = -4; return; }
	if( crcStream.read() != 0 ) { read_error = -4; return; }

	// ---

	unsigned int size;

	size = crcStream.read(); // low byte of incomming data length
	size += 256 * crcStream.read(); // high byte of incomming data length

	if( size > inputBuffer->getUnusedSpace() ) { read_error = -6; return; }

	// ---

	byte positionBefore = inputBuffer->position;
	byte limitBefore = inputBuffer->limit;

	if( size > 0 )
	{
		iln( "command=2, sn=%u, incomming data size=%u" , commandSerialNumber , size )

		while( crcStream.available() < size ); // waiting for incomming data

		inputBuffer->setPositionAndLimit( limitBefore , inputBuffer->limit + size );

		{ // todo temporary
			iln( "positionBefore=%u , limitBefore=%u , incomming data size=%u" , positionBefore , limitBefore , size );
			inputBuffer->printReport( "FROM readRECVACK() when buffer is set before reading" );
			//delay( 1000 );
		}

		while( inputBuffer->getRemaining() > 0 )
		{
			int readByte = crcStream.read();

			if( readByte == -1 )
			{
				inputBuffer->setPositionAndLimit( positionBefore , inputBuffer->position );

				read_error = -7;
				return;
			}

			inputBuffer->put( readByte );

			{ // todo temporary
				inputBuffer->printReport( "FROM readRECVACK() while putting bytes" );
				//delay( 1000 );
			}
		}

		inputBuffer->setPositionAndLimit( positionBefore , inputBuffer->position );

		//delay( 1000 ); // todo temporary
	}

	// ---

	// todo temporary
	if( inputBuffer->getRemaining() > 0 )
	{
		inputBuffer->printReport( "FROM readRECVACK()" );
		//delay( 3000 );
	}

	// ---

	if( !compareCRCsumWithCRCsumCalculatedOnTwoIncommingBytes( crcStream.getIncommingDataCRC() ) )
	{
		wln( "incomming CRC (in RECV_ACK) and our locally counted CRC does not match! setting write_error to -5" )

		delay( 3000 ); // todo temporary

		inputBuffer->setPositionAndLimit( positionBefore , limitBefore );

		read_error = -5;
		return;
	}
}

// =================================================

bool StreamHFA11xRS232WiFi::compareCRCsumWithCRCsumCalculatedOnTwoIncommingBytes( unsigned int crcCountedByUnderlyingCRCStream )
{
	static const PROGMEM prog_char functionName[] = "compareCRCsumWithCRCsumCalculatedOnTwoIncommingBytes";

	while( crcStream.available() < 2 ); // waiting for 2B of crc

	unsigned int crcCountedUsingTwoLastBytes = 0;

	crcCountedUsingTwoLastBytes = (unsigned char)crcStream.read(); // first byte of crc (low byte of u16)

	crcCountedUsingTwoLastBytes += 256 * (unsigned char)crcStream.read(); // second byte of crc (high byte of u16)

	aln( "crcCountedUsingTwoLastBytes = %u , crcCountedByUnderlyingCRCStream = %u" , crcCountedUsingTwoLastBytes , crcCountedByUnderlyingCRCStream )

	return crcCountedUsingTwoLastBytes == crcCountedByUnderlyingCRCStream;
}

// =================================================

int StreamHFA11xRS232WiFi::readOrPeek( bool justDoPeek )
{
	if( read_error == 0 )
	{
		if( inputBuffer->getRemaining() == 0 ) sendRECVndReadRECVACK();

		if( inputBuffer->getRemaining() > 0 )
		{
			return justDoPeek ? inputBuffer->array[ inputBuffer->position ] : inputBuffer->get();
		}
	}

	return -1;
}

// =================================================

int StreamHFA11xRS232WiFi::read()
{
	return readOrPeek( false );
}

// =================================================

int StreamHFA11xRS232WiFi::peek()
{
	return readOrPeek( true );
}

// =================================================

void StreamHFA11xRS232WiFi::sendSENDAndReadSENDACK()
{
	// wchodzac do tej metody przyjmujemy, ze dane do wyslania znajduja sie pomiedzy 0, a obecnym 'position'
	// tak wiec position dajemy na 0, limit na obecne position
	// te dane staramy sie wyslac, a jak sie uda to konczymy robote
	// z ustawionym position=0, a limit na tyle ile jest capacity

	if( getWriteError() != 0 ) return;

	// ---

	if( outputBuffer->position == 0 ) return;

	// ---

	static const PROGMEM prog_char functionName[] = "sendSENDAndReadSENDACK";

	// ---

	for( unsigned char i = 0 ; i < numberOfRetriesWhileSendingOutgoingData ; i++ )
	{
		clearWriteError();

		byte positionBefore = outputBuffer->position;

		outputBuffer->setPositionAndLimit( 0 , positionBefore );

		sendSEND();

		if( getWriteError() == 0 )
		{
			readSENDACK();

			if( getWriteError() == 0 )
			{
				outputBuffer->setPositionAndLimit( 0 , outputBuffer->capacity );
				commandSerialNumber++;
				break;
			}
			else
			{
				wln( "problem while receiving SEND ACK command, getWriteError() = %i, retry %u / %u" , getWriteError() , i , numberOfRetriesWhileSendingOutgoingData )
			}
		}
		else
		{
			wln( "problem while sending SEND command, getWriteError() = %i, retry %u / %u" , getWriteError() , i , numberOfRetriesWhileSendingOutgoingData )
		}

		if( getWriteError() != 0 ) outputBuffer->setPositionAndLimit( positionBefore , outputBuffer->capacity );
	}
}

// =================================================

void StreamHFA11xRS232WiFi::sendSEND()
{
	// ---

	crcStream.resetOutgoingState();

	// ---

	if(
		// command
		crcStream.write( (unsigned char)1 ) != 1 ||

		// sn
		crcStream.write( commandSerialNumber ) != 1 ||

		// reserved two bytes byte (0 and 0)
		crcStream.write( (unsigned char)0 ) != 1 ||
		crcStream.write( (unsigned char)0 ) != 1 ||

		// low byte of data length
		crcStream.write( outputBuffer->getRemaining() ) != 1 ||
		//crcStream.write( outputBuffer->position ) != 1 ||

		// high byte of data length
		crcStream.write( (unsigned char)0 ) != 1 ||

		// sending data
		!outputBuffer->writeToStream( &crcStream ) ||

		!crcStream.writeOutgoingDataCRCToStream()
	)
	{
		setWriteError( -1 );
		return;
	}

	// ---
}

// =================================================

void StreamHFA11xRS232WiFi::readSENDACK()
{
	static const PROGMEM prog_char functionName[] = "readSENDACK";

	// ---

	crcStream.resetIncommingState();

	// ---

	while( crcStream.available() == 5 ); // 1B command, 1B serial number, 2B reserved, 1B ack info

	// ---

	// command
	if( crcStream.read() != 1 ) { setWriteError( -2 ); return; }

	// sn
	if( crcStream.read() != commandSerialNumber ) { setWriteError( -3 ); return; }

	// ---

	// reserved two bytes
	if( crcStream.read() != 0 ) { setWriteError( -4 ); return; }
	if( crcStream.read() != 0 ) { setWriteError( -4 ); return; }

	// ---

	// ack info
	while( crcStream.available() == 0 );
	if( crcStream.read() != 9 ) { setWriteError( -6 ); return; }

	// ---

	if( !compareCRCsumWithCRCsumCalculatedOnTwoIncommingBytes( crcStream.getIncommingDataCRC() ) )
	{
		wln( "incomming CRC (in SEND_ACK) and our locally counter CRC does not match! setting write_error to -5" )

		setWriteError( -5 );
		return;
	}

	// ---
}

// =================================================

void StreamHFA11xRS232WiFi::flush()
{
	sendSENDAndReadSENDACK();
}

// =================================================

size_t StreamHFA11xRS232WiFi::write( uint8_t b )
{
	if( getWriteError() == 0 )
	{
		if( outputBuffer->getRemaining() == 0 )
		{
			sendSENDAndReadSENDACK();

			if( outputBuffer->getRemaining() == 0 || getWriteError() != 0 ) return 0;
		}

		outputBuffer->put( b );

		if( outputBuffer->getRemaining() == 0 ) sendSENDAndReadSENDACK();

		return 1;
	}
	else
	{
		return 0;
	}
}

// =================================================

int StreamHFA11xRS232WiFi::available()
{
	if( read_error == 0 )
	{
		if( inputBuffer->getRemaining() == 0 )
		{
			sendRECVndReadRECVACK();

			if( read_error != 0 ) return 0;
		}

		return inputBuffer->getRemaining();
	}
	else
	{
		//return -1;
		return 0;
	}
}

// =================================================

void StreamHFA11xRS232WiFi::clearReadError()
{
	read_error = 0;
}

// =================================================

int StreamHFA11xRS232WiFi::getReadError()
{
	return read_error;
}

// =================================================
*/

