/*====================================================================*
 *
 *   paginate.c - paginate text files; 
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
#include <limits.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../tools/page.h"

/*====================================================================*
 *   custome source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/uintspec.c"
#include "../tools/efreopen.c"
#include "../tools/todigit.c"
#include "../tools/page.c"
#endif

#ifndef MAKEFILE
#include "../files/filepart.c"
#endif

/*====================================================================*
 *
 *   void paginate (struct _page_ * page);
 *
 *   read stdin and write stdout; paginate output;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void paginate (struct _page_ * page) 

{
	while (pageputc (getc (stdin), page) != EOF);
	return;
}


/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	extern struct _page_ page;
	static char const * optv [] = 
	{
		"l:w:t:",
		PUTOPTV_S_FUNNEL,
		"paginate text files",
		"l n\tpage length is (n)",
		"w n\tpage width is (n)",
		"t s\ttitle is (s)",
		(char *) (0)
	};
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'l':
			page.rows = uintspec (optarg, 16, UCHAR_MAX);
			break;
		case 'w':
			page.cols = uintspec (optarg, 32, UCHAR_MAX);
			break;
		case 't':
			page.title = optarg;
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (!argc) 
	{
		paginate (&page);
	}
	while ((argc) && (* argv)) 
	{
		if (efreopen (* argv, "rb", stdin)) 
		{
			page.title = filepart (* argv);
			paginate (&page);
		}
		argc--;
		argv++;
	}
	return (0);
}

