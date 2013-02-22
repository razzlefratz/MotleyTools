/*====================================================================*
 *
 *   void memcopy (void * target, void const * source, size_t extent);
 *   
 *   memory.h
 *
 *--------------------------------------------------------------------*/

#ifndef MEMCOPY_SOURCE
#define MEMCOPY_SOURCE

#include "../tools/memory.h"

void memcopy (void * target, void const * source, size_t extent) 

{
	byte * byte1 = (byte *)(target);
	byte * byte2 = (byte *)(source);
	while (extent--) 
	{
		*byte1++ = *byte2++;
	}
	return;
}

#endif

