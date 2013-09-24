/*====================================================================*
 *
 *   search.c -	select (or delete) records by pattern;
 *
 *   this program is similar to	the UNIX grep utility;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#define	_GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../files/files.h"
#include "../regex/regex.h"
#include "../strlib/strlib.h"
#include "../chrlib/chrlib.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef	MAKEFILE
#include "../tools/console.c"
#include "../tools/fgetline.c"
#include "../tools/efreopen.c"
#include "../tools/emalloc.c"
#include "../tools/fputn.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#endif

#ifndef	MAKEFILE
#include "../regex/regexmake.c"
#include "../regex/regexspan.c"
#include "../regex/regexcomp.c"
#include "../regex/regexhelp.c"
#include "../regex/regexfree.c"
#include "../regex/regexshow.c"
#endif

#ifndef	MAKEFILE
#include "../files/match.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/makefind.c"
#include "../files/showfind.c"
#include "../files/partpath.c"
#include "../files/partfile.c"
#include "../files/find.c"
#endif

#ifndef	MAKEFILE
#include "../strlib/struesc.c"
#include "../chrlib/charset.c"
#include "../chrlib/chruesc.c"
#include "../chrlib/chruescmap.c"
#endif

#ifndef	MAKEFILE
#include "../sv/sv_ascii.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define	SEARCH_B_HEADER	(1 << 0)
#define	SEARCH_B_NUMBER	(1 << 1)
#define	SEARCH_B_RECORD	(1 << 2)
#define	SEARCH_B_INVERT	(1 << 3)
#define	SEARCH_B_REPORT	(1 << 4)
#define	SEARCH_B_SEARCH	(1 << 5)
#define	SEARCH_B_REVIEW	(1 << 6)
#define	RADIX 10
#define	FIELD 6

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

typedef struct _edit_

{
	regexp * list[_LISTSIZE];
	size_t size;
	char buffer[TEXTLINE_MAX];
	size_t length;
}

EDIT;

/*====================================================================*
 *   program functions;
 *--------------------------------------------------------------------*/

static void openfile(FIND * find, EDIT * edit, flag_t flags);
static void editfile(FIND * find, EDIT * edit, flag_t flags);
static void testfile(FIND * find, EDIT * edit, flag_t flags);
static void findfile(FIND * find, EDIT * edit, flag_t flags);

/*====================================================================*
 *
 *   void editfile (FIND * find, EDIT *	edit, flag_t flags);
 *
 *   selectively copy lines from stdin to stdout based on
 *   the regular expressions list and bits set within the mode flags.
 *
 *	#define	SEARCH_B_HEADER	 0x0001	 (show file name)
 *	#define	SEARCH_B_NUMBER	 0x0002	 (show file line)
 *	#define	SEARCH_B_RECORD	 0x0004
 *	#define	SEARCH_B_INVERT	 0x0008	 (delete matching lines)
 *
 *   if	bit field SEARCH_B_HEADER is set, the input filename is	output to
 *   separate record groups; otherwise,	records	appear as a continuous
 *   list of lines;
 *
 *   if	bit field SEARCH_B_NUMBER is set, output lines are numbered by file
 *   position; otherwise, numbers are not displayed.
 *
 *   if	bit field SEARCH_B_RECORD is set, the qualifying lines are output as
 *   records; this is the default but output can be suppressed;
 *
 *   if	bit field SEARCH_B_INVERT is set, input	lines that do not match	any
 *   list item are output; otherwise, lines match any list are output;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void editfile(FIND * find, EDIT * edit, flag_t flags)

{
	size_t line;
	size_t item;
	size_t once = 0;
	for (line = 1; fgetline(edit->buffer, edit->length, stdin) != - 1; line++)
	{
		for (item = 0; item < edit->size; item++)
		{
			char const * cp = regexspan(edit->list[item], edit->buffer);
			if (cp != (char *)(0))
			{
				if (* cp == (char)(0))
				{
					break;
				}
			}
		}
		if (! (flags & (SEARCH_B_INVERT)) == (item < edit->size))
		{
			if (! once)
			{
				if (flags & (SEARCH_B_HEADER))
				{
					if (flags & (SEARCH_B_NUMBER))
					{
						fputn (NONE, RADIX, FIELD, stdout);
						fputc (' ', stdout);
					}
					fputs (find->fullname, stdout);
					fputc ('\n', stdout);
					if ((flags & SEARCH_B_RECORD) == 0)
					{
						break;
					}
					once = 1;
				}
			}
			if (flags & (SEARCH_B_RECORD))
			{
				if (flags & (SEARCH_B_NUMBER))
				{
					fputn (line, RADIX, FIELD, stdout);
					fputc (' ', stdout);
				}
				fputs (edit->buffer, stdout);
				fputc ('\n', stdout);
			}
		}
	}
	if (once)
	{
		if (flags & (SEARCH_B_RECORD))
		{
			fputc ('\n', stdout);
		}
	}
	return;
}

/*====================================================================*
 *
 *   void openfile (FIND * find, EDIT *	edit, flag_t flags);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void openfile(FIND * find, EDIT * edit, flag_t flags)

{
	if (match(find->filename, find->wildcard))
	{
		if (freopen(find->fullname, "rb", stdin))
		{
			editfile (find, edit, flags);
			return;
		}
	}
	return;
}

/*====================================================================*
 *
 *   void testfile (FIND * find, EDIT *	edit, flag_t flags);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void testfile(FIND * find, EDIT * edit, flag_t flags)

{
	if (lstat(find->fullname, & find->statinfo))
	{
		error (0, errno, "%s", find->fullname);
		return;
	}
	if (S_ISDIR(find->statinfo.st_mode))
	{
		char const * filename = find->filename;
		if (* filename == '.')
		{
			filename++;
		}
		if (* filename == '.')
		{
			filename++;
		}
		if (* filename == (char)(0))
		{
			return;
		}
		if (_anyset(find->flagword, FIND_B_RECURSE))
		{
			findfile (find, edit, flags);
		}
		return;
	}
	if (S_ISLNK(find->statinfo.st_mode))
	{
		if (_anyset(find->flagword, FIND_B_TRAVERSE))
		{
			openfile (find, edit, flags);
		}
		return;
	}
	if (S_ISREG(find->statinfo.st_mode))
	{
		openfile (find, edit, flags);
		return;
	}
	return;
}

/*====================================================================*
 *
 *   void findfile (FIND * find, EDIT *	edit, flag_t flags);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void findfile(FIND * find, EDIT * edit, flag_t flags)

{
	DIR * dir;
	char * filename = find->fullname;
	if ((dir = opendir(filename)))
	{
		struct dirent * dirent;
		while (* filename)
		{
			filename++;
		}
		* filename = PATH_C_EXTENDER;
		while ((dirent = readdir(dir)))
		{
			strcpy (filename +  1, dirent->d_name);
			partpath (find->fullname, find->pathname, find->filename);
			partfile (find->filename, find->basename, find->extender);
			testfile (find, edit, flags);
		}
		* filename = (char)(0);
		closedir (dir);
		return;
	}
	testfile (find, edit, flags);
	return;
}

/*====================================================================*
 *   
 *    int main (int argc, const	char * argv[]);
 *   
 *    th use of	".*(s).* here is opposite of that needed by search;
 *
 *.  Motley Tools by Charles Maier;
 *;  Licensed under the Internet Software Consortium License;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *   
 *--------------------------------------------------------------------*/

int main(int argc, char const * argv[])

{
	extern const unsigned char ct_unescape[];
	extern FIND find;
	static char const * optv[] = 
	{
		"e:fHl:nrRtTv",
		PUTOPTV_S_FUNNEL,
		"output lines matching any of several regular expressions",
		"e e\texpression (e) can be anywhere on line as in \".*{e}.*\"",
		"f\tprint filenames only",
		"H\treview expression expansion",
		"l e\texpression (e) describes entire line as in \"^{e}$\"",
		"n\tdisplay line numbers",
		"r\trecursive folder search",
		"R\tregular expression rules",
		"t\ttraverse file links",
		"T\tescape sequence rules",
		"v\tinvert selection",
		(char const *)(0)
	};
	EDIT edit = 
	{
		{
			(regexp *)(0)
		},
		(size_t)(0),
		"",
		sizeof (edit.buffer)
	};
	flag_t flags = SEARCH_B_RECORD;
	signed c;
	while (~ (c = getoptv(argc, argv, optv)))
	{
		switch (c)
		{
		case 'n':
			_setbits (flags, SEARCH_B_HEADER);
			_setbits (flags, SEARCH_B_NUMBER);
			_setbits (flags, SEARCH_B_RECORD);
			break;
		case 'f':
			_setbits (flags, SEARCH_B_HEADER);
			_clrbits (flags, SEARCH_B_NUMBER);
			_clrbits (flags, SEARCH_B_RECORD);
			break;
		case 'l':
			strcpy (edit.buffer, struesc((char *)(optarg)));
			edit.list[edit.size++] = regexmake(edit.buffer);
			edit.list[edit.size] = (regexp *)(0);
			break;
		case 'e':
			strcpy (edit.buffer, REGEX_S_SPAN);
			strcat (edit.buffer, struesc((char *)(optarg)));
			strcat (edit.buffer, REGEX_S_SPAN);
			edit.list[edit.size++] = regexmake(edit.buffer);
			edit.list[edit.size] = (regexp *)(0);
			break;
		case 'r':
			_setbits (find.flagword, FIND_B_RECURSE);
			break;
		case 't':
			_setbits (find.flagword, FIND_B_TRAVERSE);
			break;
		case 'v':
			_setbits (flags, SEARCH_B_INVERT);
			break;
		case 'H':
			_setbits (flags, SEARCH_B_REVIEW);
			break;
		case 'R':
			regexhelp ();
			exit (0);
		case 'T':
			chruescmap (ct_unescape, REGEX_C_ESC);
			exit (0);
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (flags & (SEARCH_B_REVIEW))
	{
		for (edit.size = 0; edit.list[edit.size]; edit.size++)
		{
			regexshow (edit.list[edit.size]);
		}
		exit (0);
	}
	if (! argc)
	{
		editfile (& find, & edit, flags);
	}
	while ((argc) && (* argv))
	{
		makefind (& find, * argv);
		findfile (& find, & edit, flags);
		argc--;
		argv++;
	}
	exit (0);
}

