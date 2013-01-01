/*====================================================================*
 *
 *   wc.c - word count utility program;
 *
 *   this program counts the number of bytes, alphanumerics, words,
 *   and lines in a text file; a word is any consecutive string of
 *   letters and/or digits; the user May optionally specify any set
 *   of characters as elements of a word;
 *
 *   $ wc [-hlwcbt] [{c...}] [file1 file2 ...] [>listfile]
 *
 *   this is, of course, a modified version of the WORDCOUNT program
 *   presented in 'Software Tools' by Kernighan and Plauger; switches
 *   are interpreted identically to the UNIX utility program, wc;
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
#include "../chrlib/charset.c"
#include "../chrlib/chrset.c"
#include "../chrlib/chrdef.c"
#endif

/*====================================================================*
 * program constants;
 *--------------------------------------------------------------------*/

#define WC_B_NLINE  (1 << 0)
#define WC_B_NWORD  (1 << 1)
#define WC_B_NCHAR  (1 << 2)
#define WC_B_NBYTE  (1 << 3)
#define WC_B_TOTAL  (1 << 4)

/*====================================================================*
 * program variables;
 *--------------------------------------------------------------------*/

typedef struct wc 

{
	unsigned long _line;
	unsigned long _word;
	unsigned long _char;
	unsigned long _byte;
	char const *_name;
}

wc;

/*====================================================================*
 *
 *   void show (struct wc *total, flag_t flags);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void show (struct wc *total, flag_t flags) 

{
	if (flags & WC_B_NLINE) 
	{
		printf ("%12lu l ", total->_line);
	}
	if (flags & WC_B_NWORD) 
	{
		printf ("%12lu w ", total->_word);
	}
	if (flags & WC_B_NCHAR) 
	{
		printf ("%12lu c ", total->_char);
	}
	if (flags & WC_B_NBYTE) 
	{
		printf ("%12lu b ", total->_byte);
	}
	printf ("%s\n", total->_name);
	return;
}


/*====================================================================*
 *
 *   void func (char const *file, char table[], flag_t flags);
 *
 *   wrdcnt() counts the number of bytes, characters, words, and lines
 *   in a text file and produces a tabulated listing on stdout. It has
 *   the general form
 *
 *   llllllll L wwwwwwww W cccccccc C bbbbbbbb B ffff...ffff
 *
 *   where: l = number of lines
 *          w = number of words
 *          c = number of characters (letters and/or digits)
 *          b = number of bytes
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void function (char const *pathname, char table [], struct wc *total, flag_t flags) 

{
	struct wc local;
	bool word = false;
	signed c;
	local._name = pathname;
	local._line = 0;
	local._word = 0;
	local._char = 0;
	local._byte = 0;
	while ((c = getc (stdin)) != EOF) 
	{
		if (c == '\n') 
		{
			word = false;
			local._line++;
		}
		else if (table [(unsigned) (c)]) 
		{
			if (word == false) 
			{
				word = true;
				local._word++;
			}
			local._char++;
		}
		else 
		{
			word = false;
		}
		local._byte++;
	}
	total->_line += local._line;
	total->_word += local._word;
	total->_char += local._char;
	total->_byte += local._byte;
	show (&local, flags);
	return;
}


/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
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
		"W:lwcbt",
		PUTOPTV_S_FUNNEL,
		"counts the lines, words, chars and bytes in a text file",
		"W s\tcharset is (s) [" CHRLIB_WORDSET "]",
		"l\tdisplay line count",
		"w\tdisplay word count",
		"c\tdisplay char count",
		"b\tdisplay byte count",
		"t\tdisplay totals",
		(char const *) (0)
	};
	struct wc total = 
	{
		0,
		0,
		0,
		0,
		"total"
	};
	static char words [UCHAR_MAX + 1];
	static char table [UCHAR_MAX + 1];
	flag_t flags = (flag_t) (0);
	signed c;
	total._name = "total";
	memset (table, 0, sizeof (table));
	charset (CHRLIB_WORDSET, (char) (0), words, sizeof (words));
	chrdef (table, words);
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'W':
			memset (table, 0, sizeof (table));
			charset (optarg, (char) (0), words, sizeof (words));
			chrdef (table, words);
			break;
		case 'l':
			_setbits (flags, WC_B_NLINE);
			break;
		case 'w':
			_setbits (flags, WC_B_NWORD);
			break;
		case 'c':
			_setbits (flags, WC_B_NCHAR);
			break;
		case 'b':
			_setbits (flags, WC_B_NBYTE);
			break;
		case 't':
			_setbits (flags, WC_B_TOTAL);
			break;
		default:
			break;
		}
	}
	if (_allclr (flags, WC_B_NLINE | WC_B_NWORD | WC_B_NCHAR | WC_B_NBYTE)) 
	{
		_setbits (flags, WC_B_NLINE | WC_B_NWORD | WC_B_NCHAR | WC_B_NBYTE);
	}
	argc -= optind;
	argv += optind;
	if (!argc) 
	{
		function ("stdin", table, &total, flags);
	}
	while ((argc) && (* argv)) 
	{
		if (efreopen (* argv, "rb", stdin)) 
		{
			function (* argv, table, &total, flags);
		}
		argc--;
		argv++;
	}
	show (&total, flags);
	exit (0);
}

