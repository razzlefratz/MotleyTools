/*====================================================================*
 *
 *   char *_memchr(char const *buffer, const int c, size_t count)
 *
 *   _string.h
 *   _memory.h
 *
 *   search the first count character positions of a buffer for character
 *   c; return the character address if present or NULL if missing;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../stdlib/_memory.h"

char *_memchr (register char *buffer, register const int c, register size_t count) 

{
	if (buffer) while ((count-- > 0) && (*buffer != c)) buffer++;
	return (buffer);
}

