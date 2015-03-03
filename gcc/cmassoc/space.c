/*====================================================================*
 *
 *   space.c - white space minimizer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../strlib/strlib.h"
#include "../chrlib/chrlib.h"
#include "../clang/clang.h"
#include "../tidy/tidy.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/todigit.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

#ifndef MAKEFILE
#include "../tidy/literal.c"
#include "../tidy/escaped.c"
#include "../tidy/span.c"
#include "../tidy/keep.c"
#include "../tidy/skip.c"
#endif

#ifndef MAKEFILE
#include "../strlib/struesc.c"
#endif

#ifndef MAKEFILE
#include "../chrlib/chruesc.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define SPACE_NEWLINE CLANG_HT
#define SPACE_ENDLINE CLANG_NUL

/*====================================================================*
 *
 *   signed trimm (signed c, unsigned tabstop);
 *
 *   replace inline tabs with spaces; discard trailing tabs and 
 *   spaces;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static signed trimm (signed c, unsigned tabstop)

{
	unsigned column = 0;
	unsigned length = 0;
	while (c != EOF)
	{
		if (c == '\n')
		{
			column = 0;
			length = 0;
		}
		if (c == ' ')
		{
			c = getc (stdin);
			length++;
			continue;
		}
		if (c == '\t')
		{
			c = getc (stdin);
			length += tabstop - length % tabstop;
			continue;
		}
		while (column++ < length)
		{
			putc (' ', stdout);
		}
		c = keep (c);
		length++;
	}
	return (c);
}

static signed grab (signed c)

{
	return (getc (stdin));
}

static signed join (signed c)

{
	return (span (getc (stdin), '\\', '\n'));
}

/*====================================================================*
 *
 *   signed pack (signed c, signed space, signed (* edit) (signed));
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static signed pack (signed c, signed newline, signed (* edit) (signed))

{
	do 
	{
		c = edit (c);
	}
	while (isblank (c));
	if (nobreak (c))
	{
		if (newline)
		{
			putc (newline, stdout);
		}
	}
	return (c);
}

/*====================================================================*
 *
 *   signed compress (signed c, signed newline, signed endline);
 *
 *   read stdin and write stdout; replace leading spaces and tabs
 *   with character o unless it is NUL; replace embedded spaces and
 *   tabs with one space; discard trailing spaces and tabs; replace
 *   newline with character e unless it is NUL;
 *
 *   write literal strings, enclosed in quotes or apostrophes, as
 *   as read; ignore escaped newlines for lines that start in first
 *   column;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed compress (signed c, signed newline, signed endline)

{
	while (c != EOF)
	{
		signed (* edit) (signed) = join;
		if (isblank (c))
		{
			edit = grab;
			c = pack (c, newline, edit);
		}
		while (nobreak (c))
		{
			if (c == '#')
			{
				do 
				{
					c = keep (c);
				}
				while (nobreak (c));
				continue;
			}
			if (isquote (c))
			{
				c = literal (c);
				continue;
			}
			if (isblank (c))
			{
				c = pack (c, ' ', edit);
				continue;
			}
			c = keep (c);
		}
		if (endline)
		{
			putc (endline, stdout);
		}
		c = keep (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   void function (signed c, signed o, signed e, bool trim);
 *
 *
 *
 *--------------------------------------------------------------------*/

void function (signed c, signed newline, signed endline, bool trim)

{
	if (trim)
	{
		trimm (getc (stdin), 8);
	}
	else 
	{
		compress (c, newline, endline);
	}
	return;
}

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [])

{
	static char const * optv [] =
	{
		"white space minimizer",
		PUTOPTV_S_FILTER,
		"c:e:nstx",
		"c c\tindent is one (c) [" LITERAL (SPACE_NEWLINE) "]",
		"e c\treturn is one (c) [" LITERAL (SPACE_ENDLINE) "]",
		"n\tindent is nothing",
		"s\tindent is one space [" LITERAL (CLANG_SP) "]",
		"t\tindent is one tab [" LITERAL (CLANG_HT) "]",
		"x\treplace tabs with spaces; discard trailing spaces;",
		(char *) (0)
	};
	char newline = SPACE_NEWLINE;
	char endline = SPACE_ENDLINE;
	bool trim = false;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'c':
			newline = * struesc ((char *) (optarg));
			break;
		case 'e':
			endline = * struesc ((char *) (optarg));
			break;
		case 'n':
			newline = (char) (0);
			break;
		case 's':
			newline = CLANG_SP;
			break;
		case 't':
			newline = CLANG_HT;
			break;
		case 'x':
			trim = true;
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function (getc (stdin), newline, endline, trim);
	}
	while ((argc) && (* argv))
	{
		if (vfopen (* argv))
		{
			function (getc (stdin), newline, endline, trim);
		}
		argc--;
		argv++;
	}
	exit (0);
}

