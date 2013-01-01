/*====================================================================*
 *
 *   size_t strjoin (char const * vector[], char buffer [], signed c);
 *
 *   strlib.h
 *
 *   create one string from vector strings; separate each string 
 *   with one character; preserve the vector; rewrite the buffer;
 *   return the resulting string length;
 *
 *   this function is small and fast but may be unsafe since there  
 *   are not boundary checks;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRJOIN_SOURCE
#define STRJOIN_SOURCE

#include "../strlib/strlib.h"

size_t strjoin (char const * vector [], char buffer [], signed c) 

{
	register char const * sp;
	register char * cp;

#ifdef CMASSOC_SAFEMODE

	if (vector == (char const **) (0)) 
	{
		return (0);
	}
	if (buffer == (char *) (0)) 
	{
		return (0);
	}

#endif

	for (cp = buffer; *vector != (char *) (0); *cp++ = c) 
	{
		for (sp = *vector++; *sp != (char) (0); *cp++ = *sp++);
	}
	*cp = (char) (0);
	return (cp - buffer);
}


#endif

