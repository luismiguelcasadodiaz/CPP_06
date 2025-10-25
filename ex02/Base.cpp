#include "Base.hpp"

Base::~Base( void ){}
Base::Base( void ){}
Base::Base( const Base & other )
{ 
	(void)other;
}
Base & Base::operator=( const Base & other )
{
	(void)other;
	return *this;
}
