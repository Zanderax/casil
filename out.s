.text
	.global _start

_start:
	# Initalize the program counter to 1
    movl    $0, %ebx
    movl    $1, %eax
    int     $0x80
