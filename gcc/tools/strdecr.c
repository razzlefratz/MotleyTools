/*====================================================================*
 *
 *   signed strdecr (void * memory, unsigned extent, byte min, byte max);
 *
 *   memory.h
 *
 *   decrement a multi-byte memory region; start at max and reset at
 *   min; return -1 if all bytes are min;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRDECR_SOURCE
#define STRDECR_SOURCE

#include "../tools/memory.h"

signed strdecr (void * memory, register unsigned extent, register byte min, register byte max) 

{
	register byte * offset = (byte *)(memory);
	while (extent--) 
	{
		if (-- offset [extent] >= min) 
		{
			return (0);
		}
		offset [extent] = max;
	}
	return (-1);
}


#endif

