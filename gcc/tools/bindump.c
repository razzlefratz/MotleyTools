/*====================================================================*
 *
 *   void bindump (void const * memory, size_t offset, size_t extent, FILE *fp);
 *
 *   memory.h
 *
 *   print a binary dump of a memory region; memory is the base
 *   address; offset is the lower bound and extent is the upper 
 *   bound;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef BINDUMP_SOURCE
#define BINDUMP_SOURCE

#include <stdio.h>
#include <ctype.h>
#include <stdint.h>

#include "../tools/memory.h"
#include "../tools/number.h"

void bindump (void const * memory, size_t offset, size_t extent, FILE *fp) 

{
	byte * origin = (byte *)(memory);
	size_t block = 0x08;
	size_t lower = block * (offset / block);
	size_t upper = block + lower;
	size_t index = 0;
	char buffer [100];
	char * output;
	while (lower < extent) 
	{
		output = buffer + sizeof (extent) + sizeof (extent);
		for (index = lower; output-- > buffer; index >>= 4) 
		{
			*output = DIGITS_HEX [index & 0x0F];
		}
		output = buffer + sizeof (extent) + sizeof (extent);
		for (index = lower; index < upper; index++) 
		{
			unsigned bits = 8;
			*output++ = ' ';
			if (index < offset) 
			{
				while (bits--) 
				{
					*output++ = ' ';
				}
			}
			else if (index < extent) 
			{
				while (bits--) 
				{
					*output++ = DIGITS_BIN [(origin [index] >> bits) & 0x01];
				}
			}
			else 
			{
				while (bits--) 
				{
					*output++ = ' ';
				}
			}
		}
		*output++ = ' ';
		for (index = lower; index < upper; index++) 
		{
			if (index < offset) 
			{
				*output++ = ' ';
			}
			else if (index < extent) 
			{
				unsigned c = origin [index];
				*output++ = isprint (c)? c: '.';
			}
			else 
			{
				*output++ = ' ';
			}
		}

#ifdef HTML

		*output++ = '<';
		*output++ = 'b';
		*output++ = 'r';
		*output++ = '/';
		*output++ = '>';

#endif

		*output++ = '\n';
		*output++ = '\0';
		fputs (buffer, fp);
		lower += block;
		upper += block;
	}
	output = buffer;

#ifdef HTML

	*output++ = '<';
	*output++ = 'b';
	*output++ = 'r';
	*output++ = '/';
	*output++ = '>';

#endif

	*output++ = '\n';
	*output++ = '\0';
	fputs (buffer, fp);
	return;
}


#endif

