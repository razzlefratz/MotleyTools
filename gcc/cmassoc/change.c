/*====================================================================*
 *
 *   change.c - find and replace regular expression with text;
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
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
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
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/fgetline.c"
#include "../tools/emalloc.c"
#include "../tools/todigit.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/makefind.c"
#include "../files/partpath.c"
#include "../files/partfile.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/match.c"
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
#endif

#ifndef MAKEFILE
#include "../chrlib/chrindex.c"
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

#define CHANGE_B_HEADER (1 << 0)
#define CHANGE_B_NUMBER (1 << 1)
#define CHANGE_B_RECORD (1 << 2)
#define CHANGE_B_REPORT (1 << 3)
#define CHANGE_B_REVIEW (1 << 4)

/*====================================================================*
 *
 *   void func (char const *filename, EDIT *edit, flag_t flags);
 *
 *   read from stdin and write to stdout; remove text matching the 
 *   regular expression and insert fixed text; report filenames and 
 *   replacement counts;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (char const * filename, const regexp * remove, char const * insert, char buffer [], size_t length, flag_t flags) 

{ 
	unsigned changes = 0; 
	unsigned actual = 0; 
	if (!remove) 
	{ 
		return; 
	} 
	if (!insert) 
	{ 
		return; 
	} 
	if (!buffer) 
	{ 
		return; 
	} 
	while ((signed)(actual = fgetline (buffer, length, stdin)) != - 1) 
	{ 
		char const * sp; 
		for (sp = buffer; * sp; ++ sp) 
		{ 
			char const * cp; 
			if ((cp = regexspan (remove, sp))) 
			{ 
				fputs (insert, stdout); 
				sp = cp - 1; 
				changes++; 
			} 
			else 
			{ 
				fputc (* sp, stdout); 
			} 
		} 
		if (actual != (length - 1)) 
		{ 
			fputc ('\n', stdout); 
		} 
	} 
	if (changes > 0) 
	{ 
		if (flags & (CHANGE_B_HEADER)) 
		{ 
			if (flags & (CHANGE_B_NUMBER)) 
			{ 
				fprintf (stderr, "%3u ", changes); 
			} 
			fprintf (stderr, "%s\n", filename); 
		} 
	} 
	return; 
} 

/*====================================================================*
 *   
 *   int main (int argc, char const * argv[]);
 *   
 *   the use of ".*(s).*" here is opposite of that neede by search;
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *   
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	extern const unsigned char ct_unescape []; 
	static char const * optv [] = 
	{ 
		"e:l:t:fcHRT", 
		PUTOPTV_S_FILTER, 
		"replace text matching a regular expression with fixed text", 
		"e e\texpression (e) anywhere on line as in \".*{e}.*\"", 
		"l e\texpression (e) is complete line as in \"^{e}$\"", 
		"t s\treplacement text is (s)", 
		"f\treport replacement by filename", 
		"c\treport replacement counts ", 
		"H\tshow expression expansion", 
		"R\tregular expression rules", 
		"T\tescape sequence rules", 
		(char const *)(0)
	}; 
	regexp * remove = (regexp *) (0); 
	char const * insert = (char const *) (0); 
	char buffer [TEXTLINE_MAX] = 
	{ 
		(char) (0)
	}; 
	flag_t flags = (flag_t) (0); 
	int c; 
	while (~ (c = getoptv (argc, argv, optv))) 
	{ 
		switch (c) 
		{ 
		case 'c': 
			_setbits (flags, CHANGE_B_HEADER); 
			_setbits (flags, CHANGE_B_NUMBER); 
			_setbits (flags, CHANGE_B_RECORD); 
			break; 
		case 'f': 
			_setbits (flags, CHANGE_B_HEADER); 
			_clrbits (flags, CHANGE_B_NUMBER); 
			_clrbits (flags, CHANGE_B_RECORD); 
			break; 
		case 'e': 
			strcpy (buffer, struesc ((char *)(optarg))); 
			remove = regexmake (buffer); 
			break; 
		case 'l': 
			strcpy (buffer, REGEX_S_SPAN); 
			strcat (buffer, struesc ((char *)(optarg))); 
			strcat (buffer, REGEX_S_SPAN); 
			remove = regexmake (buffer); 
			break; 
		case 't': 
			insert = strdup (struesc ((char *)(optarg))); 
			break; 
		case 'H': 
			_setbits (flags, CHANGE_B_REVIEW); 
			break; 
		case 'h': 
			putoptv (optv); 
			exit (0); 
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
	if (!remove) 
	{ 
		error (0, EINVAL, "no search expression."); 
		exit (1); 
	} 
	if (flags & (CHANGE_B_REVIEW)) 
	{ 
		regexshow (remove); 
		exit (0); 
	} 
	if (!insert) 
	{ 
		error (0, EINVAL, "no replacement text."); 
		exit (1); 
	} 
	if (!* insert) 
	{ 
		error (0, EINVAL, "replacement string is empty."); 
		exit (1); 
	} 
	if (!argc) 
	{ 
		function ("stdin", remove, insert, buffer, sizeof (buffer), flags); 
	} 
	while ((argc) && (* argv)) 
	{ 
		if (vfopen (* argv)) 
		{ 
			function (* argv, remove, insert, buffer, sizeof (buffer), flags); 
		} 
		argc--; 
		argv++; 
	} 
	exit (0); 
} 

