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

	char* fileName = malloc( sizeof( char ) * FILE_NAME_SIZE );
	fileName =	"source.cas";
	char *source;
	
	long int size = readSourceFromFile( fileName, &source );

	char c = source[1];
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
