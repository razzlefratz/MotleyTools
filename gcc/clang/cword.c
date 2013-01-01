/*====================================================================*
 *
 *   cword.c 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CWORD_SOURCE
#define CWORD_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../clang/cword.h"

/*====================================================================*
 *   reserved word string vector;
 *--------------------------------------------------------------------*/

char const * sv_cword [CWORD_O_NULL+1] = 

{
	"auto",
	"bool",
	"break",
	"case",
	"char",
	"const",
	"continue",
	"default",
	"do",
	"double",
	"else",
	"entry",
	"enum",
	"extern",
	"float",
	"for",
	"goto",
	"if",
	"int",
	"long",
	"register",
	"return",
	"short",
	"signed",
	"sizeof",
	"static",
	"struct",
	"switch",
	"typedef",
	"union",
	"unsigned",
	"void",
	"volatile",
	"while",
	(char const *)(0)
};


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

