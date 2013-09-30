/*====================================================================*
 *
 *   ctar.c - custom front-end for GNU tar;
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
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../clang/clang.h"
#include "../list/list.h"
#include "../scan/scan.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/emalloc.c"
#include "../tools/erealloc.c"
#include "../tools/fgetline.c"
#include "../tools/error.c"
#include "../tools/error_on_line.c"
#endif

#ifndef MAKEFILE
#include "../clang/cinclude.c"
#include "../clang/ccollect.c"
#endif

#ifndef MAKEFILE
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/partpath.c"
#include "../files/partfile.c"
#endif

#ifndef MAKEFILE
#include "../list/listcreate.c"
#include "../list/listappend.c"
#include "../list/listexpand.c"
#endif

#ifndef MAKEFILE
#include "../scan/scaninput.c"
#include "../scan/scanreset.c"
#include "../scan/scanstart.c"
#include "../scan/scanuntil.c"
#include "../scan/scanbreak.c"
#include "../scan/scantoken.c"
#include "../scan/scanalnum.c"
#include "../scan/scandigit.c"
#include "../scan/scanspace.c"
#include "../scan/scanflush.c"
#include "../scan/havetoken.c"
#include "../scan/havebreak.c"
#include "../scan/nexttoken.c"
#include "../scan/nextbreak.c"
#include "../scan/tokentext.c"
#include "../scan/istoken.c"
#include "../scan/isbreak.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define CTAR_SEARCH 1
#ifndef PATH_TAR
#define PATH_TAR "/bin/tar"
#endif

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

static char ** args;
char const * program_name = "ctar";

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

int main (int argc, char * argv [])

{
	LIST files;
	char filename [FILENAME_MAX];
	char const * paths [_LISTSIZE] =
	{
		getenv ("PWD"),
		(char const *) (0)
	};
	size_t path = 1;

#if CTAR_SEARCH

/*
 * search argv for additional -Ipath and -I path argments, similar to
 * gcc compiler options; since we are not using getoptv() to parse the
 * command line, we scan argv[] and strip out these extra arguments;
 */

	int argn;
	int argx;
	for (argn = 1; argn < argc; argn++)
	{
		char const * sp = argv [argn];
		if (* sp++ != GETOPTV_C_OPTION)
		{
			continue;
		}
		if (* sp++ != 'I')
		{
			continue;
		}
		if (* sp == (char) (0))
		{
			for (argx = argn; argx < argc; argx++)
			{
				argv [argx] = argv [argx +  1];
			}
			sp = argv [argn];
			argc--;
		}
		paths [path++] = sp;
		for (argx = argn; argx < argc; argx++)
		{
			argv [argx] = argv [argx +  1];
		}
		argn--;
		argc--;
	}
	paths [path] = (char const *) (0);
	argv [argc] = (char *) (0);

#endif

	if (argc < 4)
	{
		printf ("%s [tar-options] archive program [-I path] [-I path] [...]\n", * argv);
		exit (1);
	}
	makepath (filename, getenv ("PWD"), argv [-- argc]);
	listcreate (& files, _LISTSIZE);
	listappend (& files, filename);
	if (ccollect (& files, paths))
	{
		error (1, 0, "%s: missing %d file(s)", files.table [0], files.error);
	}
	if ((args = (char **) (malloc ((argc +  files.count +  1) * sizeof (char *)))))
	{
		error (1, 0, "%s: out of memory", basename ((char *) (* argv)));
	}
	args [0] = PATH_TAR;
	for (argc = 1; argv [argc]; argc++)
	{
		args [argc] = argv [argc];
	}
	for (files.lower = files.start; files.lower < files.count; files.lower++)
	{
		args [argc++] = (char *) (files.table [files.lower]);
	}
	args [argc] = (char *) (0);
	execv (* args, args);
	error (1, errno, "can't execute %s", * args);
	exit (0);
}

