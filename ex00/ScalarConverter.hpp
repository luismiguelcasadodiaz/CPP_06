#ifndef SCALARCONVERTER_HH
#define SCALARCONVERTER_HH

# define RESET_ss  	"\033[0;39m"
//# define COLOR_ss		"\033[0;90m"             //GRAY
//# define COLOR_ss		"\033[0;91m"             //RED
//# define COLOR_ss		"\033[0;92m"             //GREEN
//# define COLOR_ss		"\033[38;2;75;179;82m"   //GREEN
//# define COLOR_ss		"\033[0;93m"             //YELLOW
# define COLOR_ss		"\033[0;94m"             //BLUE
//# define COLOR_ss		"\033[0;95m"             //MAGENTA
//# define COLOR_ss		"\033[0;96m"             //CYAN
//# define COLOR_ss		"\033[0;97m"             //WHITE
//# define COLOR_ss		"\033[0;99m"             //BLACK
//# define COLOR_ss		"\033[38;5;209m"         //ORANGE
//# define COLOR_ss		"\033[38;2;184;143;29m"  //BROWN
//# define COLOR_ss		"\033[38;5;234m"         //DARK_GRAY
//# define COLOR_ss		"\033[38;5;245m"         //MID_GRAY
//# define COLOR_ss		"\033[38;2;75;179;82m"   //DARK_GREEN
//# define COLOR_ss		"\033[38;5;143m"         //DARK_YELLOW

#include <string>
#include <iostream>

class ScalarConverter
{
	public:
			static void convert(const std::string & s);
	private:
		ScalarConverter( void ) ;
		~ScalarConverter( void ) ;
		ScalarConverter( const ScalarConverter & other ) ;
		ScalarConverter & operator=( const ScalarConverter & other ) ;
};
#endif
