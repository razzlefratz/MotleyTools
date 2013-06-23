/*====================================================================*
 *
 *   remove.c - remove selected records from a file;
 *
 *   this program is similar to the UNIX grep utility;
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
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../files/files.h"
#include "../regex/regex.h"
#include "../chrlib/chrlib.h"
#include "../strlib/strlib.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/emalloc.c"
#include "../tools/fgetline.c"
#include "../tools/fputline.c"
#include "../tools/todigit.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

#ifndef MAKEFILE
#include "../regex/regexmake.c"
#include "../regex/regexspan.c"
#include "../regex/regexcomp.c"
#include "../regex/regexfree.c"
#include "../regex/regexhelp.c"
#include "../regex/regexshow.c"
#endif

#ifndef MAKEFILE
#include "../strlib/struesc.c"
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

#define REMOVE_B_HEADER (1 << 0)
#define REMOVE_B_NUMBER (1 << 1)
#define REMOVE_B_RECORD (1 << 2)
#define REMOVE_B_INVERT (1 << 3)
#define REMOVE_B_REPORT (1 << 4)
#define REMOVE_B_REVIEW (1 << 5)

/*====================================================================*
 *
 *   void function (char const * filename, regexp *remove[], size_t length, flag_t flags)
 *
 *   copy lines from stdin to stdout; exclude lines that match any
 *   of several regular expression; 
 *
 *      #define REMOVE_B_HEADER  0x0001  (show file name)
 *      #define REMOVE_B_NUMBER  0x0002  (show file line)
 *      #define REMOVE_B_RECORD  0x0004
 *      #define REMOVE_B_INVERT  0x0008  (delete matching lines)
 *
 *   if bit field REMOVE_B_HEADER is set, the input filename is output to
 *   separate record groups; otherwise, records appear as a continuous
 *   list of lines;
 *
 *   if bit field REMOVE_B_NUMBER is set, output lines are numbered by file
 *   position; otherwise, numbers are not displayed.
 *
 *   if bit field REMOVE_B_RECORD is set, the qualifying lines are output as
 *   records; this is the default but output can be suppressed;
 *
 *   if bit field REMOVE_B_INVERT is set, input lines that do not match any
 *   list item are output; otherwise, lines match any list are output;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (char const * filename, regexp * list [], size_t size, char buffer [], size_t length, flag_t flags) 

{
	unsigned line;
	unsigned removed = 0;
	for (line = 1; fgetline (buffer, length, stdin) != -1; line++) 
	{
		size_t item;
		for (item = 0; item < size; item++) 
		{
			char const * cp = regexspan (list [item], buffer);
			if (cp) 
			{
				if (* cp == (char) (0)) 
				{
					break;
				}
			}
		}
		if (!(flags & (REMOVE_B_INVERT)) != (item < size)) 
		{
			fputline (buffer, length, stdout);
		}
		else 
		{
			removed++;
		}
	}
	if (removed > 0) 
	{
		if (flags & (REMOVE_B_HEADER)) 
		{
			if (flags & (REMOVE_B_NUMBER)) 
			{
				fprintf (stderr, "%3u ", removed);
			}
			fprintf (stderr, "%s\n", filename);
		}
	}
	return;
}

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	extern const unsigned char ct_unescape [];
	static char const * optv [] = 
	{
		"e:fHl:nRTv",
		PUTOPTV_S_FILTER,
		"remove lines that match any of several regular expressions",
		"e e\texpression (e) anywhere on line as in \".*{e}.*\"",
		"f\tdisplay filename only",
		"H\tview expression expansion",
		"l e\texpression (e) is complete line as in \"^{e}$\"",
		"n\tdisplay line numbers",
		"R\tregular expression rules",
		"T\tescape sequence rules",
		"v\texclude matching lines",
		(char const *) (0)
	};
	regexp * remove [_LISTSIZE] = 
	{
		(regexp *) (0)
	};
	char buffer [TEXTLINE_MAX] = 
	{
		(char) (0)
	};
	size_t size = 0;
	size_t item = 0;
	flag_t flags = REMOVE_B_RECORD;
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'n':
			_setbits (flags, REMOVE_B_HEADER);
			_setbits (flags, REMOVE_B_NUMBER);
			_setbits (flags, REMOVE_B_RECORD);
			break;
		case 'f':
			_setbits (flags, REMOVE_B_HEADER);
			_clrbits (flags, REMOVE_B_NUMBER);
			_clrbits (flags, REMOVE_B_RECORD);
			break;
		case 'l':
			strcpy (buffer, struesc ((char *)(optarg)));
			remove [size++] = regexmake (buffer);
			remove [size] = (regexp *) (0);
			break;
		case 'e':
			strcpy (buffer, REGEX_S_SPAN);
			strcat (buffer, struesc ((char *)(optarg)));
			strcat (buffer, REGEX_S_SPAN);
			remove [size++] = regexmake (buffer);
			remove [size] = (regexp *) (0);
			break;
		case 'v':
			_setbits (flags, REMOVE_B_INVERT);
			break;
		case 'r':
			_setbits (flags, FIND_B_RECURSE);
			break;
		case 't':
			_setbits (flags, FIND_B_TRAVERSE);
			break;
		case 'H':
			_setbits (flags, REMOVE_B_REVIEW);
			break;
		case 'R':
			regexhelp ();
			exit (0);
		case 'T':
			chruescmap (ct_unescape, REGEX_C_ESC);
			exit (0);
		default:
			exit (1);
		}
	}
	argc-= optind;
	argv+= optind;
	if (flags & (REMOVE_B_REVIEW)) 
	{
		for (item = 0; item < size; item++) 
		{
			regexshow (remove [item]);
		}
		exit (0);
	}
	if (!argc) 
	{
		function ("stdin", remove, size, buffer, sizeof (buffer), flags);
	}
	while ((argc) && (* argv)) 
	{
		if (vfopen (* argv)) 
		{
			function (* argv, remove, size, buffer, sizeof (buffer), flags);
		}
		argc--;
		argv++;
	}
	exit (0);
}

