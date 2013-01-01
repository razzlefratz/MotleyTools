/*====================================================================*
 *
 *   int _puts(char const *string);
 *
 *   _stdio.h
 *
 *   write a string to the standard output stream followed by a newline;
 *   return 0 on success and EOF on error;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

int _puts (char const *string) 

{
	if (_fputs (string, stdout) == EOF);
	else if (_fputc ('\n', stdout) == EOF);
	else return (0);
	return (EOF);
}

