/*====================================================================*
 *
 *   call.c - print C language functional dependencies;
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
#include "../strlib/strlib.h"
#include "../tidy/tidy.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/efreopen.c"
#endif

#ifndef MAKEFILE
#include "../strlib/svindex.c"
#endif

#ifndef MAKEFILE
#include "../tidy/nocomment.c"
#include "../tidy/nocontext.c"
#include "../tidy/noliteral.c"
#include "../tidy/noescaped.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define CALL_B_INVERT (1 << 0)

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

unsigned lineno = 0; 

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

static char const * reserved [] = 

{ 
	"auto", 
	"bool", 
	"break", 
	"case", 
	"char", 
	"const", 
	"continue", 
	"default", 
	"do", 
	"double", 
	"else", 
	"entry", 
	"enum", 
	"extern", 
	"float", 
	"for", 
	"goto", 
	"if", 
	"int", 
	"long", 
	"register", 
	"return", 
	"short", 
	"signed", 
	"sizeof", 
	"static", 
	"struct", 
	"switch", 
	"typedef", 
	"union", 
	"unsigned", 
	"void", 
	"volatile", 
	"while"
}; 

/*====================================================================*
 *
 *   unsigned function (flag_t flags);
 *
 *   scan source file for C language function definitions and calls;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (flag_t flags) 

{ 
	static unsigned level = 0; 
	char module [_NAMESIZE]; 
	char string [_NAMESIZE]; 
	signed c = getc (stdin); 
	while (c != EOF) 
	{ 
		while (isspace (c)) 
		{ 
			c = getc (stdin); 
		} 
		if (c == '#') 
		{ 
			do 
			{ 
				c = getc (stdin); 
				if (c == '\\') 
				{ 
					c = getc (stdin); 
					c = getc (stdin); 
				} 
			} 
			while (nobreak (c)); 
			continue; 
		} 
		if ((c == '{') || (c == '(') || (c == '[')) 
		{ 
			c = getc (stdin); 
			level++; 
			continue; 
		} 
		if ((c == '}') || (c == ')') || (c == ']')) 
		{ 
			c = getc (stdin); 
			level--; 
			continue; 
		} 
		if (c == '/') 
		{ 
			c = nocomment (c); 
			continue; 
		} 
		if (isquote (c)) 
		{ 
			c = noliteral (c); 
			continue; 
		} 
		if (isalpha (c) || (c == '_')) 
		{ 
			char * sp = string; 
			do 
			{ 
				* sp++ = (char)(c); 
				c = getc (stdin); 
			} 
			while (isalnum (c) || (c == '_')); 
			* sp = (char)(0); 

#if 0

			printf ("[%s]\n", string); 

#endif

			if (svindex (string, reserved, SIZEOF (reserved), strcmp) < SIZEOF (reserved)) 
			{ 
				continue; 
			} 
			while (isspace (c)) 
			{ 
				c = getc (stdin); 
			} 
			if (c == '(') 
			{ 
				if (!level) 
				{ 
					memcpy (module, string, sizeof (module)); 
				} 
				else if (_anyset (flags, CALL_B_INVERT)) 
				{ 
					printf ("%s:%s;\n", string, module); 
				} 
				else 
				{ 
					printf ("%s:%s;\n", module, string); 
				} 
			} 
			continue; 
		} 
		if (isdigit (c)) 
		{ 
			do 
			{ 
				c = getc (stdin); 
			} 
			while (isdigit (c) || (c == '.')); 
			if ((c == 'x') || (c == 'X')) 
			{ 
				do 
				{ 
					c = getc (stdin); 
				} 
				while (isxdigit (c)); 
			} 
			if ((c == 'e') || (c == 'E')) 
			{ 
				c = getc (stdin); 
				if ((c == '+') || (c == '-')) 
				{ 
					c = getc (stdin); 
				} 
				while (isdigit (c)) 
				{ 
					c = getc (stdin); 
				} 
			} 
			continue; 
		} 
		c = getc (stdin); 
	} 
	return; 
} 

/*====================================================================*
 *   
 *   int main (int argc, char const * argv[]);
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
		"x", 
		PUTOPTV_S_FUNNEL, 
		"print C language functional dependencies", 
		"x\texchange objects", 
		(char const *) (0)
	}; 
	flag_t flags = (flag_t) (0); 
	signed c; 
	while (~ (c = getoptv (argc, argv, optv))) 
	{ 
		switch (c) 
		{ 
		case 'x': 
			_setbits (flags, CALL_B_INVERT); 
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
	return (0); 
} 

