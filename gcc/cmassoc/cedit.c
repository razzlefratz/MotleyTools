/*====================================================================*
 *
 *   cedit.c - rename a C Language variable or constant;
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
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/mergepath.c"
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define CEDIT_COUNT (1 << 0) 
#define CEDIT_ERROR (1 << 1) 

/*====================================================================*
 *
 *   unsigned function (char const * oldname, char const * newname);
 *
 *   read tokens from stdin and write them to stdout; replace alpha
 *   tokens that match oldname with token newname;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

unsigned function (char const * oldname, char const * newname) 

{ 
	unsigned count = 0; 
	signed c = getc (stdin); 
	while (c != EOF) 
	{ 
		if (isspace (c)) 
		{ 
			do 
			{ 
				putc (c, stdout); 
				c = getc (stdin); 
			} 
			while (isspace (c)); 
			continue; 
		} 
		if (isalpha (c) || (c == '_')) 
		{ 
			char string [255]; 
			char * sp = string; 
			do 
			{ 
				* sp++ = (char)(c); 
				c = getc (stdin); 
			} 
			while (isalnum (c) || (c == '_')); 
			* sp = (char)(0); 
			if (!strcmp (string, oldname)) 
			{ 
				count++; 
				fputs (newname, stdout); 
				continue; 
			} 
			fputs (string, stdout); 
			continue; 
		} 
		if (isdigit (c)) 
		{ 
			do 
			{ 
				putc (c, stdout); 
				c = getc (stdin); 
			} 
			while (isdigit (c) || (c == '.')); 
			if ((c == 'x') || (c == 'X')) 
			{ 
				do 
				{ 
					putc (c, stdout); 
					c = getc (stdin); 
				} 
				while (isxdigit (c)); 
			} 
			if ((c == 'e') || (c == 'E')) 
			{ 
				putc (c, stdout); 
				c = getc (stdin); 
				if ((c == '+') || (c == '-')) 
				{ 
					putc (c, stdout); 
					c = getc (stdin); 
				} 
				while (isdigit (c)) 
				{ 
					putc (c, stdout); 
					c = getc (stdin); 
				} 
			} 
			continue; 
		} 
		if (isquote (c)) 
		{ 
			signed o; 
			putc (c, stdout); 
			o = getc (stdin); 
			while (nomatch (o, c)) 
			{ 
				if ((char)(o) == '\\') 
				{ 
					putc (o, stdout); 
					o = getc (stdin); 
				} 
				putc (o, stdout); 
				o = getc (stdin); 
			} 
			putc (c, stdout); 
			c = getc (stdin); 
			continue; 
		} 
		if (c == '/') 
		{ 
			putc (c, stdout); 
			c = getc (stdin); 
			if (c == '/') 
			{ 
				while (nobreak (c)) 
				{ 
					putc (c, stdout); 
					c = getc (stdin); 
				} 
				putc ('\n', stdout); 
				c = getc (stdin); 
				continue; 
			} 
			if (c == '*') 
			{ 
				while (nomatch (c, '/')) 
				{ 
					while (nomatch (c, '*')) 
					{ 
						putc (c, stdout); 
						c = getc (stdin); 
					} 
					putc (c, stdout); 
					c = getc (stdin); 
				} 
				putc ('/', stdout); 
				c = getc (stdin); 
				continue; 
			} 
			continue; 
		} 
		putc (c, stdout); 
		c = getc (stdin); 
	} 
	return (count); 
} 

/*====================================================================*
 *   
 *   int main (int argc, char const * argv[]);
 *   
 *   take one old and one new variable name as command arguments and
 *   call the edit function to replace the old with the new;
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
		"co:n:", 
		PUTOPTV_S_FILTER, 
		"rename a C Language variable or constant", 
		"c\treport changes", 
		"o s\told token is s", 
		"n s\tnew token is s", 
		(char const *) (0)
	}; 
	flag_t flags = (flag_t)(0); 
	char const * oldname = ""; 
	char const * newname = ""; 
	char const * sp; 
	signed c; 
	while (~ (c = getoptv (argc, argv, optv))) 
	{ 
		switch (c) 
		{ 
		case 'c': 
			_setbits (flags, CEDIT_COUNT); 
			break; 
		case 'o': 
			oldname = optarg; 
			break; 
		case 'n': 
			newname = optarg; 
			break; 
		default: 
			break; 
		} 
	} 
	if (!oldname) 
	{ 
		error (1, EINVAL, "No old name given"); 
	} 
	for (sp = oldname; * sp; sp++) 
	{ 
		if (!isalnum (* sp) && (* sp != '_')) 
		{ 
			error (1, EINVAL, "%s is not a variable or constant name", oldname); 
		} 
	} 
	if (sp == oldname) 
	{ 
		error (1, EINVAL, "Old name is empty"); 
	} 
	if (!newname) 
	{ 
		error (1, EINVAL, "No new name given"); 
	} 
	for (sp = newname; * sp; sp++) 
	{ 
		if (!isalnum (* sp) && (* sp != '_')) 
		{ 
			error (1, EINVAL, "%s is not a variable or constant name", newname); 
		} 
	} 
	if (sp == newname) 
	{ 
		error (1, EINVAL, "New name  is empty"); 
	} 
	argc -= optind; 
	argv += optind; 
	if (!argc) 
	{ 
		if ((c = function (oldname, newname))) 
		{ 
			if (_anyset (flags, CEDIT_COUNT)) 
			{ 
				fprintf (stderr, "stdin %d\n", c); 
			} 
		} 
	} 
	while ((argc) && (* argv)) 
	{ 
		if (vfopen (* argv)) 
		{ 
			if ((c = function (oldname, newname))) 
			{ 
				if (_anyset (flags, CEDIT_COUNT)) 
				{ 
					fprintf (stderr, "%s %d\n", * argv, c); 
				} 
			} 
		} 
		argc--; 
		argv++; 
	} 
	exit (0); 
} 

