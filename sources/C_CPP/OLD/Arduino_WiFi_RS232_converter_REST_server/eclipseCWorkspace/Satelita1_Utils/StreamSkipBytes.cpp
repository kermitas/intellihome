/*
 * StreamSkipBytes.cpp
 *
 *  Created on: 10-05-2012
 *      Author: root
 */

// =================================================

#include "StreamSkipBytes.h"

// =================================================

//const PROGMEM prog_char StreamSkipBytes::className[] = "StreamSkipBytes";

// =================================================

StreamSkipBytes::StreamSkipBytes(): dp( PSTR( "StreamSkipBytes" ) )//( Print& _p ) : p( _p )
{
	setStream( NULL );
	resetInternalState( 0 );
}

// =================================================

void StreamSkipBytes::setStream( Stream* _mainStream )
{
	mainStream = _mainStream;
}

// =================================================

void StreamSkipBytes::resetInternalState( unsigned int _skipBytesCount )
{
	skipBytesCount = _skipBytesCount;

	workAsByteCountSkipper = true;
}

// =================================================

void StreamSkipBytes::resetInternalState( char* _stopSequence , bool _leaveLastByteInStream )
{
	stopSequence = _stopSequence;
	alreadyMatchedBytesCount = 0;
	leaveLastByteInStream = _leaveLastByteInStream;

	workAsByteCountSkipper = false;
}

// =================================================

int StreamSkipBytes::read()
{
	static const PROGMEM prog_char functionName[] = "read";

	if( workAsByteCountSkipper )
	{
		unsigned int skippedBytesCount = 0;

		while( skipBytesCount > 0 && mainStream->available() > 0 )
		{
			int readByte = mainStream->read();

			//p << (char)readByte;

			if( readByte == -1 ) break;

			skippedBytesCount++;

			skipBytesCount--;
		}

		if( skipBytesCount == 0 )
		{
			return 1;
		}
		else
		if( mainStream->available() == 0 )
		{
			if( skippedBytesCount > 0 )
				return 0;
			else
				return -1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		bool thereWereDataRead = false;

		//while( mainStream->available() > 0 )
		while( true )
		{
			if( mainStream->available() == 0 )
			{
				if( thereWereDataRead )
				{
					//p << "StreamSkipBytes::read(): mainStream->available()==0, returning 0 (there were read and now there is no data in the stream)" << endl;
					//info( wpln( "mainStream->available()==0, returning 0 (there were read and now there is no data in the stream)" ) )
					iln( "mainStream->available()==0, returning 0 (there were read and now there is no data in the stream)" )

					return 0;
				}
				else
				{
					//p << "StreamSkipBytes::read():returning -1" << endl;
					return -1;
				}
			}

			int peekByte = mainStream->peek();

			//p << "StreamSkipBytes::read():peekByte = " << (char)peekByte << ", alreadyMatchedBytesCount=" << alreadyMatchedBytesCount << endl;
			//info( wpln( "peekByte = %i, alreadyMatchedBytesCount = %u" , peekByte , alreadyMatchedBytesCount ) )
			iln( "peekByte = %c (%u), alreadyMatchedBytesCount = %u" , peekByte , peekByte , alreadyMatchedBytesCount )

			if( peekByte == -1 ) //break;
			{
				//mainStream->read();

				if( thereWereDataRead )
				{
					//p << "StreamSkipBytes::read():peekByte == -1, returning 0 (there were read and now there is no data in the stream)" << endl;
					//info( wpln( "peekByte == -1, returning 0 (there were read and now there is no data in the stream)" ) )
					iln( "peekByte == -1, returning 0 (there were read and now there is no data in the stream)" )

					return 0;
				}
				else
				{
					//p << "StreamSkipBytes::read():returning -1" << endl;
					return -1;
				}
			}

			thereWereDataRead = true;

			if( stopSequence[alreadyMatchedBytesCount] == peekByte )
			{
				alreadyMatchedBytesCount++;

				if( stopSequence[alreadyMatchedBytesCount] == 0 )
				{
					if( !leaveLastByteInStream ) mainStream->read();

					//p << "StreamSkipBytes::read():returning 1" << endl;
					//info( wpln( "returning 1" ) )
					iln( "returning 1" )

					return 1;
				}
			}
			else
			{
				alreadyMatchedBytesCount = 0;
			}

			mainStream->read();
		}

		/*if( stopSequence[alreadyMatchedBytesCount] == 0 )
		{
			p << "StreamSkipBytes::read():returning 1" << endl;
			return 1;
		}
		else
		if( mainStream->available() == 0 )
		{
			if( skippedBytesCount > 0 )
			{
				p << "StreamSkipBytes::read():returning 0 (there were read and now there is no data in the stream)" << endl;
				return 0;
			}
			else
			{
				//p << "StreamSkipBytes::read():returning -1" << endl;
				return -1;
			}
		}
		else
		{
			p << "StreamSkipBytes::read():returning 0" << endl;
			return 0;
		}*/
	}
}

// =================================================

int StreamSkipBytes::peek()
{
	return mainStream->peek();
}

// =================================================

void StreamSkipBytes::flush()
{
	mainStream->flush();
}

// =================================================

size_t StreamSkipBytes::write( uint8_t b )
{
	return mainStream->write( b );
}

// =================================================

int StreamSkipBytes::available()
{
	return mainStream->available();
}

// =================================================


