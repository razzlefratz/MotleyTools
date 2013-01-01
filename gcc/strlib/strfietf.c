/*====================================================================*
 *
 *   size_t strfietf (char buffer[], size_t length, unsigned c);
 *
 *   strlib.h
 *
 *   encode spaces, control characters and non-ascii characters as hexadecimal
 *   octets and return encoded buffer address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   compiled using gnu c++ compiler under dibian linux;
 *
 *--------------------------------------------------------------------*/

#ifndef STRFIETF_SOURCE
#define STRFIETF_SOURCE

#include "../chrlib/chrlib.h"
#include "../strlib/strlib.h"

size_t strfietf (char buffer [], size_t length, unsigned c) 

{
	extern char const ct_digit [];
	char *string = buffer;

#ifdef CMASSOC_SAFEMODE

	if (buffer == (char *) (0)) 
	{
		return (buffer);
	}

#endif

	if (length-- > 0) 
	{
		buffer += length;

#ifdef _CTYPE_H

		if (!isgraph (*string)) 

#else

		if ((c <= 0x0020) || (c >= 0x007F)) 

#endif

		{
			if (string < buffer) 
			{
				*string++ = '%';
			}
			if (string < buffer) 
			{
				*string++ = ct_digit [(c >> 4) & 0x0F];
			}
			if (string < buffer) 
			{
				*string++ = ct_digit [(c >> 0) & 0x0F];
			}
		}
		else 
		{
			if (string < buffer) 
			{
				*string++ = (char) (c);
			}
		}
		if (string < buffer) 
		{
			*string = (char) (0);
		}
		buffer -= length;
	}
	return (string - buffer);
}


#endif

