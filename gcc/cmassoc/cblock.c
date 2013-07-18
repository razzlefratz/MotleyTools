/*====================================================================*
 *
 *   cblock.c - C/C++ Language blocker;
 *
 *   
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
#include <string.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tidy/tidy.h"
#include "../tools/chars.h"
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
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

#ifndef MAKEFILE
#include "../tidy/capsule.c"
#include "../tidy/context.c"
#include "../tidy/content.c"
#include "../tidy/control.c"
#include "../tidy/comment.c"
#include "../tidy/literal.c"
#include "../tidy/escaped.c"
#include "../tidy/fortran.c"
#include "../tidy/keep.c"
#include "../tidy/find.c"
#endif

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

static unsigned level = 1; 

/*====================================================================*
 *   program functions;
 *--------------------------------------------------------------------*/

static signed program (signed c, signed e); 

/*====================================================================*
 *
 *   signed preamble (signed c);
 *
 *   conditionally print an empty preamble comment block; return
 *   character c unchanged;
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static signed preamble (signed c) 

{ 
	extern unsigned level; 
	if (!level) 
	{ 
		while (c != EOF) 
		{ 
			if (isspace (c)) 
			{ 
				c = getc (stdin); 
				continue; 
			} 
			if (c == '/') 
			{ 
				c = comment (c); 
				continue; 
			} 
			if (c == ';') 
			{ 
				c = keep (c); 
				continue; 
			} 
			printf ("\n\n/*===*\n *\n *\n *\n *.\n *:\n *;\n *---*/\n\n"); 
			break; 
		} 
	} 
	return (c); 
} 

/*====================================================================*
 *
 *   signed statement (signed c);
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static signed statement (signed c) 

{ 
	while (isspace (c)) 
	{ 
		c = keep (c); 
	} 
	if (c == '{') 
	{ 
		c = keep (c); 
		c = program (c, '}'); 
		c = keep (c); 
	} 
	else if (c != ';') 
	{ 
		putc ('{', stdout); 
		putc (' ', stdout); 
		c = program (c, ';'); 
		c = keep (c); 
		putc (' ', stdout); 
		putc ('}', stdout); 
	} 
	return (c); 
} 

/*====================================================================*
 *
 *   signed condition (signed c);
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static signed condition (signed c) 

{ 
	while (isspace (c)) 
	{ 
		c = keep (c); 
	} 
	if (c == '(') 
	{ 
		c = context (c, ')'); 
	} 
	else if (c != ';') 
	{ 
		putc (' ', stdout); 
		putc ('(', stdout); 
		c = program (c, ';'); 
		putc (')', stdout); 
		putc (' ', stdout); 
	} 
	return (c); 
} 

/*====================================================================*
 *
 *   signed program (signed c, signed e);
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static signed program (signed c, signed e) 

{ 
	extern unsigned level; 
	c = preamble (c); 
	while ((c != e) && (c != EOF)) 
	{ 
		if (c == '#') 
		{ 
			c = fortran (c); 
			continue; 
		} 
		if (c == '/') 
		{ 
			c = comment (c); 
			continue; 
		} 
		if (c == '{') 
		{ 
			level++; 
			c = keep (c); 
			c = program (c, '}'); 
			c = keep (c); 
			level--; 
			c = preamble (c); 
			continue; 
		} 
		if (c == '(') 
		{ 
			c = context ('(', ')'); 
			continue; 
		} 
		if (c == '[') 
		{ 
			c = context ('[', ']'); 
			continue; 
		} 
		if (isquote (c)) 
		{ 
			c = literal (c); 
			continue; 
		} 
		if (isalnum (c) || (c == '_') || (c == '.')) 
		{ 
			char string [100]; 
			char * sp = string; 
			do 
			{ 
				* sp++ = c; 
				c = keep (c); 
			} 
			while (isalnum (c) || (c == '_') || (c == '.')); 
			* sp = (char)(0); 
			if (!strcmp (string, "while")) 
			{ 
				c = condition (c); 
				c = statement (c); 
				continue; 
			} 
			if (!strcmp (string, "for")) 
			{ 
				c = condition (c); 
				c = statement (c); 
				continue; 
			} 
			if (!strcmp (string, "if")) 
			{ 
				c = condition (c); 
				c = statement (c); 
				continue; 
			} 
			if (!strcmp (string, "else")) 
			{ 
				c = statement (c); 
				continue; 
			} 
			if (!strcmp (string, "do")) 
			{ 
				c = statement (c); 
				continue; 
			} 
			if (!strcmp (string, "return")) 
			{ 
				c = condition (c); 
				continue; 
			} 
			if (!strcmp (string, "exit")) 
			{ 
				c = condition (c); 
				continue; 
			} 
			continue; 
		} 
		c = keep (c); 
	} 
	return (e); 
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
		"p", 
		PUTOPTV_S_FILTER, 
		"C/C++ language blocker", 
		"p\tinsert empty function preambles", 
		(char const *) (0)
	}; 
	signed c; 
	while (~ (c = getoptv (argc, argv, optv))) 
	{ 
		switch (c) 
		{ 
		case 'p': 
			level = 0; 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (!argc) 
	{ 
		program (NUL, EOF); 
	} 
	while ((argc) && (* argv)) 
	{ 
		if (vfopen (* argv)) 
		{ 
			program (NUL, EOF); 
		} 
		argc--; 
		argv++; 
	} 
	return (0); 
} 

