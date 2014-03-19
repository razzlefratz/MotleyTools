/*====================================================================*
 *
 *   dep.c - output C Language include file dependency list;
 *
 *   specify one or more target files on the command line; each target
 *   is opened and searched for include files; each of those files is
 *   opened and searched and so on; the resulting list is printed to
 *   stdout;
 *
 *   the program distinguishes between system include files enclosed
 *   in brackets <...> and custom include files enclosed in quotes
 *   "..." and will search either or both types;
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
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../tree/depend.h"
#include "../scan/scan.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/efopen.c"
#include "../tools/emalloc.c"
#include "../tools/erealloc.c"
#include "../tools/fgetline.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/fullpath.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/partpath.c"
#include "../files/partfile.c"
#include "../files/find.c"
#endif

#ifndef MAKEFILE
#include "../scan/scaninput.c"
#include "../scan/scanstart.c"
#include "../scan/scanuntil.c"
#include "../scan/scanbreak.c"
#include "../scan/scantoken.c"
#include "../scan/scanspace.c"
#include "../scan/scanalnum.c"
#include "../scan/scandigit.c"
#include "../scan/scanflush.c"
#include "../scan/havetoken.c"
#include "../scan/nexttoken.c"
#include "../scan/havebreak.c"
#include "../scan/nextbreak.c"
#include "../scan/tokentext.c"
#include "../scan/istoken.c"
#include "../scan/isbreak.c"
#include "../tree/depend.c"
#endif

#ifndef MAKEFILE
#include "../scan/scaninput.c"
#include "../scan/scanstart.c"
#include "../scan/scanuntil.c"
#include "../scan/scanbreak.c"
#include "../scan/scantoken.c"
#include "../scan/scanspace.c"
#include "../scan/scanflush.c"
#include "../scan/havetoken.c"
#include "../scan/nexttoken.c"
#include "../scan/tokentext.c"
#include "../scan/istoken.c"
#include "../scan/isbreak.c"
#endif

/*====================================================================*
 *  program constants;
 *--------------------------------------------------------------------*/

#define DEP_B_INVERT (1 << 0)
#define DEP_B_REPORT (1 << 1)
#define DEP_B_CUSTOM (1 << 2)
#define DEP_B_SYSTEM (1 << 3)

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

extern LINK * nodelist;
extern TREE * nodetree;
static TREE * pathtree = (TREE *) (0);

/*====================================================================*
 *
 *   void relate (char const *one, char const *two, flag_t flags)
 *
 *   relate file one to file two as indicated by flags;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void relate (char const * one, char const * two, flag_t flags)

{
	if (_anyset (flags, DEP_B_INVERT))
	{
		pathtree = ordernode (pathtree, two, one, strcmp);
	}
	else 
	{
		pathtree = ordernode (pathtree, one, two, strcmp);
	}
	return;
}

/*====================================================================*
 *
 *   void function (char const *pathname, char *buffer, size_t length, flag_t flags);
 *
 *   search the named target file for include files; define relationships
 *   between each target file and the source files that it includes;
 *
 *   relationships are defined as target:source pairs stored in a tree of
 *   trees; each node of the first tree contains one name and the root of
 *   a subordinate tree that contains second names; the trees are used as
 *   lists because 1) they sort as they grow, 2) speed lookup and 3) need
 *   no data movement; we maintain two trees: one for parent-to-child and
 *   another for child-to-parent relationships; all names, whether parent
 *   or child, are stored only once, in a third tree, and the other trees
 *   merely point to the strings stored there; this seems convoluted but
 *   storage is minimized and speed is maximized;
 *
 *   an in-order search of the third tree gives an alphabeical list of all
 *   all filenames; an in-order search of the other two trees, and their
 *   subtrees, gives an alphabetical list of parent-then-child or child-
 *   then-parent relationships;
 *
 *   the needtree tree holds target filenames and the source files included
 *   by each one; the feedtree tree holds source filenames and the target
 *   files that include each one; the nodetree tree stores the master copy
 *   of all filenames, whether target or source, since there are often so
 *   many duplicates; functions that maintain these trees are in tree.c;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (char const * pathname, char * buffer, size_t length, flag_t flags)

{
	FILE * ifp;
	SCAN scan;
	FIND find;
	size_t line;
	if ((ifp = efopen (pathname, "rb")))
	{
		strcpy (find.fullname, pathname);
		partpath (find.fullname, find.pathname, find.filename);
		partfile (find.filename, find.basename, find.extender);
		scaninput (& scan, buffer, length);
		for (line = 0; ~ fgetline (buffer, length, ifp); line++)
		{
			scanstart (& scan);
			nexttoken (& scan);
			if (! havetoken (& scan, "#"))
			{
				continue;
			}
			if (! havetoken (& scan, "include"))
			{
				continue;
			}
			if (havetoken (& scan, "<"))
			{
				if (_anyset (flags, DEP_B_SYSTEM))
				{
					scanuntil (& scan, ">");
					makepath (find.fullname, "/usr/include", tokentext (& scan));
					relate (pathname, find.fullname, flags);
				}
				continue;
			}
			if (havetoken (& scan, "\""))
			{
				if (_anyset (flags, DEP_B_CUSTOM))
				{
					scanuntil (& scan, "\"");
					makepath (find.fullname, find.pathname, tokentext (& scan));
					relate (pathname, find.fullname, flags);
				}
				continue;
			}
		}
		fclose (ifp);
		if (! line)
		{
			error (0, 0, "file %s is empty", pathname);
		}
	}
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
	static char const * optv [] =
	{
		"csnf",
		PUTOPTV_S_FUNNEL,
		"list supporting c language include files on stdout",
		"c\tcustom files",
		"s\tsystem files",
		"n\tneed summary ",
		"f\tfeed summary ",
		(char const *) (0)
	};
	char buffer [TEXTLINE_MAX];
	size_t length = TEXTLINE_MAX;
	flag_t flags = DEP_B_SYSTEM;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'n':
			_setbits (flags, DEP_B_REPORT);
			_clrbits (flags, DEP_B_INVERT);
			break;
		case 'f':
			_setbits (flags, DEP_B_REPORT);
			_setbits (flags, DEP_B_INVERT);
			break;
		case 's':
			_setbits (flags, DEP_B_SYSTEM);
			_clrbits (flags, DEP_B_CUSTOM);
			break;
		case 'c':
			_clrbits (flags, DEP_B_SYSTEM);
			_setbits (flags, DEP_B_CUSTOM);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		error (1, 0, "nothing to analyse");
	}
	while ((argc) && (* argv))
	{
		makepath (buffer, getenv ("PWD"), * argv);
		nodetree = storenode (nodetree, (TREE *) (0), buffer, (void *) (0), strcmp);
		argc--;
		argv++;
	}
	if (nodelist)
	{
		LINK * nodeitem = nodelist;
		do 
		{
			nodeitem = nodeitem->next;
			function (nodeitem->name, buffer, length, flags);
		}
		while (nodeitem != nodelist);
	}
	if (_anyset (flags, DEP_B_REPORT))
	{
		structure (pathtree);
	}
	else 
	{
		enumerate (nodetree);
	}
	exit (0);
}

