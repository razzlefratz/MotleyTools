/*====================================================================*
 *
 *   void IPAout (uint8_t memory [], size_t length, unsigned c, FILE *fp);
 *
 *   convert.h
 *
 *   print memory as a series of binary octets seperated by spaces;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef IPAOUT_SOURCE
#define IPAOUT_SOURCE

#include <stdio.h>
#include <limits.h>
#include <stdint.h>

#include "../tools/number.h"

void IPAout (const uint8_t memory [], size_t length, unsigned c, FILE *fp) 

{
	while (length-- > 0) 
	{
		printd (*memory, fp);
		if (length > 0) 
		{
			putc (DEC_EXTENDER, fp);
			memory++;
		}
	}
	putc (c, fp);
	return;
}


#endif

