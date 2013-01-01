/*====================================================================*
 *
 *   char *strconv (char *string, unsigned char convert (unsigned));
 *
 *   scan string and pass each character to the conversion function
 *   convert(); this avoids repetitive code needed to check strings
 *   and index through them;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRCONV_SOURCE
#define STRCONV_SOURCE

#include "../strlib/strlib.h"

char *strconv (char *string, unsigned char convert (unsigned)) 

{
	char *sp;

#ifdef CMASSOC_SAFEMODE

	if (!string) 
	{
		return (string);
	}

#endif

	for (sp = string; *sp; sp++) 
	{
		*sp = convert (*sp);
	};
	return (string);
}


#endif

