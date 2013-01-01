/*====================================================================*
 *
 *   void svorder (char const *string, char const *vector [], size_t length, signed comp (char const *, char const *));
 *
 *   check a string vector for correct length and string order; print 
 *   an error message and exit the program if either is incorrect; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

#ifndef SVORDER_SOURCE
#define SVORDER_SOURCE

#include <stdlib.h>
#include <string.h>

#include "../strlib/strlib.h"
#include "../tools/error.h"

void svorder (char const *string, char const *vector [], size_t length, signed comp (char const *, char const *)) 

{
	size_t offset;

#ifdef CMASSOC_SAFEMODE

	if (!string) 
	{
		return;
	}
	if (!vector) 
	{
		return;
	}
	if (!comp) 
	{
		return;
	}

#endif

	for (offset = 0; vector [offset]; offset++);
	if (offset != length) 
	{
		error (1, 0, "%s: Have " SIZE_T_SPEC " instead of " SIZE_T_SPEC " members.", string, offset, length);
	}
	for (offset = 1; offset < length; offset++) 
	{
		if (strcmp (vector [offset-1], vector [offset]) > 0) 
		{
			error (1, 0, "%s: Member " SIZE_T_SPEC " ('%s') is out of order.", string, offset, vector [offset]);
		}
	}
	return;
}


#endif

