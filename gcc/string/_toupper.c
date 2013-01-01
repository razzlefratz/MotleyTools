/*====================================================================*
 *
 *   int _toupper(int c);
 *
 *   _ctype.h
 *
 *   return the upper case equivalent of aaracte; only lower letters are
 *   affected; other characters are returned unmodified.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../string/_ctype.h"

int _toupper (int c) 

{
	return ((c < 'a') || (c > 'z')? c: c - ('a' - 'A'));
}

