/*====================================================================*
 *
 *   char *_strdup(char const *sp);
 *
 *   _string.h
 *
 *   store a string in a safe place by allocating a block of memory and
 *   copying the string to that block; return the block address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../string/_string.h"
#include "../stdlib/_stdlib.h"

char *_strdup (register char const *string) 

{
	register char const *sp = string;
	if (string) 
	{
		while (*sp) sp++;
		sp = (char const *)(_strcpy ((char *)(_malloc ((size_t)(sp-string))), string));
	}
	return ((char *)(sp));
}

