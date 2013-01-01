/*====================================================================*
 *
 *   sv_cproc[] -
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stddef.h>

#ifndef CPROC_O_NULL
#define CPROC_O_DEFINE                    0
#define CPROC_O_ELIF                      1
#define CPROC_O_ELSE                      2
#define CPROC_O_ENDIF                     3
#define CPROC_O_ERROR                     4
#define CPROC_O_IF                        5
#define CPROC_O_IFDEF                     6
#define CPROC_O_IFNDEF                    7
#define CPROC_O_INCLUDE                   8
#define CPROC_O_LINE                      9
#define CPROC_O_PRAGMA                   10
#define CPROC_O_UNDEF                    11
#define CPROC_O_NULL                     12
#endif

char const *sv_cproc [CPROC_O_NULL+1] = 

{
	"define",
	"elif",
	"else",
	"endif",
	"error",
	"if",
	"ifdef",
	"ifndef",
	"include",
	"line",
	"pragma",
	"undef",
	(char const *)(0)
};

