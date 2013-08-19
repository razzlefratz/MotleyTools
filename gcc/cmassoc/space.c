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
#include "../tidy/connect.c"
#include "../tidy/span.c"
#include "../tidy/keep.c"
#include "../tidy/grab.c"
#endif

#ifndef MAKEFILE
#include "../strlib/struesc.c"
#endif

#ifndef MAKEFILE
#include "../chrlib/chruesc.c"
#endif

#include "../tidy/grab.c"

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define SPACE_NEWLINE '\t'
#define SPACE_ENDLINE '\0'

/*====================================================================*
 *
 *   void function (signed c, signed o, signed e);
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

static signed join (signed c) 

{ 
	return (span (getc (stdin))); 
} 

signed function (signed c, signed o, signed e) 

{ 
	while (c != EOF) 
	{ 
		signed (* edit) (signed) = join; 
		if (isblank (c)) 
		{ 
			edit = grab; 
			do { c = edit (c); } while (isblank (c)); 
			if (nobreak (c)) 
			{ 
				if (o) 
				{ 
					putc (o, stdout); 
				} 
			} 
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
				do { c = edit (c); } while (isblank (c)); 
				if (nobreak (c)) 
				{ 
					putc (' ', stdout); 
				} 
				continue; 
			} 
			c = keep (c); 
		} 
		if (e) 
		{ 
			putc (e, stdout); 
		} 
		c = keep (c); 
	} 
	return (c); 
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
		"c:e:nst", 
		PUTOPTV_S_FILTER, 
		"white space minimizer", 
		"c c\tindent character is (c) [" LITERAL (SPACE_NEWLINE) "]", 
		"e c\treturn character is (c) [" LITERAL (SPACE_ENDLINE) "]", 
		"n\tindent character is nothing", 
		"s\tindent character is space [\' \']", 
		"t\tindent character is tab [\'\\t\']", 
		(char *) (0)
	}; 
	char newline = SPACE_NEWLINE; 
	char endline = SPACE_ENDLINE; 
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
			newline = ' '; 
			break; 
		case 't': 
			newline = '\t'; 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (! argc) 
	{ 
		function (getc (stdin), newline, endline); 
	} 
	while ((argc) && (* argv)) 
	{ 
		if (vfopen (* argv)) 
		{ 
			function (getc (stdin), newline, endline); 
		} 
		argc--; 
		argv++; 
	} 
	exit (0); 
} 

