/*====================================================================*
 *
 *   char *strcap(char *string, char const *charset)
 *
 *   strlib.h
 *
 *   capitalize each word of a string where a word consists of the letter
 *   and punctuation found in charset;
 *
 *   if charset is only letters then "save e:my_file.dat" is capitalized
 *   as "Save E:My_File.Dat". By adding '.' and '_' to charset, it would
 *   capitalize as "Save E:My_file.dat";
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRCAP_SOURCE
#define STRCAP_SOURCE

#include <ctype.h>
#include <string.h>

#include "../strlib/strlib.h"

char *strcap (char buffer [], char const *charset) 

{
	register int word = 0;
	register char *sp;

#ifdef CMASSOC_SAFEMODE

	if (buffer == (char *) (0)) 
	{
		return (buffer);
	}
	if (charset == (char const *) (0)) 
	{
		return (buffer);
	}

#endif

	for (sp = buffer; *sp != (char) (0); ++sp) 
	{
		if (strchr (charset, *sp) != (char *) (0)) 
		{
			*sp = (!word)? (char) (toupper (*sp)): (char) (tolower (*sp));
			word++;
		}
		else 
		{
			word = 0;
		}
	}
	return (buffer);
}


#endif

