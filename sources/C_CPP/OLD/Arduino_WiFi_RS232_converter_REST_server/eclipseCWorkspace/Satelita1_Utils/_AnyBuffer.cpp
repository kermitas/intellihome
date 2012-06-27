/*
 * AnyBuffer.cpp
 *
 *  Created on: 17-05-2012
 *      Author: root
 */

// =================================================
/*
#include "AnyBuffer.h"

// =================================================

template< typename DataType , typename SizeType >
AnyBuffer<DataType,SizeType>::AnyBuffer( DataType* _array , const SizeType _capacity )
{
	init( _array , _capacity , 0 , _capacity - 1 );
}

// =================================================

template< typename DataType , typename SizeType >
AnyBuffer<DataType,SizeType>::AnyBuffer( DataType* _array , const SizeType _capacity , SizeType _position , SizeType _limit )
{
	init( _array , _capacity , _position , _limit );
}

// =================================================

template< typename DataType , typename SizeType >
void AnyBuffer<DataType,SizeType>::init( DataType* _array , const SizeType _capacity , SizeType _position , SizeType _limit )
{
	array = _array;
	capacity = _capacity;

	position = 0;
	limit = 0;

	setLimit( _limit );
	setPosition( _position );
}

// =================================================

template< typename DataType , typename SizeType >
void AnyBuffer<DataType,SizeType>::setPosition( SizeType _position )
{
	position = _position > limit ? limit : ( _position < 0 ? 0 : _position );
}

// =================================================

template< typename DataType , typename SizeType >
void AnyBuffer<DataType,SizeType>::setLimit( SizeType _limit )
{
	limit = _limit < position ? position : ( _limit >= capacity ? capacity-1 : _limit );
}

// =================================================

template< typename DataType , typename SizeType >
SizeType AnyBuffer<DataType,SizeType>::getRemaining()
{
	return limit - position;
}

// =================================================

template< typename DataType , typename SizeType >
void AnyBuffer<DataType,SizeType>::setPositionAndLimit( SizeType _position , SizeType _limit )
{
	setLimit( _limit );
	setPosition( _position );
}

// =================================================

template< typename DataType , typename SizeType >
void AnyBuffer<DataType,SizeType>::clearArrayWorkingPart()
{
	for( SizeType i = position ; i <= limit ; i++ ) array[i] = 0;
}

// =================================================

template< typename DataType , typename SizeType >
void AnyBuffer<DataType,SizeType>::clearArrayWorkingPart( SizeType fromIndex , SizeType toIndex )
{
	if( fromIndex < 0 ) fromIndex = 0;
	if( toIndex >= capacity ) toIndex = capacity-1;

	for( SizeType i = fromIndex ; i <= toIndex ; i++ ) array[i] = 0;
}

// =================================================

template< typename DataType , typename SizeType >
DataType AnyBuffer<DataType,SizeType>::get()
{
	DataType result = array[ position++ ];

	if( position > limit ) position = limit;

	return result;
}

// =================================================

template< typename DataType , typename SizeType >
DataType AnyBuffer<DataType,SizeType>::get( SizeType index )
{
	return array[ index ];
}

// =================================================

template< typename DataType , typename SizeType >
void AnyBuffer<DataType,SizeType>::put( DataType data )
{
	array[ position++ ] = data;
	if( position > limit ) position = limit;
}

// =================================================

template< typename DataType , typename SizeType >
void AnyBuffer<DataType,SizeType>::put( DataType data , SizeType index )
{
	array[ index ] = data;
}

// =================================================

template< typename DataType , typename SizeType >
bool AnyBuffer<DataType,SizeType>::writeToStream( Stream* stream )
{
	while( limit - position )
	{
		if( stream->write( array[ position ] ) != 1 ) return false;
		position++;
	}

	return true;
}
*/
// =================================================
