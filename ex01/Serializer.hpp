#ifndef SERIALIZER_HH
#define SERIALIZER_HH

#include "Data.hpp"
#include <stdint.h>

class Serializer
{
	private:
		Serializer( void ) ;
		~Serializer( void ) ;
		Serializer( const Serializer & o ) ;
		Serializer & operator=( const Serializer & o ) ;
	public:
		static uintptr_t serialize( Data * ptr) ;
		static Data * deserialize( uintptr_t raw ) ;
};

#endif
