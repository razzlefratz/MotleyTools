/*====================================================================*
 *
 *   void * _memcpy (void * target, const void * source, unsigned long count)
 *
 *   _string.h
 *   _memory.h
 *
 *   sequentially move n bytes from the second buffer to the first
 *   without compensating for possible buffer overlap; return the
 *   address of the first buffer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../stdlib/_memory.h"

void * _memcpy (register void * target, register const void * source, register unsigned long count)

{
	if (target) if (source) while (count--)
	{
		* (char *) (target) ++ = * (char *) (source) ++;
	}
	return (target);
}
