/*====================================================================*
 *
 *   cblock.c - C/C++ Language blocker;
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
#endif

/*====================================================================*
 *   program functions;
 *--------------------------------------------------------------------*/

static signed program (signed c, signed e);

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
		c = keep ('{');
		c = program (c, '}');
		c = keep ('}');
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
		c = context ('(', ')');
	}
	else if (c != ';') 
	{
		putc ('(', stdout);
		c = control (c, ';');
		putc (')', stdout);
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
			c = keep ('{');
			c = program (c, '}');
			c = keep ('}');
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
		if (isalpha (c) || (c == '_')) 
		{
			char string [100];
			char *sp = string;
			do 
			{
				*sp++ = c;
				c = keep (c);
			}
			while (isalnum (c) || (c == '_'));
			*sp = (char)(0);
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
	return (c);
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
		"",
		PUTOPTV_S_FILTER,
		"C/C++ language blocker",
		(char const *) (0)
	};
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (!argc) 
	{
		program (getc (stdin), EOF);
	}
	while ((argc) && (* argv)) 
	{
		if (vfopen (* argv)) 
		{
			program (getc (stdin), EOF);
		}
		argc--;
		argv++;
	}
	return (0);
}

