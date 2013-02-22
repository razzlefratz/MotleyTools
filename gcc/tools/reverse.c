/*====================================================================*
 *
 *   void reverse (void * memory, size_t extent);
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

#ifndef REVERSE_SOURCE
#define REVERSE_SOURCE

#include "../tools/memory.h"

void reverse (void * memory, size_t extent) 

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

