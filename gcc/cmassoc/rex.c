/*====================================================================*
 *
 *   rex.c - replace file extension;
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

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define RETYPE_ERROR 0x0001
#define RETYPE_EVENT 0x0002

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main(int argc, char const * argv[])

{
	static char const * optv[] = 
	{
		"o:n:v",
		"file [file] [...]",
		"replace file extension",
		"o s\told file extension is (s)",
		"n s\tnew file extension is (s)",
		"v\tverbose messages ",
		(char const *)(0)
	};
	char const * old = "";
	char const * new = "";
	char file[FILENAME_MAX];
	char * sp;
	char * cp;
	flag_t flags = (flag_t)(0);
	signed c;
	while (~ (c = getoptv(argc, argv, optv)))
	{
		switch (c)
		{
		case 'o':
			old = optarg;
			break;
		case 'n':
			new = optarg;
			break;
		case 'v':
			_setbits (flags, RETYPE_EVENT);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	while ((argc) && (* argv))
	{
		for (cp = sp = strcpy(file, * argv); * sp; sp++)
		{
			if (* sp == FILE_C_EXTENDER)
			{
				cp = sp;
			}
		}
		if (cp > file)
		{
			if (! strcmp(cp, old))
			{
				strcpy (cp, new);
			}
		}
		if (strcmp(* argv, file))
		{
			if (rename(* argv, file))
			{
				error (0, errno, "can't rename %s to %s", * argv, file);
			}
			else if(_anyset(flags, RETYPE_EVENT))
			{
				error (0, 0, "%s <-- %s", file, * argv);
			}
		}
		argc--;
		argv++;
	}
	exit (0);
}

