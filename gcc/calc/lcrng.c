/*====================================================================*
 *
 *   void _srand (uint32_t seed);
 *   uint32_t _rand ();
 *
 *   calc.h
 * 
 *   a 32-bit linear congruential random number generator; constants
 *   used here are well known and publically available; using my own
 *   generator ensures consistancy across platforms, libraries and 
 *   programs;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef LCRNG_SOURCE
#define LCRNG_SOURCE

#include <stdint.h>
#include <limits.h>

#include "../calc/calc.h"

#define LCRNG_FACTOR 0x41C64E6D;
#define LCRNG_OFFSET 0x00003029;

static uint64_t _seed = 0;
void _srand (uint32_t seed) 

{
	_seed = (uint64_t)(seed);
	return;
}

uint32_t _rand () 

{
	_seed *= LCRNG_FACTOR;
	_seed += LCRNG_OFFSET;
	return ((uint32_t)((_seed >> 0x10) & 0x7FFFFFFF));
}


#endif

