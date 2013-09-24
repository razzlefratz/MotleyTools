/*====================================================================*
 *
 *   void hexview (void const * memory, size_t offset, size_t extent, FILE *fp);
 *
 *   memory.h
 *
 *   print memory as a hexadecimal dump showing absolute offsets and
 *   an ASCII character display; this function is similar to but not
 *   the same as function hexdump;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef HEXVIEW_SOURCE
#define HEXVIEW_SOURCE

#include <stdio.h>
#include <ctype.h>
#include <stdint.h>

#include "../tools/memory.h"
#include "../tools/number.h"
#include "../tools/sizes.h"

void hexview(void const * memory, size_t offset, size_t extent, FILE * fp)

{
	byte * origin = (byte *) (memory);
	unsigned block = 0x10;
	size_t lower = block * (offset / block);
	size_t upper = block +  lower;
	size_t index = 0;
	char buffer[_ADDRSIZE +  72];
	char * output;
	while (lower < offset +  extent)
	{
		output = buffer +  _ADDRSIZE;
		for (index = lower; output-- > buffer; index >>= 4)
		{
			* output = DIGITS_HEX[index & 0x0F];
		}
		output = buffer +  _ADDRSIZE;
		for (index = lower; index < upper; index++)
		{
			* output++ = ' ';
			if (index < offset)
			{
				* output++ = ' ';
				* output++ = ' ';
			}
			else if(index < offset +  extent)
			{
				* output++ = DIGITS_HEX[(origin[index - offset] >> 4) & 0x0F];
				* output++ = DIGITS_HEX[(origin[index - offset] >> 0) & 0x0F];
			}
			else 
			{
				* output++ = ' ';
				* output++ = ' ';
			}
		}
		* output++ = ' ';
		for (index = lower; index < upper; index++)
		{
			if (index < offset)
			{
				* output++ = ' ';
			}
			else if(index < offset +  extent)
			{
				unsigned c = origin[index - offset];
				* output++ = isprint(c)? c: '.';
			}
			else 
			{
				* output++ = ' ';
			}
		}
		* output++ = '\n';
		* output++ = '\0';
		fputs (buffer, fp);
		lower += block;
		upper += block;
	}

#if 0

/*
 *   applications that call this function, like odd and odc, do not want
 *   a blank line in between blocks;
 */

	output = buffer;
	* output++ = '\n';
	* output++ = '\0';
	fputs (buffer, fp);

#endif

	return;
}

#endif



