/*====================================================================*
 *
 *   _alloc.c - memory allocation functions;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../stdlib/_malloc.h"

Pool base = 

{
	0,
	&base
};

Pool *head = &base;

/*====================================================================*
 *
 *   void *_sbrk(size_t nbytes);
 *
 *--------------------------------------------------------------------*/

#ifdef W5F7D1

void *_sbrk (size_t count) 

{
	void *hMemory = (void *)(GlobalAlloc ((0x0040), count));
	return ((hMemory)? (hMemory):(void *)(ERR));
}


#endif

#ifdef STAND_ALONE
#include "_malloc.c"
#include "_calloc.c"
#include "_cfree.c"
#include "_free.c"
#endif

