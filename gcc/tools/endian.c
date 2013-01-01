/*====================================================================*
 *
 *   void endian (void * memory, unsigned extent);
 *
 *   memory.h
 *
 *   reverse the order of bytes within a multi-byte memory region; 
 *   return no value;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ENDIAN_SOURCE
#define ENDIAN_SOURCE

#include "../tools/memory.h"

void endian (void * memory, unsigned extent) 

{
	register byte * first = (byte *)(memory);
	register byte * final = first + extent;
	while (first < final) 
	{
		register byte byte = *first;
		*first++ = *--final;
		*final = byte;
	}
	return;
}


#endif

