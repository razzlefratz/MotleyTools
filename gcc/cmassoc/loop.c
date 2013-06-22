/*====================================================================*
 *
 *   loop.c - command sequence repeater
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
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/getoptv.h"
#include "../tools/putoptv.h"
#include "../tools/version.h"
#include "../tools/number.h"
#include "../tools/error.h"
#include "../tools/sizes.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE 
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/error.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define COUNT 1
#define PAUSE 0

/*====================================================================*
 *
 *   int main (int argc, char * const argv []);
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
		"el:w:",
		"command [command] [...]",
		"command sequence repeater",
		"e\tdirect stderr to stdout",
		"l n\tloop (n) times [" LITERAL (COUNT) "]",
		"w n\twait (n) seconds [" LITERAL (PAUSE) "]",
		(char const *) (0)
	};
	FILE * fp;
	signed index = 0;
	signed count = COUNT;
	signed pause = PAUSE;
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'l':
			count = (unsigned)(uintspec (optarg, 1, USHRT_MAX));
			break;
		case 'w':
			pause = (unsigned)(uintspec (optarg, 1, USHRT_MAX));
			break;
		case 'e':
			dup2 (STDOUT_FILENO, STDERR_FILENO);
			break;
		default:
			break;
		}
	}
	argc-= optind;
	argv+= optind;
	while (count--) 
	{
		for (index = 0; index < argc; index++) 
		{
			if ((fp = popen (argv [index], "r"))) 
			{
				while ((c = getc (fp)) != EOF) 
				{
					putc (c, stdout);
				}
			}
			putc ('\n', stdout);
		}
		if (count) 
		{
			sleep (pause);
		}
	}
	exit (0);
}

