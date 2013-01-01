/*====================================================================*
 *
 *   void markup (signed device, signed indent, char const *format, ...);
 *
 *   format.h
 *
 *   print a formatted string having a specified indent level;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MARKUP_SOURCE
#define MARKUP_SOURCE

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#include "../tools/format.h"

#ifdef __GNUC__

__attribute__ ((format (printf, 3, 4))) 

#endif

void markup (signed device, signed indent, char const *format, ...) 

{
	static char tab = '\t';
	static char end = '\n';
	char buffer [1024];
	signed length = 0;
	while (indent-- > 0) 
	{
		write (device, &tab, sizeof (tab));
	}
	if ((format) && (*format)) 
	{
		va_list arglist;
		va_start (arglist, format);
		length = vsnprintf (buffer, sizeof (buffer), format, arglist);
		va_end (arglist);
	}
	write (device, buffer, length);
	write (device, &end, sizeof (end));
	return;
}


#endif

