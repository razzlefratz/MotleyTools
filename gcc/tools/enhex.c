/*====================================================================*
 *
 *   size_t enhex (char buffer [], size_t length, void const * memory, size_t extent);
 *
 *   memory.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ENHEX_SOURCE
#define ENHEX_SOURCE

#include <stdint.h>

#include "../tools/memory.h"
#include "../tools/number.h"
#include "../tools/types.h"

size_t enhex (char buffer [], size_t length, void const * memory, size_t extent) 

{
	register char * string = (char *)(buffer);
	register byte * offset = (byte *)(memory);
	length >>= 1;
	while ((length--) && (extent--)) 
	{
		*string++ = DIGITS_HEX [(*offset >> 4) & 0x0F];
		*string++ = DIGITS_HEX [(*offset >> 0) & 0x0F];
		offset++;
	}
	return (string - buffer);
}


#endif

