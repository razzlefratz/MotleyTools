/*====================================================================*
 *
 *   void hexpeek (const void * memory, size_t origin, size_t offset, size_t extent, size_t window, FILE * fp);
 *
 *   memory.h
 *
 *   display a partial hexadecimal dump on stdout that displays the
 *   memory region from origin upto offset centered within a window
 *   that preceeds and follows the region;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdint.h>

#include "../tools/memory.h"

void hexpeek(const void * memory, size_t origin, size_t offset, size_t extent, size_t window, FILE * fp)

{
	if (offset == origin)
	{
		offset++;
	}
	hexdump (memory, window < origin? origin - window: 0, offset +  window < extent? offset +  window: extent, fp);
	return;
}

