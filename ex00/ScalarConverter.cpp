#include "ScalarConverter.hpp"


ScalarConverter::ScalarConverter( void )
{
	std::cou << COLOR_ss << "ScalarConverter default constructor called." << RESET_ss << std::endl;
}
ScalarConverter::~ScalarConverter( void )
{
	std::cout << COLOR_ss << "ScalarConverter default destructor called." << RESET_ss << std::endl;
}
ScalarConverter::ScalarConverter( const ScalarConverter & other )
{
	std::cout << COLOR_ss << "ScalarConverter copy    constructor called." << RESET_ss << std::endl;
	(void)other;
}
ScalarConverter & ScalarConverter::ScalarConverter( const ScalarConverter & other )
{
	std::cout << COLOR_ss << "ScalarConverter copy    constructor called." << RESET_ss << std::endl;
	(void)other;
	//return *this ;
}
ScalarConverter::convert(const std::string & s)
{
	(void) s;
}
