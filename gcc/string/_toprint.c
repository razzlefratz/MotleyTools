/*====================================================================*
 *
 *   int _toprint(int c);
 *
 *   _ctype.h
 *
 *   return the ANSI control code for an ASCII control character; .
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../string/_ctype.h"

int _toprint (int c) 

{
	return ((unsigned)(c)|(0x0040));
}

