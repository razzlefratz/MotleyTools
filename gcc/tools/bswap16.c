/*====================================================================*
 * 
 *   uint16_t bswap16(uint16_t x);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdint.h>

#include "../tools/endian.h"

uint16_t bswap16 (uint16_t x) 

{
	return ((x >> 8) | (x << 8));
}

