/*====================================================================*
 *
 *   void memout (void const  * memory, size_t extent, char const * format, unsigned group, char c, FILE *fp) 
 *
 *   memory.h
 *
 *   print memory as a series of octets formatted by format string fmt,
 *   seperated by character c every mod prints;
 *
 *   for example, memout (memory, IPv4_LEN, "%d", 1, '.', stdout) would print:
 *
 *      192.168.1.1
 *
 *   another example, memout (memory, IPv6_LEN, "%02x", 2, ':', stdout) would print:
 *
 *     0032:0045:0000:0000:0000:0000:1123:4456 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MEMOUT_SOURCE
#define MEMOUT_SOURCE

#include <stdio.h>

#include "../tools/memory.h"

void memout (void const * memory, size_t extent, char const * format, unsigned group, signed c, FILE *fp) 

{
	byte * origin = (byte *) (memory);
	byte * offset = (byte *) (memory);
	while (extent--) 
	{
		fprintf (fp, format, * offset++);
		if ((extent) && !((offset - origin) % group)) 
		{
			putc (c, fp);
		}
	}
	return;
}


#endif

