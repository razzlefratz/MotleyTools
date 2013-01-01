/*====================================================================*
 *
 *   size_t strfunix (char buffer[], size_t length, unsigned c);
 *
 *   strlib.h
 *
 *   encode spaces, control characters and non-ascii characters as octal
 *   trigraphs and return the encoded buffer address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRFUNIX_SOURCE
#define STRFUNIX_SOURCE

#include "../chrlib/chrlib.h"
#include "../strlib/strlib.h"

size_t strfunix (char buffer [], size_t length, unsigned c) 

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
		while ((*string != (char) (0)) && (string < buffer)) 
		{

#ifdef _CTYPE_H

			if (!isgraph (*string)) 

#else

			if ((*string <= 0x0020) || (*string >= 0x007F)) 

#endif

			{
				if (string < buffer) 
				{
					*string++ = '%';
				}
				if (string < buffer) 
				{
					*string = ct_digit [((*string) >> 6) & 0x03];
					string++;
				}
				if (string < buffer) 
				{
					*string = ct_digit [((*string) >> 3) & 0x07];
					string++;
				}
				if (string < buffer) 
				{
					*string = ct_digit [((*string) >> 0) & 0x07];
					string++;
				}
			}
			else 
			{
				if (string < buffer) 
				{
					*string++ = (char) (c);
				}
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

