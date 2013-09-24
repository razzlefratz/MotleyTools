/*====================================================================*
 *
 *   void memcopy (void * target, void const * source, size_t extent);
 *   
 *   memory.h
 *
 *   copy the contents of one memory region to another in native byte
 *   order; this function is the counterpart to function memfold(); 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

#ifndef MEMCOPY_SOURCE
#define MEMCOPY_SOURCE

#include "../tools/memory.h"

void memcopy(void * target, void const * source, size_t extent)

{
	byte * byte1 = (byte *) (target);
	byte * byte2 = (byte *) (source);
	while (extent--)
	{
		* byte1++ = * byte2++;
	}
	return;
}

#endif



