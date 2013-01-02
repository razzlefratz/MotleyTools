/*====================================================================*
 *
 *   go.c -                                  
 *
 *   copy one or more files to stdout; if no files are specified 
 *   then copy stdin to stdout;
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
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../tools/command.h"
#include "../linux/linux.h"
#include "../strlib/strlib.h"
#include "../tree/tree.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/command.c"
#include "../tools/emalloc.c"
#include "../tools/cgetc.c"
#include "../tools/error.c"
#endif

/*====================================================================*
 *
 *   int main (int argc, char * argv []);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	extern char c;
	static char const * optv [] = 
	{
		"",
		PUTOPTV_S_FUNNEL,
		"example command line program",
		(char const *)(0)
	};
	TREE *node = (TREE *)(0);
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
	printf ("stdin %s a tty\n", isatty (STDIN_FILENO)? "is": "is not");
	while ((c = cgetc (STDIN_FILENO)) != EOF) 
	{
		DCLInit ();
		node = DCLLine ();
		if ((c != ';') && (c != EOF)) 
		{
			error (1, 0, "Have '%c' but need ';'", c);
		}
		DCLTree (node);
		DCLFree (node);
	}
	return (0);
}

