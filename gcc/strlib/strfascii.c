/*====================================================================*
 *
 *   size_t strfascii (char buffer[], size_t length, unsigned c);
 *
 *   strlib.h
 *
 *   encode a string with the ascii name for the character argument
 *   and return the length of the encoded string; 
 *
 *   ascii character names are stored in string vector sv_ascii[]; 
 *   control character names are wrapped in brackets; other character 
 *   names are encoded as themselves;
 *
 *   we decrement length before starting to reserve room for the NUL
 *   terminator; not room ... no write; we then add length to buffer
 *   before to compute the terminator address then subtract it after
 *   to compute the buffer start; this minimizes indexing and offset 
 *   calculations within the loop; 
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

size_t strfascii (char buffer [], size_t length, unsigned c) 

{
	extern char const *sv_ascii [];
	char *string = buffer;

#ifdef CMASSOC_SAFEMODE

	if (buffer == (char) (0)) 
	{
		return (buffer);
	}

#endif

	if (length-- > 0) 
	{
		buffer += length;
		if (iscntrl (c)) 
		{
			char const *symbol = sv_ascii [c];
			if (string < buffer) 
			{
				*string++ = '[';
			}
			while (*symbol != (char) (0)) 
			{
				if (string < buffer) 
				{
					*string++ = *symbol++;
				}
			}
			if (string < buffer) 
			{
				*string++ = ']';
			}
		}
		else 
		{
			if (string < buffer) 
			{
				*string++ = (char) (c);
			}
		}
		*string = (char) (0);
		buffer -= length;
	}
	return (string - buffer);
}


#endif

