/*====================================================================*
 *
 *   char * hexstring (char buffer [], size_t length, const byte memory [], size_t extent);
 *
 *   memory.h
 *
 *   decode a memory region into a hexadecimal character buffer and 
 *   return the buffer address;
 *
 *   allow three string characters for each memory byte; this means
 *   that the buffer must hold at least three characters or nothing
 *   will be decoded; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef HEXSTRING_SOURCE
#define HEXSTRING_SOURCE

#include <stdint.h>

#include "../tools/memory.h"

char * hexstring(char buffer[], size_t length, const byte memory[], size_t extent)

{
	hexdecode (memory, extent, buffer, length);
	return (buffer);
}

#endif



