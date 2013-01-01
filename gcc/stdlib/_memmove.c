/*====================================================================*
 *
 *   void *_memmove(void *target, void const *source, size_t count);
 *
 *   _string.h
 *   _memory.h
 *
 *   sequentially move count bytes from the source buffer to the target
 *   buffer, compensating for any buffer overlap; return address of the
 *   target buffer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../stdlib/_memory.h"

void *_memmove (register char *target, register char const *source, register size_t count) 

{
	register size_t index;
	if (target < source) 
	{
		for (index = 0; index < count; index++) target [index] = source [index];
	}
	else if (target > source) 
	{
		for (index = count; index > 0; index--) target [index] = source [index];
	}
	return (target);
}

