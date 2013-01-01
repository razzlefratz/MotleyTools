/*====================================================================*
 *
 *   uint32_t bswap32 (uint32_t x);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdint.h>

#include "../tools/endian.h"

uint32_t bswap32 (uint32_t x) 

{
	return (((x << 24) & 0xFF000000) | ((x << 8) & 0x00FF0000) | ((x >> 8) & 0x0000FF00) | ((x >> 24) & 0x000000FF));
}

