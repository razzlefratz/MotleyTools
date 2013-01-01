/*====================================================================*
 *
 *   size_t strvsplit(char const *vector[], char buffer[])
 *
 *   strlib.h
 *
 *   separate buffer strings and store start addresses in vector;   
 *   return the number of stored strings;
 *   
 *   AAA[-AAA[-AAA]].000[.000[.000[...]]]
 *
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRVSPLIT_SOURCE
#define STRVSPLIT_SOURCE

#include "../strlib/strlib.h"

size_t strvsplit (char *vector [], register char buffer []) 

{
	char **vp = vector;

#ifdef CMASSOC_SAFEMODE

	if (vector == (char **) (0)) 
	{
		return (0);
	}
	if (buffer == (char *) (0)) 
	{
		return (0);
	}

#endif

	for (*vector = buffer; *buffer; buffer++) 
	{
		if (*buffer == '-') 
		{
			*++vector = buffer + 1;
			*buffer = (char)(0);
		}
	}
	for (buffer = *vector; *buffer; buffer++) 
	{
		if (*buffer == '.') 
		{
			*++vector = buffer + 1;
			*buffer = (char) (0);
		}
	}
	*++vector = (char *) (0);
	return (vector - vp);
}


#endif

