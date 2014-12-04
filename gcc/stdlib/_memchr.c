/*====================================================================*
 *
 *   void * _memchr (void * memory, const int c, unsigned long count)
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

void * _memchr (register void * memory, register const int c, register unsigned long count)

{
	if (memory) while (count--)
	{
		if (* (char *) (memory) == c)
		{
			break;
		}
		(char *) (memory) ++;
	}
	return (memory);
}
