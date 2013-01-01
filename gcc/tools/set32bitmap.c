/*====================================================================*
 *
 *   void set32bitmap (uint32_t * map, unsigned bit);
 *
 *   flags.h
 *
 *   set the given bit in a multi-element 32-bit flagword array;
 *   for example, a three element array represents 96 bits and so
 *   we might set bit 75 or bit 10 in element 2; macro _bits () 
 *   is defined in flags.h;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SET32BITMAP_SOURCE
#define SET32BITMAP_SOURCE

#include "../tools/flags.h"
#include "../tools/endian.h"

void set32bitmap (uint32_t * map, unsigned bit) 

{
	map [bit / _bits (* map)] |= HTOLE32 (1 << (bit % _bits (* map)));
	return;
}


#endif

