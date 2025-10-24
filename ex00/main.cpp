#include "ScalarConverter.hpp"

int main( int argc, char** argv )
{
	if ( ( argc == 1 ) || ( argc > 2) ) {
		std::cout << "Usage: ./convert <arg> " << std::endl;
		return 0 ;
	}
	//std::cout << "Passed argument >" << argv[1] << "<." << std::endl;
	ScalarConverter::convert( argv[1] ) ;
	return 0;
}
