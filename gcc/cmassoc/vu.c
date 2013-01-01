/*====================================================================*
 *
 *   vu.cc - display ASCII control characters;
 *
 *   this program converts all ASCII control characters   to a visible,
 *   or printable, display format; the display mode is selectable, as
 *   either an ASCII, ANSI, or UNIX escape sequence;
 *
 *   $ vu [-acnbh] [file1 file2 ...] [>stdout]
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <ctype.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../chrlib/chrlib.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/efreopen.c"
#endif

#ifndef MAKEFILE
#include "../sv/sv_ascii.c"
#include "../sv/sv_glyph.c"
#endif

/*====================================================================*
 *   program definitions and declarations;
 *--------------------------------------------------------------------*/

#define VIS_S_ENBOLD "\033[1m\033[7m"
#define VIS_S_NORMAL "\033[0m"
#define VIS_B_BOLD (1 << 0)
#define VIS_B_NORM (1 << 1) 
#define VIS_B_NAME (1 << 2) 
#define VIS_B_CNTL (1 << 3) 
#define VIS_B_UNIX (1 << 4) 
#define VIS_B_IETF (1 << 5) 
#define VIS_B_HTML (1 << 6) 
#define VIS_B_MASK (VIS_B_NAME|VIS_B_CNTL|VIS_B_UNIX|VIS_B_IETF|VIS_B_HTML)

/*====================================================================*
 *
 *   void function (flag_t flags);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void function (flag_t flags) 

{
	extern char const *sv_ascii [];
	extern char const *sv_glyph [];
	char *sp1 = "";
	char *sp2 = "";
	signed c;
	if (_anyset (flags, VIS_B_BOLD)) 
	{
		if (isatty (fileno (stdout))) 
		{
			sp1 = VIS_S_ENBOLD;
			sp2 = VIS_S_NORMAL;
		}
	}
	while ((c = getc (stdin)) != EOF) 
	{
		if (c == '\n') 
		{
			putc (c, stdout);
			continue;
		}
		if (iscntrl (c)) 
		{
			fputs (sp1, stdout);
			if (_anyset (flags, VIS_B_NAME)) 
			{
				printf ("[%s]", sv_ascii [(unsigned) (c)]);
			}
			else if (_anyset (flags, VIS_B_HTML)) 
			{
				printf ("&%s;", sv_glyph [(unsigned) (c)]);
			}
			else if (_anyset (flags, VIS_B_CNTL)) 
			{
				printf ("^%c", ((unsigned) (c) | (0x0040)));
			}
			else if (_anyset (flags, VIS_B_UNIX)) 
			{
				printf ("\\%03o", (unsigned) (c));
			}
			else if (_anyset (flags, VIS_B_IETF)) 
			{
				printf ("%%%02X", (unsigned) (c));
			}
			else 
			{
				putc (' ', stdout);
			}
			fputs (sp2, stdout);
			continue;
		}
		putc (c, stdout);
	}
	return;
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"acgoxb",
		PUTOPTV_S_FUNNEL,
		"display control characters in visible formats",
		"a\tshow ASCII character names",
		"c\tshow ANSI control codes",
		"g\tshow ISO glyph codes",
		"x\tshow IETF hexidecimal octets",
		"o\tshow UNIX octal codes",
		"b\tshow in bold",
		(char const *)(0)
	};
	flag_t flags = (flag_t)(0);
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'a':
			_clrbits (flags, VIS_B_MASK);
			_setbits (flags, VIS_B_NAME);
			break;
		case 'c':
			_clrbits (flags, VIS_B_MASK);
			_setbits (flags, VIS_B_CNTL);
			break;
		case 'g':
			_clrbits (flags, VIS_B_MASK);
			_setbits (flags, VIS_B_HTML);
			break;
		case 'o':
			_clrbits (flags, VIS_B_MASK);
			_setbits (flags, VIS_B_UNIX);
			break;
		case 'x':
			_clrbits (flags, VIS_B_MASK);
			_setbits (flags, VIS_B_IETF);
			break;
		case 'b':
			_setbits (flags, VIS_B_BOLD);
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (!argc) 
	{
		function (flags);
	}
	while ((argc) && (* argv)) 
	{
		if (efreopen (* argv, "rb", stdin)) 
		{
			function (flags);
		}
		argc--;
		argv++;
	}
	exit (0);
}

