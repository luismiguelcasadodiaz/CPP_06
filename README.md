# CPP_06
C++ cast practice

## Description

A class has a class's member named convert with a string as argument. 

The member analyses the string to identify which data type it represents.

Once identified cast the string to the right type and prints its value




### Parser definition

Here's the BNF syntax for C++98 literals that you need to parse:

###CHAR
bnf<char-literal> ::= "'" <c-char> "'"
<c-char>       ::= <any printable ASCII character except ' and \>
                 | <escape-sequence>
<escape-sequence> ::= "\n" | "\t" | "\r" | "\\" | "\'" | "\""

Examples: 'a', 'Z', '0', '\n', '\t'
i
###INT
bnf<int-literal> ::= <sign>? <digit-sequence>
<sign>        ::= "+" | "-"
<digit-sequence> ::= <digit>+
<digit>       ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
Examples: 0, 42, -42, +42, 2147483647

###FLOAT
bnf<float-literal> ::= <sign>? <floating-point> "f"
                  | <sign>? "inf" "f"
                  | "nan" "f"
<floating-point> ::= <digit-sequence> "." <digit-sequence>?
                   | <digit-sequence>? "." <digit-sequence>
                   | <digit-sequence>
Examples: 0.0f, 42.0f, -4.2f, .5f, 42.f, +inff, -inff, nanf

###DOUBLE
bnf<double-literal> ::= <sign>? <floating-point>
                   | <sign>? "inf"
                   | "nan"
<floating-point> ::= <digit-sequence> "." <digit-sequence>?
                   | <digit-sequence>? "." <digit-sequence>
