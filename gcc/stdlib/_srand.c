/*====================================================================*
 *
 *   void _srand (uint32_t seed);
 *   unsigned _rand (void);
 *
 *   _stdlib.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _SRAND_SOURCE
#define _SRAND_SOURCE

#include <stdint.h>

#include "../stdlib/_stdlib.h"

static uint64_t _seed = 0;
void _srand (uint32_t seed) 

{
	_seed = (uint64_t)(seed);
	return;
}

unsigned _rand (void) 

{
	_seed *= 0x41C64E6D;
	_seed += 0x00003029;
	return ((unsigned)((_seed >> 0x10) & _RAND_MAX));
}


#endif

