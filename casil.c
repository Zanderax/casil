#include <stdio.h>

char start[] = ".text\n\t.global _start\n\n_start:\n";
char move1[] = "movl    $";
char move11[] =", %ebx\n";
char move2[] = "movl    $1, %eax\n";
char intrp[] = "int     $0x80\n";

int main( void )
{
	
	FILE *fp;
	fp = fopen( "source", "r" );

	if(!fp)
	{
		return -1;
	}

	char c = fgetc( fp );

	fclose( fp );

	fp = fopen( "exe.out", "w" );

	fwrite( start, 31, sizeof( char ), fp);
	fwrite( move1, 9, sizeof( char ), fp);
	fputc( c, fp);
	fwrite( move11, 7, sizeof( char ), fp);
	fwrite( move2, 17, sizeof( char ), fp);
	fwrite( intrp, 14, sizeof( char ), fp);
	 
	fclose( fp );
	
	return 0;
}