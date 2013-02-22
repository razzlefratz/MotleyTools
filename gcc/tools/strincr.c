/*====================================================================*
 *
 *   signed strincr (void * memory, size_t extent, byte min, byte max);
 *
 *   memory.h
 *
 *   increment a multi-byte memory region; start at min and reset at
 *   max; return -1 if all bytes are max;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRINCR_SOURCE
#define STRINCR_SOURCE

#include "../tools/memory.h"

signed strincr (void * memory, register size_t extent, register byte min, register byte max) 

{
	register byte * offset = (byte *)(memory);
	while (extent--) 
	{
		if (++ offset [extent] <= max) 
		{
			return (0);
		}
		offset [extent] = min;
	}
	return (-1);
}


#endif

