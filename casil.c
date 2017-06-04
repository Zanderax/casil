#include <stdio.h>
#include <stdlib.h>
#include "casil.h"

char start[] = ".text\n\t.global _start\n\n_start:\n";
char move1[] = "movl    $";
char move11[] =", %ebx\n";
char move2[] = "movl    $1, %eax\n";
char intrp[] = "int     $0x80\n";

int main( void )
{

	char* fileName = calloc( FILE_NAME_SIZE, sizeof( char ) );
	fileName =	"source.cas";
	char *source, *symbols;
	
	size_t sourceSize = readSourceFromFile( fileName, &source );
	size_t symbolSize = 0;

	int i;
	for( i = 0; i < sourceSize; ++i)
	{
		printf("%d ", source[i]);
	}
	printf("\n");

	symbols = calloc( sourceSize, sizeof( char ) );
 
	int error = parse( source, symbols, sourceSize, &symbolSize );

	if (error)
	{
		printf("Error Code = %d\n", error );
		return error;
	}
	
	for( i = 0; i < symbolSize; ++i)
	{
		printf("%d ", symbols[i]);
	}
	printf("\n");
	
	char c = source[0];
	int n = c;

	FILE *fp;

	fp = fopen( "exe.out", "w" );

	fwrite( start, 31, sizeof( char ), fp);
	fwrite( move1, 9, sizeof( char ), fp);
	fprintf( fp, "%d", n );
	fwrite( move11, 7, sizeof( char ), fp);
	fwrite( move2, 17, sizeof( char ), fp);
	fwrite( intrp, 14, sizeof( char ), fp);
	 
	fclose( fp );

	system("as exe.out -o out.o --32");
	system("ld -m elf_i386 -s -o out out.o");
	
	return 0;
}


long int readSourceFromFile( char* fileName, char** source )
{
	FILE *fp;

	fp = fopen( fileName, "r");

	if( !fp )
		return 1;

	fseek( fp, 0L, SEEK_END );
	long int size = ftell( fp );
	rewind( fp );

	*source = malloc( sizeof( char ) * size );
	int i = 0;
	while( ( (*source)[i++] = fgetc( fp ) ) != EOF );
	return size;
}

int parse( char* source, char* symbols, size_t sourceSize, size_t *symbolSize )
{
	int i, symbolCount = 0;
	for( i = 0; i < sourceSize; ++i )
	{
		switch( source[i] )
		{
			case EQUALS:
				if( !isNum(source[i+1]) )
				{
					return -1;
				}
				symbols[symbolCount++] = EQUALS;
				break;
			case NEW_LINE:
				break;
			default:
				if( isNum(source[i]) )
				{
					symbols[symbolCount++] = source[i];
				}
				else
				{
					return source[i];
				}
		}
	}
	*symbolSize = symbolCount;
	return 0;
} 

int isNum( char c )
{
	return !( c < 48 || c > 57 );
}
