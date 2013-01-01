/*====================================================================*
 *
 *   int _getchar(void);
 *
 *   _stdio.h
 *
 *   read one character straight from STDIN, bypassing any other buffered
 *   data; return the character value on success or EOF on failure;
 *
 *   _getchar() is also defineid as a macro in _stdio.h;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

int _getchar (void) 

{
	char c;
	return ((read (STDIN, &c, sizeof (char)) > 0)? (unsigned)(c): EOF);
}

