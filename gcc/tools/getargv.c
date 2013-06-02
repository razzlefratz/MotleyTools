/*====================================================================*
 *   
 *   Copyright (c) 2012 by Qualcomm Atheros.
 *   
 *   Permission to use, copy, modify, and/or distribute this software 
 *   for any purpose with or without fee is hereby granted, provided 
 *   that the above copyright notice and this permission notice appear 
 *   in all copies.
 *   
 *   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL 
 *   WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED 
 *   WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL  
 *   THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR 
 *   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM 
 *   LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, 
 *   NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN 
 *   CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *   
 *--------------------------------------------------------------------*/

/*====================================================================*
 *
 *   signed getargv (signed argc, char const * argv [])
 *
 *   symbol.h
 *
 *   read one line from stdin; fill argv [] with fields from that
 *   line; return the number of fields found; ignore blank lines 
 *   and script style comment lines; this implementation inserts
 *   a program name at argv [0] to emulate a true argv [];
 *
 *.  Qualcomm Atheros HomePlug AV Powerline Toolkit
 *:  Published 2009-2012 by Qualcomm Atheros. ALL RIGHTS RESERVED
 *;  For demonstration and evaluation only. Not for production use
 *
 *--------------------------------------------------------------------*/

#ifndef GETARGV_SOURCE
#define GETARGV_SOURCE

#include <stdio.h>
#include <ctype.h>
#include <memory.h>

#include "../tools/symbol.h"
#include "../tools/chars.h"

signed getargv (signed argc, char const * argv []) 

{
	static char string [4096];
	char const ** argp = argv;
	char * sp = string;
	signed c;
	memset (string, 0, sizeof (string));
	memset ((char **)(argv), 0, argc * sizeof (char const *));
	do 
	{
		c = getc (stdin);
		if (c == '#') 
		{
			do { c = getc (stdin); } while (nobreak (c));
		}
	}
	while (isspace (c));
	*argp = sp;
	while (nobreak (c)) 
	{
		if (isblank (c)) 
		{
			do { c = getc (stdin); } while (isblank (c));
			*sp++ = (char)(0);
			*++argp = sp;
		}
		else if (isquote (c)) 
		{
			signed o = c;
			for (c = getc (stdin); nobreak (c) && (c != o); c = getc (stdin)) 
			{
				*sp++ = (char) (c);
			}
			if (c ==  o)
			{
				c = getc (stdin);
			}
			*sp++ = (char)(0);
		}
		else
		{
			*sp++ = (char)(c);
			c = getc (stdin);
		}
	}
	*sp = (char)(0);
	if (*argp != sp)
	{
		argp++;
	}
	*argp = (char const *)(0);
	return ((signed)(argp - argv));
}


#endif

