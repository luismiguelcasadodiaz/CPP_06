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
	std::cout << "Passed argument >" << s << "< is digit "  ;
	std::cout << ScalarConverter::isDigit(s.at(0)) << std::endl;
	std::cout << "Passed argument >" << s << "< is printable "  ;
	std::cout << ScalarConverter::isCharc(s.at(0)) << std::endl;
	std::cout << "Passed argument >" << s << "< is Escape "  ;
	std::cout << ScalarConverter::isEscSeq(s.at(0)) << std::endl;
	std::cout << "Passed argument >" << s << "< is DigitSeq "  ;
	std::cout << ScalarConverter::isDigitSeq(s) << std::endl;
	std::cout << "Passed argument >" << s << "< is floatPoint "  ;
	std::cout << ScalarConverter::isFloatPoint(s) << std::endl;

}


bool ScalarConverter::isCharc( char c) 
{	
	if ( std::isprint( static_cast<unsigned char>(c) ) )
	{
		if ( (c != '\\') and (c != '\'') )
		{
			return true ;
		}
	}
	return false ;
}
bool ScalarConverter::isEscSeq( char c)
{	
	if ( c == '\n' || // Line Feed (LF), Decimal 10
         c == '\t' || // Horizontal Tab (HT), Decimal 9
         c == '\r' || // Carriage Return (CR), Decimal 13
         c == '\\' || // Backslash, Decimal 92
         c == '\'' || // Single Quote, Decimal 39
         c == '"')    // Double Quote, Decimal 34
    {
        return true;
    }
	return false ;
}
bool ScalarConverter::isDigit( char c)
{
	if ( std::isdigit( static_cast<unsigned char>(c) ) )
	{
		return true ;
	}
	return false  ;
}
bool ScalarConverter::isSign( char c)
{	
	if ( c == '+' ||  // Positive sign 
         c == '-')    // Negative Sign
    {
        return true;
    }
	return false ;
}
bool ScalarConverter::isDigitSeq( const std::string & str )
{ 
	bool result = true ;
	for (size_t i = 0 ; i < str.size(); i++ )
	{
		result = result && ScalarConverter::isDigit( str.at(i) ) ;
	}
	
	return result ;
}

/*
##### isFloatpoint ( string str )

Returns true if any of four posibilities happens
 1. <digit-sequence> "." <digit-sequence>
 2. <digit-sequence> "."
 3. "." <digit-sequence>
 4. <digit-sequence>

```bnf
<floating-point> ::= <digit-sequence> "." <digit-sequence>?
                   | <digit-sequence>? "." <digit-sequence>
                   | <digit-sequence>
```
 * */

bool ScalarConverter::isFloatPoint( const std::string & str )
{
	size_t len = str.size();
	size_t dot_pos = str.find(".") ;
	if ( dot_pos == std::string::npos ) // 4.-<digit-sequence>
	{
		return isDigitSeq(str) ;
	}
	if ( str.at(0) == '.' )
	{
		return isDigitSeq( str.substr(1) ) ;
	}
	if ( str.at( len - 1) == '.' )
	{
		return isDigitSeq( str.substr(0, len - 1) ) ;
	}
	return (  isDigitSeq( str.substr(0, dot_pos ) ) &&  isDigitSeq( str.substr(dot_pos ) ) ) ;
}
bool ScalarConverter::isChar ( const std::string & str )
{ 
	(void)str;
	return false ;
}
bool ScalarConverter::isInt ( const std::string & str )
{ 
	(void)str;
	return false ;
}
bool ScalarConverter::isFloat ( const std::string & str )
{ 
	(void)str;
	return false ;
}
bool ScalarConverter::isDouble ( const std::string & str ) 
{ 
	(void)str;
	return false ;
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
