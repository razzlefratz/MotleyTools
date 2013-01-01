/*====================================================================*
 *
 *   void print (signed level, char const *format, ...);
 *
 *   tools.h
 *
 *   print a formatted string haing the proper indent level;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PRINT_SOURCE
#define PRINT_SOURCE

#include <stdio.h>
#include <stdarg.h>

#include "../tools/tools.h"

#ifdef __GNUC__

__attribute__ ((format (printf, 2, 3))) 

#endif

void print (signed level, char const *format, ...) 

{
	while (level-- > 0) 
	{
		putc ('\t', stdout);
	}
	if ((format) && (*format)) 
	{
		va_list arglist;
		va_start (arglist, format);
		vprintf (format, arglist);
		va_end (arglist);
	}
	putc ('\n', stdout);
	return;
}


#endif

