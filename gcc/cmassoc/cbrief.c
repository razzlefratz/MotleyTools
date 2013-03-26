/*====================================================================*
 *
 *   cbrief.c - remove C Language comments; 
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
#include "../tidy/tidy.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

#ifndef MAKEFILE
#include "../tidy/nocomment.c"
#include "../tidy/literal.c"
#include "../tidy/escaped.c"
#include "../tidy/keep.c"
#endif

/*====================================================================*
 *
 *   void function (flag_t flags);
 *
 *   read stdin and write stdout; intercept and discard C Language
 *   style comments that start with double slash or appear between
 *   inverted slash/asterisk character pairs;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (signed c, flag_t flags) 

{
	while (c != EOF) 
	{
		if (c == '/') 
		{
			c = nocomment (c);
			continue;
		}
		if (isquote (c)) 
		{
			c = literal (c);
			continue;
		}
		c = keep (c);
	}
	return;
}


/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"",
		PUTOPTV_S_FILTER,
		"remove C/C++ language comments",
		(char const *) (0)
	};
	flag_t flags = (flag_t) (0);
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
		function (getc (stdin), flags);
	}
	while ((argc) && (* argv)) 
	{
		if (vfopen (* argv)) 
		{
			function (getc (stdin), flags);
		}
		argv++;
		argc--;
	}
	return (0);
}

