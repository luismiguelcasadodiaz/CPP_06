#include "Serializer.hpp"


Serializer::Serializer( void ) {}
Serializer::~Serializer( void ) {}
Serializer::Serializer( const Serializer & o ) { (void)o ; }
Serializer & Serializer::operator=( const Serializer & o )
{ 
	(void)o ;
	return *this;
}
uintptr_t Serializer::serialize( Data * ptr) {
	return reinterpret_cast<uintptr_t>(ptr);
}
Data * Serializer::deserialize( uintptr_t raw ) {
	return reinterpret_cast<Data *>(raw) ;}
