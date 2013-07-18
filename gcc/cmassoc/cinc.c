/*====================================================================*
 *
 *   cinc.c - include all C language support files;
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
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/getoptv.h"
#include "../tools/putoptv.h"
#include "../tools/version.h"
#include "../tools/error.h"
#include "../tools/tools.h"
#include "../tools/chars.h"
#include "../tools/paths.h"
#include "../tools/sizes.h"
#include "../tools/tools.h"
#include "../tools/types.h"
#include "../tools/vtdef.h"
#include "../tools/memory.h"
#include "../tools/number.h"
#include "../tools/symbol.h"
#include "../tools/format.h"
#include "../files/files.h"
#include "../clang/clang.h"
#include "../chrlib/chrlib.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/efopen.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

/*====================================================================*
 *
 *   void function (char const * pathname, char const * vector []);
 *
 *   read stdin and write stdout; copy targetfile tokens to stdout;
 *   intercept processor include directives and include local files
 *   where specified; 
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (char * fullpath, char const * vector []) 

{ 
	FILE * fp; 
	char buffer [CSOURCE]; 
	char * sp; 
	char * cp; 
	signed c; 
	if ((fp = efopen (fullpath, "rb"))) 
	{ 
		char pathname [FILENAME_MAX]; 
		for (sp = cp = strcpy (pathname, fullpath); * cp; ++ cp) 
		{ 
			if (* cp == '/') 
			{ 
				sp = cp; 
			} 
		} 
		* sp = (char)(0); 
		c = getc (fp); 
		while (c != EOF) 
		{ 
			sp = buffer; 
			if (isspace (c)) 
			{ 
				do 
				{ 
					putc (c, stdout); 
					c = getc (fp); 
				} 
				while (isspace (c)); 
				continue; 
			} 
			if (isalpha (c)) 
			{ 
				do 
				{ 
					putc (c, stdout); 
					c = getc (fp); 
				} 
				while (isalnum (c)); 
				continue; 
			} 
			if (isdigit (c)) 
			{ 
				do 
				{ 
					putc (c, stdout); 
					c = getc (fp); 
				} 
				while (isdigit (c)); 
				continue; 
			} 
			if (c == '#') 
			{ 
				* sp++ = (char)(c); 
				c = getc (fp); 
				while (isblank (c)) 
				{ 
					* sp++ = (char)(c); 
					c = getc (fp); 
				} 
				cp = sp; 
				while (isalpha (c)) 
				{ 
					* sp++ = (char) (c); 
					c = getc (fp); 
				} 
				* sp = (char)(0); 
				if (strcmp ("include", cp)) 
				{ 
					while (nobreak (c)) 
					{ 
						* sp++ = (char) (c); 
						c = getc (fp); 
					} 
					* sp++ = (char)(c); 
					for (cp = buffer; cp < sp; putc (* cp++, stdout)); 
					c = getc (fp); 
					continue; 
				} 
				while (isblank (c)) 
				{ 
					* sp++ = (char) (c); 
					c = getc (fp); 
				} 
				if (c == '\"') 
				{ 
					size_t index; 
					char filename [FILENAME_MAX]; 
					cp = filename; 
					c = getc (fp); 
					while ((c != '\"') && (c != EOF)) 
					{ 
						* cp++ = * sp++ = (char) (c); 
						c = getc (fp); 
					} 
					* cp = (char) (0); 
					makepath (fullpath, pathname, filename); 
					for (index = 0; vector [index] != (char *)(0); index++) 
					{ 
						if (!strcmp (fullpath, vector [index])) 
						{ 
							break; 
						} 
					} 
					if (vector [index] == (char *)(0)) 
					{ 
						vector [index++] = strdup (fullpath); 
						vector [index] = (char *)(0); 
						function (fullpath, vector); 
					} 
					while (nobreak (c)) 
					{ 
						* sp++ = (char) (c); 
						c = getc (fp); 
					} 
					* sp++ = (char) (c); 
				} 
				else 
				{ 
					while (nobreak (c)) 
					{ 
						* sp++ = (char) (c); 
						c = getc (fp); 
					} 
					* sp++ = (char) (c); 
					for (cp = buffer; cp < sp; putc (* cp++, stdout)); 
				} 
				c = getc (fp); 
				continue; 
			} 
			if (isquote (c)) 
			{ 
				signed o = getc (fp); 
				putc (c, stdout); 
				while ((o != c) && (c != EOF)) 
				{ 
					if (o == '\\') 
					{ 
						putc (o, stdout); 
						o = getc (fp); 
					} 
					putc (o, stdout); 
					o = getc (fp); 
				} 
				putc (c, stdout); 
				c = getc (fp); 
				continue; 
			} 
			if (c == '/') 
			{ 
				putc (c, stdout); 
				c = getc (fp); 
				if (c == '/') 
				{ 
					while (nobreak (c)) 
					{ 
						putc (c, stdout); 
						c = getc (fp); 
					} 
					putc ('\n', stdout); 
					c = getc (fp); 
					continue; 
				} 
				if (c == '*') 
				{ 
					while (nomatch (c, '/')) 
					{ 
						while (nomatch (c, '*')) 
						{ 
							putc (c, stdout); 
							c = getc (fp); 
						} 
						putc (c, stdout); 
						c = getc (fp); 
					} 
					putc ('/', stdout); 
					c = getc (fp); 
					continue; 
				} 
				putc (c, stdout); 
				c = getc (fp); 
				continue; 
			} 
			putc (c, stdout); 
			c = getc (fp); 
		} 
		fclose (fp); 
	} 
	return; 
} 

/*====================================================================*
 *   
 *   int main (int argc, char const * argv[]);
 *   
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
		"", 
		PUTOPTV_S_FILTER, 
		"include all C language support files", 
		(char const *) (0)
	}; 
	char pathname [FILENAME_MAX]; 
	signed c; 
	while (~ (c = getoptv (argc, argv, optv))) 
	{ 
		switch (c) 
		{ 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	while ((argc) && (* argv)) 
	{ 
		char const * vector [200]; 
		makepath (pathname, getenv ("PWD"), * argv); 
		vector [0] = strdup (pathname); 
		vector [1] = (char *)(0); 
		function (pathname, vector); 
		for (argc = 0; vector [argc]; argc++) 
		{ 
			fprintf (stderr, "%s\n", vector [argc]); 
		} 
		argc--; 
		argv++; 
	} 
	exit (0); 
} 

