#include "ScalarConverter.hpp"


ScalarConverter::ScalarConverter( void )
{
	std::cout << COLOR_ss << "ScalarConverter default constructor called." << RESET_ss << std::endl;
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
ScalarConverter & ScalarConverter::operator=( const ScalarConverter & other )
{
	std::cout << COLOR_ss << "ScalarConverter copy    constructor called." << RESET_ss << std::endl;
	(void)other;
	return *this ;
}
void ScalarConverter::convert(const std::string & s)
{
	std::cout << "Passed argument >" << s << "<." << std::endl;

}
/*
Here's the BNF syntax for C++98 literals that you need to parse:
CHAR
bnf<char-literal> ::= "'" <c-char> "'"
<c-char>       ::= <any printable ASCII character except ' and \>
                 | <escape-sequence>
<escape-sequence> ::= "\n" | "\t" | "\r" | "\\" | "\'" | "\""
Examples: 'a', 'Z', '0', '\n', '\t'
INT
bnf<int-literal> ::= <sign>? <digit-sequence>
<sign>        ::= "+" | "-"
<digit-sequence> ::= <digit>+
<digit>       ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
Examples: 0, 42, -42, +42, 2147483647
FLOAT
bnf<float-literal> ::= <sign>? <floating-point> "f"
                  | <sign>? "inf" "f"
                  | "nan" "f"
<floating-point> ::= <digit-sequence> "." <digit-sequence>?
                   | <digit-sequence>? "." <digit-sequence>
                   | <digit-sequence>
Examples: 0.0f, 42.0f, -4.2f, .5f, 42.f, +inff, -inff, nanf
DOUBLE
bnf<double-literal> ::= <sign>? <floating-point>
                   | <sign>? "inf"
                   | "nan"
<floating-point> ::= <digit-sequence> "." <digit-sequence>?
                   | <digit-sequence>? "." <digit-sequence>

				   */
