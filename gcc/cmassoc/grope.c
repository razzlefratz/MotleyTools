/*====================================================================*
 *
 *   grope.c - extract and print regular expression substrings;
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

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/fgetline.c"
#include "../tools/efreopen.c"
#include "../tools/emalloc.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/fputn.c"
#endif

#ifndef MAKEFILE
#include "../regex/regexmake.c"
#include "../regex/regexspan.c"
#include "../regex/regexcomp.c"
#include "../regex/regexhelp.c"
#include "../regex/regexfree.c"
#include "../regex/regexshow.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/match.c"
#include "../files/makepath.c"
#include "../files/partpath.c"
#include "../files/partfile.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/find.c"
#include "../files/makefind.c"
#endif

#ifndef MAKEFILE
#include "../strlib/struesc.c"
#endif

#ifndef MAKEFILE
#include "../chrlib/charset.c"
#include "../chrlib/chruesc.c"
#include "../chrlib/chruescmap.c"
#endif

#ifndef MAKEFILE
#include "../sv/sv_ascii.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define GROPE_B_RECORD (1 << 0)
#define GROPE_B_NUMBER (1 << 1)
#define GROPE_B_HEADER (1 << 2)
#define GROPE_B_INVERT (1 << 3)
#define GROPE_B_REVIEW (1 << 4)

#define RADIX 10
#define FIELD 6

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

static void findfile(FIND * find, EDIT * edit, flag_t flags);
static void testfile(FIND * find, EDIT * edit, flag_t flags);

/*====================================================================*
 *
 *   void editfile (FIND *find, EDIT *edit, flag_t flags);
 *
 *   selectively copy lines from stdin to stdout based on the regular
 *   expressions list and bits set within the mode flag.
 *
 *      #define GROPE_B_HEADER  0x0004  (show file name)
 *      #define GROPE_B_NUMBER  0x0002  (show file line)
 *      #define GROPE_B_RECORD  0x0001
 *      #define GROPE_B_INVERT  0x0008  (delete matching lines)
 *
 *   if bit field GROPE_B_HEADER is set, the input filename is output 
 *   at the start of each record group; otherwise, records appear as 
 *   a continuous list of lines;
 *
 *   if bit field GROPE_B_NUMBER is set, output lines are numbered by 
 *   file position; otherwise, numbers are not displayed.
 *
 *   if bit field GROPE_B_RECORD is set, qualifying lines are output 
 *   as records; this is the default but output can be suppressed;
 *
 *   if bit field GROPE_B_INVERT is set, input lines that do not match 
 *   any list item are output; otherwise, lines match any list are 
 *   output;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void editfile(FIND * find, EDIT * edit, flag_t flags)

{
	size_t line = 0;
	size_t item = 0;
	size_t once = 0;
	for (line = 1; fgetline(edit->buffer, edit->length, stdin) != - 1; line++)
	{
		for (item = 0; item < edit->size; item++)
		{
			char const * sp;
			for (sp = edit->buffer; * sp; sp++)
			{
				char const * cp;
				if ((cp = regexspan(edit->list[item], sp)))
				{
					if (! once)
					{
						if (flags & GROPE_B_HEADER)
						{
							if (flags & GROPE_B_NUMBER)
							{
								fputn (NONE, RADIX, FIELD, stdout);
								fputc (' ', stdout);
							}
							fputs (find->fullname, stdout);
							fputc ('\n', stdout);
							once = 1;
						}
					}
					if (flags & GROPE_B_RECORD)
					{
						if (flags & GROPE_B_NUMBER)
						{
							fputn (line, RADIX, FIELD, stdout);
							fputc (' ', stdout);
						}
						while (sp < cp)
						{
							fputc (* sp++, stdout);
						}
						fputc ('\n', stdout);
						sp--;
					}
				}
			}
		}
	}
	if (once)
	{
		if (flags & GROPE_B_RECORD)
		{
			fputc ('\n', stdout);
		}
	}
	return;
}

/*====================================================================*
 *
 *   void openfile (FIND * find, EDIT * edit, flag_t flags);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void openfile(FIND * find, EDIT * edit, flag_t flags)

{
	if (! match(find->filename, find->wildcard))
	{
		return;
	}
	if (! freopen(find->fullname, "rb", stdin))
	{
		return;
	}
	editfile (find, edit, flags);
	return;
}

/*====================================================================*
 *
 *   void testfile (FIND * find, EDIT * edit, flag_t flags);
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
		if (_anyset(find->flagword, FIND_B_DIR))
		{
			openfile (find, edit, flags);
		}
		if (_anyset(find->flagword, FIND_B_RECURSE))
		{
			findfile (find, edit, flags);
		}
		return;
	}
	if (S_ISLNK(find->statinfo.st_mode))
	{
		if (_anyset(find->flagword, FIND_B_LNK))
		{
			openfile (find, edit, flags);
		}
		return;
	}
	if (S_ISREG(find->statinfo.st_mode))
	{
		if (_anyset(find->flagword, FIND_B_REG))
		{
			openfile (find, edit, flags);
		}
		return;
	}
	return;
}

/*====================================================================*
 *
 *   void findfile (FIND * find, EDIT * edit, flag_t flags);
 *
 *   if find is a folder then search it; otherwise, test it;
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
		while (* filename != (char)(0))
		{
			filename++;
		}
		* filename = PATH_C_EXTENDER;
		while ((dirent = readdir(dir)) != (struct dirent *)(0))
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
 *   main program;
 *--------------------------------------------------------------------*/

int main(int argc, char const * argv[])

{
	extern const unsigned char ct_unescape[];
	extern FIND find;
	static char const * optv[] = 
	{
		"w:e:fnHrRT",
		PUTOPTV_S_FUNNEL,
		"extract and print regular expression substrings",
		"w n\tmaximum line width is n [1024] ",
		"e s\texpression (s) anywhere on line \".*(s).*\"",
		"f\tdisplay filename only",
		"n\tdisplay line numbers",
		"r\trecursive search",
		"H\treview expression expansion",
		"R\tregular expression rules",
		"T\tescape sequence rules",
		(char const *) (0)
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
	flag_t flags = GROPE_B_RECORD;
	signed c;
	while (~ (c = getoptv(argc, argv, optv)))
	{
		switch (c)
		{
		case 'n':
			_setbits (flags, GROPE_B_HEADER);
			_setbits (flags, GROPE_B_RECORD);
			_setbits (flags, GROPE_B_NUMBER);
			break;
		case 'f':
			_setbits (flags, GROPE_B_HEADER);
			_clrbits (flags, GROPE_B_RECORD);
			_clrbits (flags, GROPE_B_NUMBER);
			break;
		case 'e':
			strcpy (edit.buffer, struesc((char *)(optarg)));
			edit.list[edit.size++] = regexmake(edit.buffer);
			edit.list[edit.size] = (regexp *)(0);
			break;
		case 'w':
			edit.length = uintspec(optarg, 1, SHRT_MAX);
			break;
		case 'r':
			_setbits (find.flagword, FIND_B_RECURSE);
			break;
		case 'R':
			regexhelp ();
			exit (0);
		case 'H':
			_setbits (flags, GROPE_B_REVIEW);
			break;
		case 'T':
			chruescmap (ct_unescape, REGEX_C_ESC);
			exit (0);
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (_allclr(find.flagword, FIND_B_REG | FIND_B_LNK))
	{
		_setbits (find.flagword, FIND_B_REG | FIND_B_LNK);
	}
	if (flags & (GROPE_B_REVIEW))
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

