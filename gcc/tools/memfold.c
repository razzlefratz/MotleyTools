/*====================================================================*
 *
 *   void memfold (void * target, void const * source, size_t extent);
 *   
 *   memory.h
 *
 *   copy the contents of one memory region to another in reverse byte
 *   order; this function is the counterpart to function memcopy() and
 *   can be used to copy an integer in one endian format to another;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

#ifndef MEMFOLD_SOURCE
#define MEMFOLD_SOURCE

#include "../tools/memory.h"

void memfold (void * target, void const * source, size_t extent) 

{
	byte * byte1 = (byte *)(target);
	byte * byte2 = (byte *)(source) + extent;
	while (extent--) 
	{
		*byte1++ = *--byte2;
	}
	return;
}

#endif

