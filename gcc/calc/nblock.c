/*====================================================================*
 *
 *   int nblock(int count, int block);
 *
 *   calc.h
 *
 *   compute the number of blocks, of a specified size, that are needed to
 *   hold count items; in other words, the smallest positive integer value
 *   n such that count <= n * block where 'block' is the 'blocking factor';
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef NBLOCK_SOURCE
#define NBLOCK_SOURCE

#include "../calc/calc.h"

int nblock (register int count, register int block) 

{
	return (((count > 0) && (block > 0))? ((count + block - 1) / block): (0));
}


#endif

