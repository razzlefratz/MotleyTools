/*====================================================================*
 *
 *   go.c -
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
#include <string.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../tools/dcl.h"
#include "../linux/linux.h"
#include "../strlib/strlib.h"

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
	static char const * optv [] =
	{
		"",
		PUTOPTV_S_FUNNEL,
		"example command line program",
		(char const *) (0)
	};
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	while (~ (c = DCLRead ()))
	{
		TREE * root = DCLLine ();
		TREE * node = root;
		while (node)
		{
			if (!strcmp (node->name, "quit"))
			{
				DCLFree (root);
				return (0);
			}
			if (!strcmp (node->name, "exit"))
			{
				DCLFree (root);
				return (0);
			}
			node = node->next;
		}
		DCLFree (root);
	}
	return (0);
}

