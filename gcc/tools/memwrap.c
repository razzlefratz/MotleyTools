/*====================================================================*
 *
 *   void memwrap (void * memory, size_t extent, ssize_t offset);
 *
 *   memory.h 
 *
 *   Rotate (cycle) bytes within a memory region left or right by a given
 *   offset and return the region address. Positive offsets rotate right.
 *   Negative offsets rotate left. Offsets can exceed region extent.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MEMWRAP_SOURCE
#define MEMWRAP_SOURCE

#include <string.h>

#include "../tools/memory.h"

void memwrap (void * memory, size_t extent, ssize_t offset) 

{
	byte * buffer = (byte *)(memory);
	size_t start = 0;
	size_t moved = 0;
	if ((offset %= extent) < 0) 
	{
		offset += extent;
	}
	while (moved < extent) 
	{
		size_t store = start;
		size_t fetch = start;
		byte temp = buffer [fetch];
		fetch += offset;
		fetch %= extent;
		while (fetch != start) 
		{
			buffer [store] = buffer [fetch];
			store = fetch;
			fetch += offset;
			fetch %= extent;
			moved++;
		}
		buffer [store] = temp;
		moved++;
		start++;
	}
	return;
}


/*====================================================================*
 *   demo/test program;
 *--------------------------------------------------------------------*/

#if 0

void dump (byte memory [], size_t extent) 

{
	size_t offset = 0;
	while (offset < extent) 
	{
		printf (" %02d", memory [offset++]);
	}
	printf ("\n");
	return;
}

int main (signed argc, char const * atgv []) 

{
	byte memory [] = 
	{
		0,
		1,
		2,
		3,
		4,
		5,
		6,
		7,
		8,
		9
	};
	dump (memory, sizeof (memory));
	memwrap (memory, sizeof (memory), 5);
	dump (memory, sizeof (memory));
	memwrap (memory, sizeof (memory), -3);
	dump (memory, sizeof (memory));
	return (0);
}


#endif

#endif

