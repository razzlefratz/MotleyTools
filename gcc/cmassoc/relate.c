/*====================================================================*
 *
 *   relate.c - organize dependency information;
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

#include <unistd.h>
#include <string.h>
#include <ctype.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../tree/depend.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/efreopen.c"
#include "../tools/emalloc.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../tree/depend.c"
#endif

/*====================================================================*
 *  program constants; 
 *--------------------------------------------------------------------*/

#define DEP_B_INVERT  (1 << 0)
#define DEP_B_REPORT  (1 << 1)

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

extern TREE * nodetree;
static TREE * edgetree = (TREE *) (0);

/*====================================================================*
 *
 *   void populate (char const *filename);
 *
 *   read stdin as a series of csv string pairs;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void populate (flag_t flags) 

{
	char one [TEXTLINE_MAX];
	char two [TEXTLINE_MAX];
	signed c = getc (stdin);
	while (c != EOF) 
	{
		char * sp;
		while (isspace (c)) 
		{
			c = getc (stdin);
		}
		sp = one;
		while (nobreak (c) && (c != ',') && (c != ':') && (c != ';')) 
		{
			* sp++ = (char) (c);
			c = getc (stdin);
		}
		* sp = (char) (0);
		while (isblank (c)) 
		{
			c = getc (stdin);
		}
		if ((c == ',') || (c == ':')) 
		{
			c = getc (stdin);
		}
		while (isblank (c)) 
		{
			c = getc (stdin);
		}
		sp = two;
		while (nobreak (c) && (c != ';')) 
		{
			* sp++ = (char) (c);
			c = getc (stdin);
		}
		* sp = (char) (0);
		while (isblank (c)) 
		{
			c = getc (stdin);
		}
		if (c == ';') 
		{
			c = getc (stdin);
		}
		while (isspace (c)) 
		{
			c = getc (stdin);
		}
		if (_anyset (flags, DEP_B_INVERT)) 
		{
			edgetree = ordernode (edgetree, two, one, strcmp);
		}
		else 
		{
			edgetree = ordernode (edgetree, one, two, strcmp);
		}
	}
	return;
}

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
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
		"nf",
		PUTOPTV_S_FUNNEL,
		"organize dependency information",
		"n\tneed summary ",
		"f\tfeed summary ",
		(char const *) (0)
	};
	flag_t flags = (flag_t) (0);
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'n':
			_setbits (flags, DEP_B_REPORT);
			_clrbits (flags, DEP_B_INVERT);
			break;
		case 'f':
			_setbits (flags, DEP_B_REPORT);
			_setbits (flags, DEP_B_INVERT);
			break;
		default:
			break;
		}
	}
	argc-= optind;
	argv+= optind;
	if (!argc) 
	{
		populate (flags);
	}
	while ((argc) && (* argv)) 
	{
		if (efreopen (* argv, "rb", stdin)) 
		{
			populate (flags);
		}
		argc--;
		argv++;
	}
	if (_anyset (flags, DEP_B_REPORT)) 
	{
		structure (edgetree);
	}
	else 
	{
		enumerate (nodetree);
	}
	return (0);
}

