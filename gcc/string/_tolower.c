/*====================================================================*
 *
 *   int _tolower(int c);
 *
 *   _ctype.h
 *
 *   return the lower case equivalent of a character;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../string/_ctype.h"

int _tolower (int c) 

{
	return ((c < 'A') || (c > 'Z')? (c): (c)+('a'-'A'));
}

