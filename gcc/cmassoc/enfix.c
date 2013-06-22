/*====================================================================*
 *
 *   enfix.c - record prefix/suffix append program;
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
#include <string.h>
#include <ctype.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../strlib/strlib.h"
#include "../chrlib/chrlib.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/todigit.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

#ifndef MAKEFILE
#include "../strlib/struesc.c"
#include "../chrlib/chruesc.c"
#endif

/*====================================================================*
 *
 *   void function (char * prefix, char * suffix, flag_t flags)
 *
 *   read from stdin and write to stdout; append the prefix and suffix 
 *   string to each output line; ignore NULL prefix or suffix strings;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (char const * prefix, char const * suffix, flag_t flags) 

{
	signed c;
	signed o = '\n';
	while ((c = getc (stdin)) != EOF) 
	{
		if (o == '\n') 
		{
			fputs (prefix, stdout);
		}
		if (c == '\n') 
		{
			fputs (suffix, stdout);
		}
		o = putc (c, stdout);
	}
	return;
}

/*====================================================================*
 *  main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"p:s:",
		PUTOPTV_S_FILTER,
		"prepend/append text to each line of a text file",
		"p s\tprefix is s",
		"s s\tsuffix is s",
		(char const *)(0)
	};
	flag_t flags = (flag_t)(0);
	char * prefix = "";
	char * suffix = "";
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'p':
			prefix = struesc ((char *) (optarg));
			break;
		case 's':
			suffix = struesc ((char *) (optarg));
			break;
		default:
			break;
		}
	}
	argc-= optind;
	argv+= optind;
	if (!argc) 
	{
		function (prefix, suffix, flags);
	}
	while ((argc) && (* argv)) 
	{
		if (vfopen (* argv)) 
		{
			function (prefix, suffix, flags);
		}
		argc--;
		argv++;
	}
	exit (0);
}

