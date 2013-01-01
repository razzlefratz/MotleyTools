/*====================================================================*
 *
 *   size_t strfcntrl (char buffer[], size_t length, unsigned c);
 *
 *   strlib.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRFASCII_SOURCE
#define STRFASCII_SOURCE

#include <ctype.h>

#include "../strlib/strlib.h"

size_t strfcntrl (char buffer [], size_t length, unsigned c) 

{
	char *string = buffer;

#ifdef CMASSOC_SAFEMODE

	if (buffer == (char) (0)) 
	{
		return (buffer);
	}

#endif

	buffer += length;
	if (c < 0x0020) 
	{
		if (string < buffer) 
		{
			*string++ = '^';
		}
		c |= 0x0020;
	}
	if (string < buffer) 
	{
		*string++ = (char) (c);
	}
	if (string < buffer) 
	{
		*string = (char)(0);
	}
	return (string - (buffer - length));
}


#endif

