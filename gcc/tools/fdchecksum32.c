/*====================================================================*
 *
 *   uint32_t fdchecksum32 (int fd, size_t extent, uint32_t checksum);
 *
 *   memory.h
 *
 *   compute the 16 bit checksum of a file region starting from the
 *   current file position; the checksum is the one's complement of 
 *   the XOR of 16 bit words read from the file;
 *
 *   the region extent is specified in bytes but is truncated to a
 *   multiple of two bytes;
 *
 *   passing a checksum of 0 returns the computed checksum; passing
 *   the computed checksum returns 0 if the checksum is correct;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FDCHECKSUM32_SOURCE
#define FDCHECKSUM32_SOURCE

#include <unistd.h>

#include "../tools/memory.h"
#include "../tools/error.h"

uint32_t fdchecksum32 (int fd, register size_t extent, register uint32_t checksum) 

{
	uint32_t memory;
	while (extent >= sizeof (memory)) 
	{
		if (read (fd, &memory, sizeof (memory)) != sizeof (memory)) 
		{
			error (1, errno, "Can't compute checksum");
		}
		extent -= sizeof (memory);
		checksum ^= memory;
	}
	return (~checksum);
}


#endif

