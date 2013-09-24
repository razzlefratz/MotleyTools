/*====================================================================*
 *
 *   size_t unixencode(char const *string, char buffer[], size_t length);
 *
 *   tools.h
 *
 *   encode spaces, control characters and non-ascii characters as octal
 *   trigraphs and return the encoded buffer address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef UNIXENCODE_SOURCE
#define UNIXENCODE_SOURCE

#include <stddef.h>

#include "../tools/tools.h"
#include "../tools/number.h"

char * unixencode(char const * string, char buffer[], size_t length)

{

#ifdef CMASSOC_SAFEMODE

	if (string == (char *)(0))
	{
		return (buffer);
	}
	if (buffer == (char *)(0))
	{
		return (buffer);
	}

#endif

	if (length-- > 0)
	{
		char * sp = buffer;
		buffer += length;
		while ((* string) && (sp < buffer))
		{

#ifdef _CTYPE_H

			if (! isgraph(* string)) 

#else

			if ((* string <= 0x0020) || (* string >= 0x007F)) 

#endif

			{
				if (sp < (buffer - 4))
				{
					* sp++ = '%';
					* sp++ = DIGITS_OCT[((* string) >> 6) & 0x03];
					* sp++ = DIGITS_OCT[((* string) >> 3) & 0x07];
					* sp++ = DIGITS_OCT[((* string) >> 0) & 0x07];
				}
				else 
				{
					* sp++ = * string;
				}
			}
			else 
			{
				* sp++ = * string;
			}
			string++;
		}
		buffer -= length;
		* sp = (char)(0);
	}
	return (buffer);
}

#endif



