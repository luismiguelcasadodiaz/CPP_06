# CPP_06
C++ cast practice

## Description

A class has a class's member named convert with a string as argument. 

The member analyses the string to identify which data type it represents. 
I do that with the support of BNF syntax.

Once identified the type, calculate numeric values with strtol() and strtod()
and control MIN/MAX limits to detect overflows.






### Parser definition

Here's the BNF syntax for C++98 literals that you need to parse:

### CHAR
```bnf
bnf<char-literal> ::= "'" <c-char> "'"
<c-char>       ::= <any printable ASCII character except ' and \>
                 | <escape-sequence>
<escape-sequence> ::= "\n" | "\t" | "\r" | "\\" | "\'" | "\""

Examples: 'a', 'Z', '0', '\n', '\t'

```


### INT
```bnf
bnf<int-literal> ::= <sign>? <digit-sequence>
<sign>        ::= "+" | "-"
<digit-sequence> ::= <digit>+
<digit>       ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
Examples: 0, 42, -42, +42, 2147483647
```


### FLOAT
```bnf
bnf<float-literal> ::= <sign>? <floating-point> "f"
                  | <sign>? "inf" "f"
                  | "nan" "f"
<floating-point> ::= <digit-sequence> "." <digit-sequence>?
                   | <digit-sequence>? "." <digit-sequence>
                   | <digit-sequence>
Examples: 0.0f, 42.0f, -4.2f, .5f, 42.f, +inff, -inff, nanf
```
### DOUBLE

```bnf
bnf<double-literal> ::= <sign>? <floating-point>
                   | <sign>? "inf"
                   | "nan"
<floating-point> ::= <digit-sequence> "." <digit-sequence>?
                   | <digit-sequence>? "." <digit-sequence>
Note: According to the exercise, integer notation without a decimal point is NOT valid for doubles in this context (only decimal notation).
Examples: 0.0, 42.0, -4.2, .5, 42., +inf, -inf, nan                   
```


#### Required function in the parser

##### isCharC ( char )

this includes all characters with ASCII codes from 32 (space) through 126 (tilde ~) but 39 and 92.

```bnf
<c-char>::= <any printable ASCII character except ' and \>
```

##### isEscSeq ( char c)

|Escape Sequence|ASCII Character|Decimal Code|Description|
|----------------|-----------------|-------------|-------------|
|\n	|Line Feed (LF)	|10|	Moves to the next line.|
|\t	|Horizontal Tab (HT)	|9|	Moves to the next tab stop.|
|\r	|Carriage Return (CR)	|13|	Moves to the beginning of the line.|
|\\	|Backslash (\)	|92|	A literal backslash.|
|\'	|Single Quote (′)	|39|	A literal single quote.|
|\"	|Double Quote (")	|34|	A literal double quote.|

```bnf
<escape-sequence> ::= "\n" | "\t" | "\r" | "\\" | "\'" | "\""
```

##### isDigit( char c )
```bnf
<digit>       ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
```
##### isSign( char c )
```bnf
<sign>        ::= "+" | "-"
```
##### isDigitSeq( string str )
```bnf
<digit-sequence> ::= <digit>+
```

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
##### isChar (string str)
Returns true if length is 3 and first and last are `'` and the one in the midel is either printable or escape secuence


##### isInt( string str)

Returns true if the first char is sign and the rest of the string is a digit 
sequence or if all string is a digit secuence
```bnf
bnf<int-literal> ::= <sign>? <digit-sequence>
```

#### isFloat( string str )
Returns true if any of this cases happens
1.- string ends with f and any of this cases:
2.- string length is 4 and string starts with "nan" of "inf"
3.- string lenght is 5 and string starts with a sign and contains "inf"
4.- string starts with sign and the rest of the string is a floating point
5.- string is floating point

```bnf
bnf<float-literal> ::= <sign>? <floating-point> "f"
                  | <sign>? "inf" "f"
                  | "nan" "f"
```

#### isDouble ( string str )
Returns true if any of this cases happens
1.- string length is 3 and string starts with "nan" of "inf"
2.- string lenght is 4 and string starts with a sign and contains "inf"
3.- string starts with sign and the rest of the string is a floating point
4.- string is floating point

```bnf
bnf<double-literal> ::= <sign>? <floating-point>
                   | <sign>? "inf"
                   | "nan"
```

#### Quick reference table:

|Symbol|Meaning|Occurrences|Example|
|------|-------|-----------|-------|
|`\|`|OR|Exactly 1 choice|`"+" \| "-"` → + or -|
|?|Optional|0 or 1|<sign>? → can be empty or one sign|
|+|One or more|1 or more|<digit>+ → 5 or 42 or 123|
|*|Zero or more|0 or more|<digit>* → empty or 5 or 42|



# what i read
(floats versus doubles)[https://www.freecodecamp.org/espanol/news/double-vs-float-en-c-la-diferencia-entre-floats-y-doubles/]