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

	if ( isDouble(s) ) {
		showDou(s) ;
	} else if ( isFloat(s) ) {
		showFlo(s) ;
	} else if ( isInt(s) ) {
		showInt(s) ;
	} else if ( isChar(s) ) { 
		showChr(s) ;
	} else {
		std::cout << "No type detected" << std::endl;
	}
	ScalarConverter::showAll( );
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
	return str.size() == 1 && ( isEscSeq( str.at(0) ) || isCharc( str.at(0) ) ) ;
	/*return str.size() == 3 &&
		str.at(0) == '\'' && 
		str.at(2) == '\'' && 
		( isEscSeq( str.at(1) ) || isCharc( str.at(1) ) ) ;
		*/
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
	if (!str.compare("nanf"))
	{
		isValid = true;
		return std::numeric_limits<float>::quiet_NaN();
	}
	if (!str.compare("inff") || !str.compare("+inff"))
	{
		isValid = true;
		return std::numeric_limits<float>::infinity();
	}
	if (!str.compare("-inff"))
	{
		isValid = true;
		return -std::numeric_limits<float>::infinity();
	}
	char * end ;
	errno = 0 ;
	double r_dou = std::strtod( str.c_str(), &end) ;
	double r_dou_abs = std::fabs(r_dou) ;
	if ( ( errno == ERANGE ) ||
		 ( (r_dou_abs != 0) &&
		   ( ( r_dou_abs < std::numeric_limits<float>::min() ) || 
		     ( std::numeric_limits<float>::max() < r_dou_abs )
		   )
		 )
		)
	{
		isValid = false ;
		return 0 ;
	}
	isValid = true ;
	return static_cast<float>(r_dou) ;	
}
double  ScalarConverter::str2Dou ( const std::string & str, bool & isValid )
{
	if (!str.compare("nan"))
	{
		isValid = true;
		return std::numeric_limits<double>::quiet_NaN();
	}
	if (!str.compare("inf") || !str.compare("+inf"))
	{
		isValid = true;
		return std::numeric_limits<double>::infinity();
	}
	if (!str.compare("-inf"))
	{
		isValid = true;
		return -std::numeric_limits<double>::infinity();
	}
		char * end ;
	errno = 0 ;
	long double r_llon = std::strtod( str.c_str(), &end) ;
	if ( ( errno == ERANGE ) ||
		 ( (0 < r_llon) && (r_llon < std::numeric_limits<double>::min() ) ) || 
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
	unsigned char r_uchar = static_cast<unsigned char>(*str.c_str());
	if ((32 <= r_uchar) && (r_uchar <= 126) )
	{
		std::stringstream ss_char ;
		ss_char << "'" << str.c_str() << "'" ;
		ScalarConverter::charstr = ss_char.str() ;
	} else {
		ScalarConverter::charstr = "Non displayable" ;
	}
	std::stringstream ss_int ;
	std::stringstream ss_flt ;
	std::stringstream ss_dbl ;
	ss_int << static_cast<int>(r_uchar);
	ScalarConverter::intstr = ss_int.str();
	ss_flt << std::fixed << std::setprecision(1) << static_cast<float>(r_uchar) << "f" ;
	ScalarConverter::floatstr = ss_flt.str() ;
	ss_dbl << std::fixed << std::setprecision(1) << static_cast<double>(r_uchar) ;
	ScalarConverter::doublestr = ss_dbl.str() ;


}
void ScalarConverter::showInt (const std::string & str ) 
{
	bool isValid = false ;
	int r_int = ScalarConverter::str2Int(str, isValid) ;
	if (isValid)
	{
		if ((32 <= r_int) && (r_int < 256) )
		{
			std::stringstream ss_char ;
			ss_char << "'" <<static_cast<unsigned char>(r_int) << "'" ;
			ScalarConverter::charstr = ss_char.str() ;
		} else {
			ScalarConverter::charstr = "Non displayable" ;
		}
		std::stringstream ss_int ;
		std::stringstream ss_flt ;
		std::stringstream ss_dbl ;
		ss_int << r_int;
		ScalarConverter::intstr = ss_int.str();
		ss_flt << static_cast<float>(r_int) ;
		ScalarConverter::floatstr = ss_flt.str() ;
		ss_dbl << static_cast<double>(r_int) ;
		ScalarConverter::doublestr = ss_dbl.str() ;
	} else {
		double r_dou = ScalarConverter::str2Dou(str, isValid) ;
		if (isValid) 
		{
			std::stringstream ss_flt ;
			std::stringstream ss_dbl ;
			ss_flt << static_cast<float>(r_dou) << "f" ;
			ScalarConverter::floatstr = ss_flt.str() ;
			ss_dbl << r_dou ;
			ScalarConverter::doublestr  = ss_dbl.str() ;
		}
	}

}
void ScalarConverter::showFlo (const std::string & str ) 
{
	bool isValid = false;
	float r_flt = ScalarConverter::str2Flo(str, isValid) ;
	if (isValid)
	{
		if ((32 <= r_flt) && (r_flt < 256) )
		{
			std::stringstream ss_char ;
			ss_char << "'" << static_cast<unsigned char>(r_flt) << "'" ;
			ScalarConverter::charstr = ss_char.str() ;
		} else {
			ScalarConverter::charstr = "Non displayable" ;
		}
		std::stringstream ss_flt ; 
		ss_flt  << std::fixed <<std::setprecision(1) << r_flt << "f" ;
		ScalarConverter::floatstr = ss_flt.str() ;
		double r_dou = static_cast<double>(r_flt) ;
		std::stringstream ss_dbl ;
		ss_dbl << std::fixed << std::setprecision(1) << r_dou ;
		ScalarConverter::doublestr = ss_dbl.str() ;
		// does this float fits in a int?
		if ( ( (std::numeric_limits<int>::min() <= r_flt) && 
			   (r_flt <= std::numeric_limits<int>::max())
			 )
		   )
		{
			std::stringstream ss_int ;
			ss_int << static_cast<int>(r_flt);
			ScalarConverter::intstr = ss_int.str() ;
		}
		
	}

}
void ScalarConverter::showDou (const std::string & str ) 
{
	bool isValid = false ;
	double r_dou = ScalarConverter::str2Dou(str, isValid) ;
	if (isValid)
	{

		if ((32 <= r_dou) && (r_dou < 256) )
		{
			std::stringstream ss_char ;
			ss_char << "'" << static_cast<unsigned char>(r_dou) <<"'" ;
			ScalarConverter::charstr = ss_char.str() ;
		} else {
			ScalarConverter::charstr = "Non displayable" ;
		}
		std::stringstream ss_dbl ;
		ss_dbl << static_cast<double>(r_dou) ;
		ScalarConverter::doublestr = ss_dbl.str() ;
		double dou_abs = std::fabs(r_dou) ;
		// does this double fits in a float?
		std::stringstream ss_flt ;
		if ( (dou_abs == 0) || 
			 ( (std::numeric_limits<float>::min() <= dou_abs) && 
			   (dou_abs <= std::numeric_limits<float>::max())
			 )
		   )
		{
			ss_flt  << std::fixed << std::setprecision(1) << static_cast<float>(r_dou) << "f";
			ScalarConverter::floatstr = ss_flt.str() ;
		} else if ( std::isnan(r_dou) )
		{
			ss_flt << std::numeric_limits<float>::quiet_NaN() << "f" ;
			ScalarConverter::floatstr = ss_flt.str();

		} else if ( r_dou == std::numeric_limits<double>::infinity() )
		{
			ss_flt << std::numeric_limits<float>::infinity() << "f" ;
			ScalarConverter::floatstr = ss_flt.str();
		} else if ( r_dou == -std::numeric_limits<double>::infinity() )
		{
			ss_flt << -std::numeric_limits<float>::infinity() << "f" ;
			ScalarConverter::floatstr = ss_flt.str();
		}

		// does this double fits in a int?
		if ( ( dou_abs == 0 ) || 
			 ( (std::numeric_limits<int>::min() <= dou_abs) && 
			   (dou_abs <= std::numeric_limits<int>::max())
			 )
		   )
		{
			std::stringstream ss_int ;
			ss_int << static_cast<int>(r_dou);
			ScalarConverter::intstr = ss_int.str() ;
		}
		
	}
}


std::string ScalarConverter::charstr = "Impossible"; 
std::string ScalarConverter::intstr = "Impossible";
std::string ScalarConverter::floatstr = "Impossible";
std::string ScalarConverter::doublestr = "Impossible";

void ScalarConverter::showAll()
{
    std::cout << "char  : " << charstr << std::endl;
    std::cout << "int   : " << intstr << std::endl;
    std::cout << "float : " << floatstr << std::endl;
    std::cout << "double: " << doublestr << std::endl;
}
