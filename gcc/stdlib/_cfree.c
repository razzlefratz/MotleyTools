/*====================================================================*
 *
 *   int _cfree(void *memory);
 *
 *   release a memory region allocated by _malloc() or _calloc(); do not
 *   modify region contents; return NULL;
 *
 *   to maintain consistency with various implementations, use free() with
 *   malloc() and cfree() with calloc();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../stdlib/_malloc.h"

void _cfree (void *buffer) 

{
	_free (buffer);
}

