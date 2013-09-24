/*====================================================================*
 *
 *   size_t hexload (void * memory, size_t extent, FILE *fp);
 *
 *   memory.h
 *
 *   read a file and convert hexadecimal octets to binary bytes then 
 *   store them in consecutive memory locations up to a given length; 
 *   return the actual number of bytes stored;
 *
 *   digits may be consecutive or separated by white space consisting 
 *   of spaces, tabs, linefeeds, carriage returns, formfeeds or other
 *   characters such as punctuation; C-style or script-style comments 
 *   are treated as white space;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef HEXIN_SOURCE
#define HEXIN_SOURCE

#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <errno.h>

#include "../tools/memory.h"
#include "../tools/error.h"

size_t hexload(void * memory, size_t extent, FILE * fp)

{
	uint8_t * origin = (uint8_t *) (memory);
	uint8_t * offset = (uint8_t *) (memory);
	unsigned digits = 0;
	signed c = EOF;
	while ((extent) && ((c = getc(fp)) != EOF) && (c != ';'))
	{
		if (isspace(c))
		{
			continue;
		}
		if (c == '#')
		{
			do 
			{
				c = getc(fp);
			}
			while ((c != '\n') && (c != EOF));
			continue;
		}
		if (c == '/')
		{
			c = getc(fp);
			if (c == '/')
			{
				do 
				{
					c = getc(fp);
				}
				while ((c != '\n') && (c != EOF));
				continue;
			}
			if (c == '*')
			{
				while ((c != '/') && (c != EOF))
				{
					while ((c != '*') && (c != EOF))
					{
						c = getc(fp);
					}
					c = getc(fp);
				}
				continue;
			}
			continue;
		}
		if ((c >= '0') && (c <= '9'))
		{
			* offset *= 16;
			* offset += c - '0';
			if (digits++ & 1)
			{
				offset++;
				extent--;
			}
			continue;
		}
		if ((c >= 'A') && (c <= 'F'))
		{
			* offset *= 16;
			* offset += 10;
			* offset += c - 'A';
			if (digits++ & 1)
			{
				offset++;
				extent--;
			}
			continue;
		}
		if ((c >= 'a') && (c <= 'f'))
		{
			* offset *= 16;
			* offset += 10;
			* offset += c - 'a';
			if (digits++ & 1)
			{
				offset++;
				extent--;
			}
			continue;
		}

#if defined (BAILOUT)

		error (1, ENOTSUP, "Illegal hex digit '%c' (0x%02X) in source", c, c);

#else

		return ((size_t) (- 1));

#endif

	}
	if ((extent) && (digits & 1))
	{

#if defined (BAILOUT)

		error (1, ENOTSUP, "Odd number of hex digits (%d) in source", digits);

#else

		return ((size_t) (- 1));

#endif

	}

#if 0

	while ((c != ';') && (c != EOF))
	{
		c = getc(fp);
	}

#endif

	return (offset - origin);
}

#endif



