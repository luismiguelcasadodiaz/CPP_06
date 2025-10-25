#include "identify.hpp"
#include <iostream>

int main ( void )
{
	for( int i = 0 ; i < 10 ; i ++)
	{
		Base * guessptr = generate( );
		Base & guessref = *guessptr ;
		std::cout << "Pointer   identication equals ==>" ;
		identify( guessptr );
		std::cout << "Reference identication equals ==>" ;
		identify( guessref );
	}
	return 0;
}
