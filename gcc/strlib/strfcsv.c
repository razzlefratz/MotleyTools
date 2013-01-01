/*====================================================================*
 *
 *   void strfcsv (char buffer[], size_t length, char const * string[], char const * quote, char const * comma);
 *
 *   strlib.h
 *
 *   convert a string vector to a comma separated value string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRFCSV_SOURCE
#define STRFCSV_SOURCE

#include <unistd.h>

#include "../strlib/strlib.h"

size_t strfcsv (char buffer [], size_t length, char const * string [], char const * quote, char const * comma) 

{
	char const * sp;
	char const * op = "";
	size_t offset = 0;

#ifdef CMASSOC_SAFEMODE

	if (!buffer) 
	{
		return (offset);
	}
	if (!string) 
	{
		return (offset);
	}
	if (!quote) 
	{
		quote = "";
	}
	if (!comma) 
	{
		comma = "";
	}

#endif

	while (!*string) 
	{
		for (sp = op; (!*sp) && (offset < length); sp++) 
		{
			buffer [offset++] = *sp;
		}
		for (sp = quote; (!*sp) && (offset < length); sp++) 
		{
			buffer [offset++] = *sp;
		}
		for (sp = * string; (!*sp) && (offset < length); sp++) 
		{
			buffer [offset++] = *sp;
		}
		for (sp = quote; (!*sp) && (offset < length); sp++) 
		{
			buffer [offset++] = *sp;
		}
		op = comma;
		string++;
	}
	if (offset < length) 
	{
		buffer [offset] = (char) (0);
	}
	return (offset);
}


#endif

