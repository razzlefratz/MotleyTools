/*====================================================================*
 *
 *   void * _memset (void * memory, const int c, unsigned long extent);
 *
 *   _string.h
 *   _memory.h
 *
 *   place character c in the first count character positions of memory
 *   and return the memory address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../stdlib/_memory.h"

void * _memset (register void * memory, register const int c, unsigned long extent) 

{
	if (memory) while (extent--) ((unsigned char *)(memory)) [extent] = (unsigned char)(c);
	return (memory);
}

