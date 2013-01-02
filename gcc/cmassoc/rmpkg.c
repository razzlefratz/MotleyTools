/*====================================================================*
 *
 *   rmpkg.c - remove prior versions of software packages by name; 
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
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../strlib/strlib.h"
#include "../list/list.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/emalloc.c"
#include "../tools/erealloc.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/makefind.c"
#include "../files/partpath.c"
#include "../files/partfile.c"
#include "../files/find.c"
#include "../files/match.c"
#endif

#ifndef MAKEFILE
#include "../list/listcreate.c"
#include "../list/listdelete.c"
#include "../list/listinsert.c"
#include "../list/listdetect.c"
#include "../list/listexpand.c"
#endif

#ifndef MAKEFILE
#include "../strlib/strvercmp.c"
#endif

/*====================================================================*
 *   program functions; 
 *--------------------------------------------------------------------*/

static void findfile (FIND * find, LIST * list, flag_t flags);
static void findfile (FIND * find, LIST * list, flag_t flags);

/*====================================================================*
 *
 *   void function1 (char const *filename, flag_t flags);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function1 (char const *filename, flag_t flags) 

{
	if (flags & FIND_B_TESTRUN) 
	{
		printf ("rm %s\n", filename);
	}
	else if (remove (filename) != 0) 
	{
		error (0, errno, "can't remove %s", filename);
	}
	else if (flags & FIND_B_VERBOSE) 
	{
		printf ("rm %s\n", filename);
	}
	return;
}


/*====================================================================*
 *
 *   void function (LIST *list, flag_t flags);
 *
 *   point to filename in list for later use, copy that string to a 
 *   working buffer for splitting and create a string vector containing longname and separate extensions;
 *
 * compare next and last string vectors element by element until mismatch; mismatch at the first
 * element means a different package; mismatch at other elements means a version difference; we
 * remove the lowest of any two mismatched versions then move on; in principle, files never have
 * the same name so equality checks have been omitted; 
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (LIST * list, flag_t flags) 

{
	struct _part_ 
	{
		struct _part_ *next;
		char const *name;
	}
	one,
	two,
	*this;
	this = &one;
	one.next = &two;
	two.next = &one;
	this->name = list->table [list->index++];
	while (list->index < list->count) 
	{
		char const *sp1;
		char const *sp2;
		this->next->name = list->table [list->index++];

// printf ("[%s][%s]\n", this->name, this->next->name);

		for (sp1 = this->name, sp2 = this->next->name; *sp1 == *sp2; sp1++, sp2++) 
		{
			if (*sp1 == (char) (0)) 
			{
				this->next->name = list->table [list->index++];
				break;
			}
			if (*sp1 == FILE_C_EXTENDER) 
			{
				int order = strvercmp (sp1, sp2, FILE_C_EXTENDER);
				if (order < 0) 
				{
					function1 (this->name, flags);
				}
				if (order > 0) 
				{
					this = this->next;
					function1 (this->name, flags);
				}
				break;
			}
		}
	}
	return;
}


/*====================================================================*
 *
 *   static void testfile (FIND *find, struct_list *list, flag_t flags);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void testfile (FIND * find, LIST * list, flag_t flags) 

{
	if (lstat (find->fullname, &find->statinfo)) 
	{
		error (0, errno, "can't stat %s.", find->fullname);
		return;
	}
	if (S_ISDIR (find->statinfo.st_mode)) 
	{
		char *filename = find->filename;
		if (*filename == '.') 
		{
			filename++;
		}
		if (*filename == '.') 
		{
			filename++;
		}
		if (*filename == (char) (0)) 
		{
			return;
		}
		if (_anyset (find->flagword, FIND_B_RECURSE)) 
		{
			findfile (find, list, flags);
		}
		return;
	}
	if (S_ISREG (find->statinfo.st_mode)) 
	{
		if (match (find->filename, find->wildcard)) 
		{
			listinsert (list, find->fullname);
		}
		return;
	}
	return;
}


/*====================================================================*
 *
 *   static void findfile (FIND *find, struct_list *list, flag_t flags);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void findfile (FIND * find, LIST * list, flag_t flags) 

{
	struct dirent *dirent;
	char *filename = find->fullname;
	DIR *dir = opendir (filename);
	if (dir == (DIR *) (0)) 
	{
		testfile (find, list, flags);
		return;
	}
	while (*filename != (char) (0)) 
	{
		filename++;
	}
	*filename = PATH_C_EXTENDER;
	while ((dirent = readdir (dir)) != (struct dirent *) (0)) 
	{
		strcpy (filename + 1, dirent->d_name);
		partpath (find->fullname, find->pathname, find->filename);
		partfile (find->filename, find->basename, find->extender);
		testfile (find, list, flags);
	}
	*filename = (char) (0);
	closedir (dir);
	return;
}


/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	extern FIND find;
	static char const * optv [] = 
	{
		"crv",
		PUTOPTV_S_SEARCH,
		"remove old versions of software packages based on filename;",
		"c\tcheck but do not remove",
		"r\trecursive search",
		"v\tverbose messages",
		(char const *) (0)
	};
	LIST list;
	flag_t flags = (flag_t) (0);
	int c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'c':
			_setbits (flags, FIND_B_TESTRUN);
			break;
		case 'r':
			_setbits (find.flagword, FIND_B_RECURSE);
			break;
		case 'v':
			_setbits (flags, FIND_B_VERBOSE);
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	listcreate (&list, _LISTSIZE);
	while ((argc) && (* argv)) 
	{
		makefind (&find, * argv);
		strcpy (find.fullname, find.pathname);
		findfile (&find, &list, flags);
		function (&list, flags);
		argc--;
		argv++;
	}
	listdelete (&list);
	exit (0);
}

