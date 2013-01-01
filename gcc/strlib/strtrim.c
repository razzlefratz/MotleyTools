/*====================================================================*
 *
 *   char *strtrim(const register char *buffer)
 *
 *   strlib.h
 *
 *   remove white space from both ends of a buffer and return the buffer
 *   address; white space is whatever isspace() dictates;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRTRIM_SOURCE
#define STRTRIM_SOURCE

#include <ctype.h>
#include "../strlib/strlib.h"

char *strtrim (register char buffer []) 

{
	char *sp,
	*cp;
	if (buffer == (char *) (0)) 
	{
		return (buffer);
	}
	for (cp = buffer; isspace (*cp); cp++);
	for (sp = buffer; *cp != (char) (0); *sp++ = *cp++);
	while ((sp-- > buffer) && isspace (*sp)) 
	{
		*sp = (char) (0);
	}
	return (buffer);
}


#endif

