/*====================================================================*
 *
 *   hbrief.c - remove HTLM attributes; 
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../files/files.h"
#include "../chrlib/chrlib.h"
#include "../clang/clang.h"
#include "../tidy/tidy.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

#ifndef MAKEFILE
#include "../tidy/nocontext.c"
#include "../tidy/noliteral.c"
#include "../tidy/noescaped.c"
#include "../tidy/keep.c"
#endif

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

unsigned lineno = 0;

/*====================================================================*
 *
 *   int element (int c) 
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static signed element (int c) 

{
	c = getc (stdin);
	if ((c == '?') || (c == '%')) 
	{
		do 
		{
			c = nocontext (c, c);
		}
		while ((c != '>') && (c != EOF));
		return (c);
	}
	if (c == '!') 
	{
		do 
		{
			c = keep (c);
		}
		while (isalnum (c) || ((char)(c) == '-'));
		c = nocontext (c, '>');
		return (c);
	}
	if (isalpha (c) || ((char)(c) == '/')) 
	{
		do 
		{
			c = keep (c);
		}
		while (isident (c));
		c = nocontext (c, '>');
		return (c);
	}
	return (c);
}


/*====================================================================*
 *
 *   void document (flag_t flags) 
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void document (flag_t flags) 

{
	signed c;
	while ((c = getc (stdin)) != EOF) 
	{
		if (c == '<') 
		{
			putc ('<', stdout);
			c = element (c);
			putc ('>', stdout);
			continue;
		}
		putc (c, stdout);
	}
	return;
}


/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"",
		PUTOPTV_S_FILTER,
		"remove HTML attributes from HTML tags",
		(char const *) (0)
	};
	flag_t flags = (flag_t)(0);
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (!argc) 
	{
		document (flags);
	}
	while ((argc) && (* argv)) 
	{
		if (vfopen (* argv)) 
		{
			document (flags);
		}
		argc--;
		argv++;
	}
	exit (0);
}

