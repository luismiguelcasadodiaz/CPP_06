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
	std::cout << "Passed argument >" << s << "< is      digit "  ;
	std::cout << ScalarConverter::isDigit(s.at(0)) << std::endl;
	std::cout << "Passed argument >" << s << "< is  printable "  ;
	std::cout << ScalarConverter::isCharc(s.at(0)) << std::endl;
	std::cout << "Passed argument >" << s << "< is     Escape "  ;
	std::cout << ScalarConverter::isEscSeq(s.at(0)) << std::endl;
	std::cout << "Passed argument >" << s << "< is   DigitSeq "  ;
	std::cout << ScalarConverter::isDigitSeq(s) << std::endl;
	std::cout << "Passed argument >" << s << "< is floatPoint "  ;
	std::cout << ScalarConverter::isFloatPoint(s) << std::endl;
	std::cout << "Passed argument >" << s << "< is       CHAR "  ;
	std::cout << ScalarConverter::isChar(s) << std::endl;
	std::cout << "Passed argument >" << s << "< is        INT "  ;
	std::cout << ScalarConverter::isInt(s) << std::endl;
	std::cout << "Passed argument >" << s << "< is      FLOAT "  ;
	std::cout << ScalarConverter::isFloat(s) << std::endl;
	std::cout << "Passed argument >" << s << "< is     DOUBLE "  ;
	std::cout << ScalarConverter::isDouble(s) << std::endl;

	if ( isChar(s) ) { 
		showChr(s) ;
	} else if ( isFloat(s) ) {
		showFlo(s) ;
	} else if ( isInt(s) ) {
		showInt(s) ;
	} else if ( isDouble(s) ) {
		showDou(s) ;
	} else {
	}



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
	return (  isDigitSeq( str.substr(0, dot_pos ) ) &&  isDigitSeq( str.substr(dot_pos + 1 ) ) ) ;
}
bool ScalarConverter::isChar ( const std::string & str )
{ 
	return str.size() == 3 &&
		str.at(0) == '\'' && 
		str.at(2) == '\'' && 
		( isEscSeq( str.at(1) ) || isCharc( str.at(1) ) ) ;
}
bool ScalarConverter::isInt ( const std::string & str )
{ 
	return ( isSign( str.at(0) ) && isDigitSeq( str.substr(1) ) ) || isDigitSeq(str) ;
}

/*
#### isFloat( string str )
Returns true if any of this cases happens
1.- string ends with f and any of this cases:
2.- string length is 4 and string starts with "nan" of "inf"
3.- string lenght is 5 and string starts with a sign and contains "inf"
4.- string starts with sign and the rest of the string is a floating point
5.- string is floating point
 * */
bool ScalarConverter::isFloat ( const std::string & str )
{ 
	if ( str.at( str.size() - 1 ) != 'f' )
	{ return false ; }  // does not end with "f"
						  
	// does emd with f
	size_t len = str.size() ;
	std::string str2 = str.substr(0, len - 1) ;
	if ( (len == 4) && ( !str2.compare("nan") || !str2.compare("inf") ) )
	{ return true ; } // is "nanf" or "inff" 

	if ( (len == 5) && isSign( str2.at(0) ) && !str2.substr(1).compare("inf") )
	{ return true ; } // is +inff or -inff

	if ( isSign( str2.at(0) ) && isFloatPoint(str2.substr(1)) )
	{ return true ; } // <sign> <floating-point> "f"

	return isFloatPoint(str2) ; // <sign> <floating-point> "f"

	

}
/*
  
#### isDouble ( string str )
Returns true if any of this cases happens
1.- string length is 3 and string starts with "nan" of "inf"
2.- string lenght is 4 and string starts with a sign and contains "inf"
3.- string starts with sign and the rest of the string is a floating point
4.- string is floating point
*/

bool ScalarConverter::isDouble ( const std::string & str ) 
{ 
	size_t len = str.size() ;

	if ( (len == 3) && ( !str.compare("nan") || !str.compare("inf") ) )
	{ return true ; } // is "nan" or "inf" 

	if ( (len == 4) && isSign( str.at(0) ) && !str.substr(1).compare("inf") )
	{ return true ; } // is +inf or -inf

	if ( isSign( str.at(0) ) && isFloatPoint(str.substr(1)) )
	{ return true ; } // <sign> <floating-point>

	return isFloatPoint(str) ; // <sign> <floating-point>
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

int  ScalarConverter::str2Int ( const std::string & str, bool & isValid ) 
{
	char * end ;
	errno = 0 ;
	int base = 10 ;
	long r_lon = std::strtol( str.c_str(), &end, base ) ;
	if ( ( errno == ERANGE ) ||
		 ( r_lon < std::numeric_limits<int>::min() ) || 
		 ( std::numeric_limits<int>::max() < r_lon ) ) {
		isValid = false ;
		return 0 ;
	}
	isValid = true;
	return static_cast<int>(r_lon);
}
float  ScalarConverter::str2Flo ( const std::string & str, bool & isValid )
{
	(void)str;
	(void)isValid;
	return 0;
}
double  ScalarConverter::str2Dou ( const std::string & str, bool & isValid )
{
	char * end ;
	errno = 0 ;
	long long r_llon = std::strtod( str.c_str(), &end) ;
	if ( ( errno == ERANGE ) ||
		 ( r_llon < std::numeric_limits<double>::min() ) || 
		 ( std::numeric_limits<double>::max() < r_llon ) )
	{
		isValid = false ;
		return 0 ;
	}
	
	isValid = true;
	return static_cast<double>(r_llon);
}


void ScalarConverter::showChr (const std::string & str ) 
{
	std::cout << str << " Char   :Not implemented yet" << std::endl ;
}
void ScalarConverter::showInt (const std::string & str ) 
{
	bool isValid = false ;
	int r_int = ScalarConverter::str2Int(str, isValid) ;
	if (isValid)
	{
		std::cout << "Int    :" << r_int << std::endl ;
		std::cout << "Float  :" << static_cast<float>(r_int) << std::endl ;
		std::cout << "Double :" << static_cast<double>(r_int) << std::endl ;
	} else {
		std::cout << "Int    :Impossible" << std::endl ;
		double r_dou = ScalarConverter::str2Dou(str, isValid) ;
		if (isValid) 
		{
		std::cout << "Float  :" << static_cast<float>(r_dou) << std::endl ;
		std::cout << "Double :" << r_dou << std::endl ;
		} else {
			std::cout << "Float  :Impossible" << std::endl ;
			std::cout << "Double :Impossible" << std::endl ;
		}
	}

}
void ScalarConverter::showFlo (const std::string & str ) 
{
	(void)str;
		std::cout << "Float  :Not Implemented Yet" << std::endl ;
}
void ScalarConverter::showDou (const std::string & str ) 
{
	(void)str;
		std::cout << "Double :Not implemented yet" << std::endl ;
}
