/*====================================================================*
 *
 *   void *_memset(char *buffer, const int c, size_t count);
 *
 *   _string.h
 *   _memory.h
 *
 *   place character c in the first count character positions of a buffer
 *   and return the buffer address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../stdlib/_memory.h"

void *_memset (register char *buffer, register const int c, size_t count) 

{
	if (buffer) while (count > 0) buffer [count--] = (unsigned char)(c);
	return (buffer);
}

