/*====================================================================*
 *
 *   void memfold (void * memory1, void const * memory2, size_t extent);
 *   
 *   memory.h
 *
 *--------------------------------------------------------------------*/

#ifndef MEMFOLD_SOURCE
#define MEMFOLD_SOURCE

#include "../tools/memory.h"

void memfold (void * memory1, void const * memory2, size_t extent) 

{
	byte * byte1 = (byte *)(memory1);
	byte * byte2 = (byte *)(memory2) + extent;
	while (extent--) 
	{
		*byte1++ = *--byte2;
	}
	return;
}

#endif

