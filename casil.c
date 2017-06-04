#include <stdio.h>
#include <stdlib.h>

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

	int n = c;

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
