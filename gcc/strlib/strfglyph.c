/*====================================================================*
 *
 *   size_t strfglyph (char buffer[], size_t length, unsigned c);
 *
 *   chrlib.h
 *
 *   encode buffer with the ISO glyph name of the character argument
 *   or the character argument if no glyph name exists; prefix glyph
 *   names with '&' and suffix them with ';';
 *
 *   we decrement length before starting to reserve room for the NUL
 *   terminator; not room ... no write; we then add length to buffer
 *   before to compute the terminator address then subtract it after
 *   to compute the buffer start; this minimizes indexing and offset 
 *   calculations within the loop; 
 *
 *   raw glyph names are stored in string vector sv_glyph[]; 
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

size_t strfglyph (char buffer [], size_t length, unsigned c) 

{
	extern char const * sv_glyph [];
	char *string = buffer;

#ifdef CMASSOC_SAFEMODE

	if (!buffer) 
	{
		return (buffer);
	}

#endif

	if (length--) 
	{
		buffer += length;
		if (iscntrl (c)) 
		{
			char const *symbol = sv_glyph [c];
			if (string < buffer) 
			{
				*string++ = '&';
			}
			while ((string < buffer) && (*symbol != (char) (0))) 
			{
				*string++ = *symbol++;
			}
			if (string < buffer) 
			{
				*string++ = ';';
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

