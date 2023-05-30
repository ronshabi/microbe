global _fini
global _init


; x86 crti.s
section .init
_init:
	push ebp
	mov ebp, esp
	; gcc will nicely put the contents of crtbegin.o's .init section here.

section .fini
_fini:
	push ebp
	mov ebp, esp
	; gcc will nicely put the contents of crtbegin.o's .fini section here.
