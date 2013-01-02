/*====================================================================*
 *
 *   mmf.c -  make a makefile program;
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
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <time.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../files/files.h"
#include "../clang/clang.h"
#include "../strlib/strlib.h"
#include "../list/list.h"

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
#include "../tools/error_on_line.c"
#endif

#ifndef MAKEFILE
#include "../clang/ccollect.c"
#include "../clang/cinclude.c"
#endif

#ifndef MAKEFILE
#include "../strlib/strwcmp.c"
#endif

#ifndef MAKEFILE
#include "../files/setfiletype.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/partpath.c"
#include "../files/partfile.c"
#include "../files/filename.c"
#endif

#ifndef MAKEFILE
#include "../list/listcreate.c"
#include "../list/listdelete.c"
#include "../list/listdetect.c"
#include "../list/listexpand.c"
#include "../list/listinsert.c"
#include "../list/listappend.c"
#include "../list/listload.c"
#include "../list/listsort.c"
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
#include "../scan/havebreak.c"
#include "../scan/nexttoken.c"
#include "../scan/nextbreak.c"
#include "../scan/tokentext.c"
#include "../scan/istoken.c"
#include "../scan/isbreak.c"
#include "../scan/isclass.c"
#endif

#ifndef MAKEFILE
#include "../date/arctime.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define MMF_S_COMPILER "gcc"
#define MMF_S_ARCHIVE ".."
#define MMF_S_PRIVATE "~"
#define MMF_S_CONTROL "~"
#define MMF_S_EXCLUDE "--exclude=.git"
#define MMF_S_PACKAGE "$(shell basename ${PWD})"
#define MMF_B_VERBOSE  (1 << 0)
#define MMF_B_SILENCE  (1 << 1)
#define MMF_B_MAKEFILE (1 << 2)
#define MMF_B_GENERIC_OBJECT  (1 << 3)
#define MMF_B_PROGRAM_BINARY  (1 << 4)
#define MMF_B_PROGRAM_OBJECT  (1 << 5)
#define MMF_B_CONTENT  (1 << 6)
#define MMF_B_FILEMODE (S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH)

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

static char const * headerfiles [] = 

{
	"*.h",
	"*.hpp",
	(char const *)(0)
};

static char const * sourcefiles [] = 

{
	"*.c",
	"*.cpp",
	(char const *)(0)
};

static char const * mask = "?*";
static char const * sourcedir = FILE_S_EXTENDER;
static char const * targetdir = PATH_CMASSOC;

/*====================================================================*
 *
 *   bool member (char const * name, char const * list [], char const * mask);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static bool member (char const * name, char const * list [], char const * mask) 

{
	if (list) while (* list) 
	{
		if (strwcmp (name, *list++, mask)) 
		{
			return (true);
		}
	}
	return (false);
}


/*====================================================================*
 *
 *   void listoutput (LIST * list, char const * target);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void listoutput (LIST * list, char const * target) 

{
	printf ("%s:", target);
	for (list->index = list->start; list->index < list->count; list->index++) 
	{
		printf (" %s", list->table [list->index]);
	}
	printf ("\n");
	return;
}


/*====================================================================*
 *
 *   void compile (char * target, char const * source);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void compile (char * target, char const * source) 

{
	LIST list;
	LIST name;
	char const * paths [] = 
	{
		"",
		(char const *)(0)
	};
	listcreate (&list, _LISTSIZE);
	listappend (&list, source);
	if (cinclude (&list, paths)) 
	{
		error (0, 0, "target %s is missing %d files.", list.table [0], list.error);
	}
	listcreate (&name, _LISTSIZE);
	listappend (&name, filename (source));
	name.start++;
	for (list.index = list.start + 1; list.index < list.count; list.index++) 
	{
		listinsert (&name, filename (list.table [list.index]));
	}
	name.start--;
	strcpy (target, filename (source));
	setfiletype (target, ".o");
	listoutput (&name, target);
	listdelete (&name);
	listdelete (&list);
	return;
}


/*====================================================================*
 *
 *   void include (char * target, char const * source);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void include (char * target, char const * source) 

{
	LIST list;
	LIST name;
	char const * paths [] = 
	{
		"",
		(char const *)(0)
	};
	listcreate (&list, _LISTSIZE);
	listappend (&list, source);
	if (cinclude (&list, paths)) 
	{
		error (0, 0, "target %s is missing %d files.", list.table [0], list.error);
	}
	if (list.count > 1) 
	{
		listcreate (&name, _LISTSIZE);
		for (list.index = list.start + 1; list.index < list.count; list.index++) 
		{
			listinsert (&name, filename (list.table [list.index]));
		}
		strcpy (target, filename (source));
		listoutput (&name, target);
		listdelete (&name);
	}
	listdelete (&list);
	return;
}


/*====================================================================*
 *
 *   void program_binary (char * target, char const * source, char const * ignore [], char const * mask)
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void program_binary (char * target, char const * source, char const * ignore [], char const * mask) 

{
	LIST list;
	LIST name;
	char const * paths [] = 
	{
		"",
		(char const *)(0)
	};
	listcreate (&list, _LISTSIZE);
	listappend (&list, source);
	if (cinclude (&list, paths)) 
	{
		error (0, 0, "target %s is missing %d files.", list.table [0], list.error);
	}
	listcreate (&name, _LISTSIZE);
	strcpy (target, filename (source));
	setfiletype (target, ".o");
	listappend (&name, target);
	name.start++;
	for (list.index = list.start + 1; list.index < list.count; list.index++) 
	{
		strcpy (target, filename (list.table [list.index]));
		if (!member (target, ignore, mask)) 
		{
			setfiletype (target, ".o");
			listinsert (&name, target);
		}
	}
	name.start--;
	strcpy (target, filename (source));
	setfiletype (target, "");
	listoutput (&name, target);
	listdelete (&name);
	listdelete (&list);
	return;
}


/*====================================================================*
 *
 *   void program_object (char * target, char const * source, char const * ignore [], char const * mask)
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void program_object (char * target, char const * source, char const * ignore [], char const * mask) 

{
	LIST list;
	LIST name;
	char const * paths [] = 
	{
		"",
		(char const *)(0)
	};
	listcreate (&list, _LISTSIZE);
	listappend (&list, source);
	if (cinclude (&list, paths)) 
	{
		error (0, 0, "target %s is missing %d files.", list.table [0], list.error);
	}
	listcreate (&name, _LISTSIZE);
	strcpy (target, filename (source));
	listappend (&name, target);
	name.start++;
	for (list.index = list.start + 1; list.index < list.count; list.index++) 
	{
		strcpy (target, filename (list.table [list.index]));
		if (!member (target, ignore, mask)) 
		{
			listinsert (&name, target);
		}
	}
	name.start--;
	strcpy (target, filename (source));
	setfiletype (target, ".o");
	listoutput (&name, target);
	listdelete (&name);
	listdelete (&list);
	return;
}


/*====================================================================*
 *
 *   void content (char * target, char const * source);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void content (char * target, char const * source) 

{
	LIST list;
	char const * paths [] = 
	{
		"",
		(char const *)(0)
	};
	listcreate (&list, _LISTSIZE);
	listappend (&list, source);
	if (ccollect (&list, paths)) 
	{
		error (0, 0, "target %s is missing %d files.", list.table [0], list.error);
	}
	list.start++;
	listsort (&list);
	list.start--;
	for (list.index = list.start; list.index < list.count; list.index++) 
	{
		printf ("%s\n", list.table [list.index]);
	}
	listdelete (&list);
	return;
}


/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"c:ef:imop",
		"source-file [source-file] ...",
		"create makefile for c source files",
		"e\ttargets are program binary files",
		"f s\tread target files from file (s)",
		"i\toutput is an inventory",
		"m\toutput a makefile",
		"o\ttargets are general object files",
		"p\ttargets are program object files",
		(char const *)(0)
	};
	flag_t flags = (flag_t) (0);
	time_t now = time ((time_t *)(0));
	char string [TEXTLINE_MAX << 1];
	char target [FILENAME_MAX] = "";
	char topbar [BARWIDTH_MAX + 1] = 
	{
		0
	};
	char botbar [BARWIDTH_MAX + 1] = 
	{
		0
	};
	LIST targets;
	LIST sources;
	signed c;
	memset (topbar, '=', sizeof (topbar) - 1);
	memset (botbar, '-', sizeof (botbar) - 1);
	listcreate (&targets, _LISTSIZE);
	listcreate (&sources, _LISTSIZE);
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'f':
			listload (&targets, optarg, string, sizeof (string));
			break;
		case 'i':
			_setbits (flags, MMF_B_CONTENT);
			break;
		case 'm':
			_setbits (flags, MMF_B_MAKEFILE);
			break;
		case 'o':
			_setbits (flags, MMF_B_GENERIC_OBJECT);
			break;
		case 'p':
			_setbits (flags, MMF_B_PROGRAM_OBJECT);
			break;
		case 'e':
			_setbits (flags, MMF_B_PROGRAM_BINARY);
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	while ((argc) && (* argv)) 
	{
		listinsert (&targets, * argv);
		argc--;
		argv++;
	}
	if (_anyset (flags, MMF_B_MAKEFILE)) 
	{
		printf ("#!/usr/bin/make -f\n");
		strftime (string, sizeof (string), "Published %Y by Charles Maier for personal use;", localtime (&now));
		printf ("# %s\n", string);

#if 1

		printf ("\n# %s\n# symbols;\n# %s\n\n", topbar, botbar);
		printf ("ARCHIVE=%s\n", MMF_S_ARCHIVE);
		printf ("PRIVATE=%s\n", MMF_S_PRIVATE);
		printf ("CONTROL=%s\n", MMF_S_CONTROL);
		printf ("EXCLUDE=%s\n", MMF_S_EXCLUDE);
		printf ("PACKAGE=%s\n", MMF_S_PACKAGE);
		printf ("CC=gcc\n");
		printf ("INSTALL=install\n");
		printf ("SRC=%s\n", sourcedir);
		printf ("BIN=%s\n", targetdir);
		printf ("CFLAGS=-Wall -DMAKEFILE\n");
		printf ("LFLAGS=\n");
		printf ("TRASH=*~ *.o t t.* *.[0-9][0-9][0-9]\n");
		printf ("TOOLS=");
		for (targets.index = targets.start; targets.index < targets.count; targets.index++) 
		{
			strcpy (target, filename (targets.table [targets.index]));
			setfiletype (target, "");
			printf ("%s ", target);
		}
		printf ("\n");

#endif
#if 1

		printf ("\n# %s\n# targets;\n# %s\n\n", topbar, botbar);
		printf (".PHONY: compile library scripts manuals install uninstall archive clean fresh\n");
		printf ("compile: ${TOOLS}\n");
		printf ("library:\n#\t${INSTALL} -m 0755 -o root -g root -d ${BIN}\n");
		printf ("scripts:\n");
		printf ("manuals:\n");
		printf ("install: compile\n#\t${INSTALL} -m 0755 -o root -g root -s ${TOOLS} ${BIN}\n");
		printf ("uninstall:\n#\tcd ${BIN}; rm -f ${TOOLS}\n");
		printf ("clean:\n\trm -f ${TRASH}\n");
		printf ("fresh: clean compile\n");

#endif
#if 1

		printf ("\n# %s\n# objects;\n# %s\n\n", topbar, botbar);
		printf ("nightly: clean\n");
		printf ("\tif [ -d ${ARCHIVE} ]; then tar ${EXCLUDE} -vzcf ${ARCHIVE}/$$(date +%%y%%m%%d-%%H%%M%%S).tar.gz  -C .. ${PACKAGE}; fi\n");
		printf ("\tif [ -d ${PRIVATE} ]; then tar ${EXCLUDE} -vzcf ${PRIVATE}/$$(date +%%y%%m%%d-%%H%%M%%S).tar.gz  -C .. ${PACKAGE}; fi\n");
		printf ("snapshot: clean\n");
		printf ("\tif [ -d ${ARCHIVE} ]; then tar ${EXCLUDE} -vzcf ${ARCHIVE}/$$(stamp).tar.gz  -C .. ${PACKAGE}; fi\n");
		printf ("\tif [ -d ${PRIVATE} ]; then tar ${EXCLUDE} -vzcf ${PRIVATE}/$$(stamp).tar.gz  -C .. ${PACKAGE}; fi\n");
		printf ("archive: clean\n");
		printf ("\tif [ -d ${ARCHIVE} ]; then tar ${EXCLUDE} -vjcf ${ARCHIVE}/${PACKAGE}.tar.bz2 -C .. ${PACKAGE}; fi\n");
		printf ("\tif [ -d ${ARCHIVE} ]; then tar ${EXCLUDE} -vzcf ${ARCHIVE}/${PACKAGE}.tar.gz  -C .. ${PACKAGE}; fi \n");
		printf ("private: clean\n");
		printf ("\tif [ -d ${PRIVATE} ]; then tar ${EXCLUDE} -vjcf ${PRIVATE}/${PACKAGE}.tar.bz2 -C .. ${PACKAGE}; fi\n");
		printf ("\tif [ -d ${PRIVATE} ]; then tar ${EXCLUDE} -vzcf ${PRIVATE}/${PACKAGE}.tar.gz  -C .. ${PACKAGE}; fi\n");
		printf ("control:\n");
		printf ("\tif [ -d ${CONTROL} ]; then tar ${EXCLUDE} -vjcf ${CONTROL}/${PACKAGE}.tar.bz2 -C .. ${PACKAGE}; fi \n");
		printf ("\tif [ -d ${CONTROL} ]; then tar ${EXCLUDE} -vzcf ${CONTROL}/${PACKAGE}.tar.gz  -C .. ${PACKAGE}; fi\n");

#endif
#if 1

		printf ("\n# %s\n# objects;\n# %s\n\n", topbar, botbar);
		printf ("%%.c: %%.o:\n\t${CC} -c ${<} ${CFLAGS}\n");
		printf ("%%.o:\n\t${CC} -o ${@} ${^} ${LFLAGS}\n");
		printf ("\n");

#endif

	}
	else if (_anyset (flags, MMF_B_PROGRAM_BINARY)) 
	{
		for (targets.index = targets.start; targets.index < targets.count; targets.index++) 
		{
			program_binary (target, targets.table [targets.index], headerfiles, mask);
		}
	}
	else if (_anyset (flags, MMF_B_PROGRAM_OBJECT)) 
	{
		for (targets.index = targets.start; targets.index < targets.count; targets.index++) 
		{
			program_object (target, targets.table [targets.index], sourcefiles, mask);
		}
	}
	else if (_anyset (flags, MMF_B_GENERIC_OBJECT)) 
	{
		for (targets.index = targets.start; targets.index < targets.count; targets.index++) 
		{
			char const * source = targets.table [targets.index];
			if (member (source, sourcefiles, mask)) 
			{
				compile (target, source);
				continue;
			}
			if (member (source, headerfiles, mask)) 
			{
				include (target, source);
				continue;
			}
			error (0, EINVAL, "%s", source);
		}
	}
	else if (_anyset (flags, MMF_B_CONTENT)) 
	{
		for (targets.index = targets.start; targets.index < targets.count; targets.index++) 
		{
			content (target, targets.table [targets.index]);
		}
	}
	printf ("\n");
	listdelete (&targets);
	listdelete (&sources);
	fchmod (STDOUT_FILENO, MMF_B_FILEMODE);
	exit (0);
}

