/*====================================================================*
 *
 *   uint16_t checksum16 (void const * memory, size_t extent, uint16_t checksum);
 *
 *   memory.h
 *
 *   compute the 16-bit checksum of a memory region; the calculated
 *   checksum is the one's complement of the XOR of 16-bit words in
 *   that region; this means that extent should be an even multiple 
 *   of 2-bytes because trailing bytes will be excluded; 
 *
 *   set checksum argument to 0 when the memory region does not 
 *   include the previous checksum value;
 *
 *   set checksum argument to the previous checksum value when the 
 *   memory region includes the previous checksum value; this will
 *   effectively cancel-out the previous checksum value;
 *
 *   Motley Tools by Charles Maier <cmaier@cmassoc.net>;
 *   Copyright 2001-2006 by Charles Maier Associates;
 *   Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#ifndef CHECKSUM16_SOURCE
#define CHECKSUM16_SOURCE

#include <stdint.h>

#include "../tools/memory.h"

uint16_t checksum16(void const * memory, register size_t extent, register uint16_t checksum)

{
	while (extent >= sizeof(checksum))
	{
		checksum ^= * (typeof(checksum) *) (memory);
		memory += sizeof(checksum);
		extent -= sizeof(checksum);
	}
	return (~ checksum);
}

#endif



