/*====================================================================*
 *
 *   char *_gets(char *string);
 *
 *   _stdio.h
 *
 *   Read characters from the standard input stream until a newline or EOF
 *   occurs. Replace either with a NUL terminator. Return string address
 *   on success or EOF on error or end-of-file.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

char *_gets (char *string) 

{
	register char *sp = string;
	register signed c;
	if (sp != NULL) 
	{
		while (((c = _getc (stdin)) != EOF) && (c != '\n')) 
		{
			*sp++ = (char)(c);
		}
		*sp = NUL;
	}
	return (((sp > string) || (c != EOF))? string: NULL);
}

