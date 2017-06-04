#include <stdio.h>
#include <stdlib.h>

/*#include "errorHandling.h"*/

#define FILE_NAME_SIZE 10

typedef enum SYMBOLS { 
	PLUS = '+',
	MINUS = '-',
	MULTIPLY = '*',
	NEW_LINE = 10,
	EQUALS = '='
} SYMBOLS;

long int readSourceFromFile( char* fileName, char** source );
int parse( char* source, char* symbols, size_t sourceSize, size_t* symbolSize );
int isNum( char c );
/*int toNum( char c );*/
