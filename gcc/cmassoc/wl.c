/*====================================================================*
 *
 *   wl.c - word list utility program;
 *
 *   output words read from the input stream, one per line; by 
 *   default, a word is any consecutive string of letters, digits, 
 *   underscore (_) or dollar_sign ($); 
 *
 *   $ wl [-w charset] [-lu] [file1 file2 ...] [>listfile]
 *
 *   this is, of course, a modified version of the wordlist program 
 *   found in 'Software Tools' by Kernighan and Plauger;
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
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/*====================================================================*
 * custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../chrlib/chrlib.h"

/*====================================================================*
 * custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/efreopen.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../chrlib/chrset.c"
#include "../chrlib/chrdef.c"
#include "../chrlib/chrlwr.c"
#include "../chrlib/chrupr.c"
#include "../chrlib/charset.c"
#include "../strlib/strcomp.c"
#include "../strlib/strconv.c"
#endif

/*====================================================================*
 * program constants;
 *--------------------------------------------------------------------*/

#define WL_FLAG_UPPER (1 << 0) 
#define WL_FLAG_LOWER (1 << 1)

/*====================================================================*
 *
 *   void wordlist(char ctable[], flag_t flag);
 *
 *   read from ifp and write to ofp; isolate words read from ifp; write
 *   each word to ofp on a new line; optionally convert words to upper
 *   or lower case on output;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (char const ctable [], flag_t flags)

{
	bool word = false;
	signed c;
	while ((c = getc (stdin)) != EOF)
	{
		if (ctable [(unsigned) (c)])
		{
			word = true;
			if (_anyset (flags, WL_FLAG_UPPER))
			{
				putc (chrupr (c), stdout);
				continue;
			}
			if (_anyset (flags, WL_FLAG_LOWER))
			{
				putc (chrlwr (c), stdout);
				continue;
			}
			putc (c, stdout);
			continue;
		}
		if (word)
		{
			word = false;
			putc ('\n', stdout);
			continue;
		}
	}
	return;
}

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
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
		"fw:lu",
		PUTOPTV_S_FUNNEL,
		"prints a list of words read from the input stream",
		"f\toutput filenames",
		"w s\tword consists of character set (s) [" CHRLIB_WORDSET "]",
		"l\toutput words in lower case ",
		"u\toutput words in upper case ",
		(char *) (0)
	};
	char words [UCHAR_MAX +  1];
	char table [UCHAR_MAX +  1];
	flag_t flags = (flag_t) (0);
	signed c;
	memset (table, 0, sizeof (table));
	charset (CHRLIB_WORDSET, (char) (0), words, sizeof (words));
	chrdef (table, words);
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'f':
			memset (table, 0, sizeof (table));
			charset ("_[:alnum:].-", (char) (0), words, sizeof (words));
			chrdef (table, words);
			break;
		case 'w':
			memset (table, 0, sizeof (table));
			charset (optarg, (char) (0), words, sizeof (words));
			chrdef (table, words);
			break;
		case 'u':
			_setbits (flags, WL_FLAG_UPPER);
			_clrbits (flags, WL_FLAG_LOWER);
			break;
		case 'l':
			_clrbits (flags, WL_FLAG_UPPER);
			_setbits (flags, WL_FLAG_LOWER);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function (table, flags);
	}
	while ((argc) && (* argv))
	{
		if (efreopen (* argv, "rb", stdin))
		{
			function (table, flags);
		}
		argc--;
		argv++;
	}
	exit (0);
}

