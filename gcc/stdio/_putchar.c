/*====================================================================*
 *
 *   int _putchar(c);
 *
 *   _stdio.h
 *
 *   write one character straight to STDOUT, bypassing any other buffered
 *   data; return the character value on success or EOF on failure;
 *
 *   _putchar() is also defined as a macro in _stdio.h;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

int _putchar (int c) 

{
	return ((write (STDOUT, &c, sizeof (char)))? (unsigned)(c): EOF);
}

