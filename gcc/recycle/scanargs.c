/*====================================================================*
 *
 *   static int scanargs (SCAN *scan);
 *   
 *   collect option arguments in scan->value[]; discard any leading 
 *   or trailing whitespace; an optional equals sign may separate the
 *   option from its values;
 *
 *   rather than scan to line end and back-track over trailing space,
 *   we use a 'catch-up' pointer;  
 *
 *   on entering this function, the token buffer contains the option;
 *   we overwrite the option when arguments are present but leave it
 *   alone they are missing; we can use it in the error message since 
 *   it is still available if an error occurs;
 *
 *   this function expects an argument; otherwise, it prints an error
 *   message and returns an error code; right now, optional arguments
 *   must be scanned in-line,... with in-line code.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANVALUE_SOURCE
#define SCANVALUE_SOURCE

#include <ctype.h>
#include <errno.h>

#include "../recycle/recycle.h"
#include "../tools/error.h"

int scanargs (SCAN *scan) 

{
	while (isblank (*scan->cp)) 
	{
		++scan->cp;
	}
	if (*scan->cp == '=') 
	{
		++scan->cp;
	}
	while (isblank (*scan->cp)) 
	{
		++scan->cp;
	}
	scan->tp = scan->token;
	for (scan->sp = scan->cp; !isbreak (*scan->cp); ++scan->cp) 
	{
		if (!isblank (*scan->cp)) 
		{
			while (scan->sp <= scan->cp) 
			{
				*scan->tp++ = *scan->sp++;
			}
		}
	}
	if (scan->tp == scan->token) 
	{
		error_on_line (0, EINVAL, scan->file, scan->line, "option '%s' has no arguments", scan->token);
		return (-1);
	}
	*scan->tp = (char) (0);
	return (0);
}


#endif

