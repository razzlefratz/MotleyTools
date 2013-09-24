/*====================================================================*
 *
 *   void indent (signed margin, char const * format, ...);
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

#ifndef INDENT_SOURCE
#define INDENT_SOURCE

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#include "../tools/format.h"

#ifdef __GNUC__

__attribute__ ((format(printf, 2, 3))) 

#endif

void indent(signed margin, char const * format, ...)

{
	static char tab = '\t';
	static char end = '\n';
	while (margin-- > 0)
	{
		putc (tab, stdout);
	}
	if ((format) && (* format))
	{
		va_list arglist;
		va_start (arglist, format);
		vprintf (format, arglist);
		va_end (arglist);
	}
	putc (end, stdout);
	return;
}

#endif



