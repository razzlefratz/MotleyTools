/*====================================================================*
 *
 *   signed memdecr (void * memory, unsigned extent);
 *
 *   memory.h
 *
 *   decrement a multi-byte memory region; start at 0xff and reset 
 *   at 0x00; return -1 once all bytes are 0x00; reset all bytes to
 *   0xff on next decrement;
 *
 *   for example:
 *
 *      0x00 0x00 0x00 --> 0x00 0x00 0x01
 *      0xFF 0x00 0xFF --> 0xFF 0x01 0x00
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MEMDECR_SOURCE
#define MEMDECR_SOURCE

#include "../tools/memory.h"

signed memdecr (void * memory, register unsigned extent) 

{
	register byte * offset = (byte *)(memory);
	while (extent--) 
	{
		if (-- offset [extent] != 0xFF) 
		{
			return (0);
		}
	}
	return (-1);
}


#endif

