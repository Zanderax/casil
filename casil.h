#include <stdio.h>
#include <stdlib.h>

/*#include "errorHandling.h"*/

#define FILE_NAME_SIZE 10

typedef enum SYMBOLS { 
	PLUS = '+',
	MINUS = '-',
	MULTIPLY = '*',
	NEW_LINE = 10,
} SYMBOLS;

long int readSourceFromFile( char* fileName, char** source );
/*int isNumber( char c );*/
/*int toNum( char c );*/
