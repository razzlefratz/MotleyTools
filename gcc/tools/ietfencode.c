/*====================================================================*
 *
 *   size_t ietfencode(char const *string, char buffer[], size_t length);
 *   
 *   tools.h
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

#ifndef IETFENCODE_SOURCE
#define IETFENCODE_SOURCE

#include <stddef.h>
#include <ctype.h>

#include "../tools/tools.h"
#include "../tools/number.h"

char *ietfencode (char const *string, char buffer [], size_t length) 

{

#ifdef CMASSOC_SAFEMODE

	if (string == (char *) (0)) 
	{
		return (buffer);
	}
	if (buffer == (char *) (0)) 
	{
		return (buffer);
	}

#endif

	if (length-- > 0) 
	{
		char *sp = buffer;
		buffer += length;
		while ((*string != (char)(0)) && (sp < buffer)) 
		{

#ifdef _CTYPE_H

			if (!isgraph (*string)) 

#else

			if ((*string <= 0x0020) || (*string >= 0x007F)) 

#endif

			{
				if (sp < (buffer - 3)) 
				{
					*sp++ = '%';
					*sp++ = DIGITS_HEX [(*string >> 4) & 0x0F];
					*sp++ = DIGITS_HEX [(*string >> 0) & 0x0F];
				}
				else 
				{
					*sp++ = *string;
				}
			}
			else 
			{
				*sp++ = *string;
			}
			string++;
		}
		buffer -= length;
		*sp = (char) (0);
	}
	return (buffer);
}


#endif

