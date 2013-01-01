/*====================================================================*
 *
 *   void *_memcpy(void *target, void const *source, size_t count);
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

void *_memcpy (register char *target, register char const *source, register size_t count) 

{
	if (target) if (source) 
	{
		register size_t index;
		for (index = 0; index < count; index++) 
		{
			target [index] = source [index];
		}
	}
	return ((void *)(target));
}

