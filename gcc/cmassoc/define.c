/*====================================================================*
 *
 *   tl.c - type list code generator;
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
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../tools/symbol.h"
#include "../tools/markup.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/efreopen.c"
#include "../tools/todigit.c" 
#include "../tools/typeload.c" 
#include "../tools/typesave.c" 
#include "../tools/indent.c" 
#endif

/*====================================================================*
 *   constants;
 *--------------------------------------------------------------------*/

#define LISTSIZE 1000
#define LISTNAME "LIST"

/*====================================================================*
 *
 *   void stylesheet ();
 *   
 *   print css stylesheet on stdout; this ensures that element class 
 *   names agree;
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void stylesheet (unsigned margin) 

{
	indent (margin++, "<style type='text/css'>");
	indent (margin, "table { table-layout: fixed; background: transparent; border-collapse: separate; border-spacing: 1pt; font: normal 10pt verdana; }");
	indent (margin, "th { background: inherit; padding: 2px 10px; text-align: center; vertical-align: middle; }");
	indent (margin, "td { background: inherit; padding: 2px 10px; text-align: left; vertical-align: top; }");
	indent (margin--, "</style>");
	indent (margin++, "<style type='text/css'>");
	indent (margin, "table.%s { border: solid 1pt black; border-spacing: 1px; background: white; }", STYLE_DATA);
	indent (margin, "th.%s, td.%s { border: solid 1pt silver; text-align: left; width: 250px; }", STYLE_NAME, STYLE_NAME);
	indent (margin, "th.%s, td.%s { border: solid 1pt silver; text-align: right; width: 100px; }", STYLE_SIZE, STYLE_SIZE);
	indent (margin, "th.%s, td.%s { border: solid 1pt silver; text-align: left; };", STYLE_TEXT, STYLE_TEXT);
	indent (margin--, "</style>");
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
		"cdmn:svx",
		PUTOPTV_S_FUNNEL,
		"generate C source code for a type table",
		"c\tprint css stylesheet for xhtml",
		"d\tprint preprocessor definitions",
		"m\tprint xhtml markup",
		"n s\ttable name is (s) [" LISTNAME "]",
		"s\tprint switch statement",
		"v\tprint variable declaration",
		"x\tuse numbers instead of names",
		(char const *)(0)
	};
	char const * name = LISTNAME;
	struct _type_ list [LISTSIZE];
	size_t size = 0;
	flag_t flags = (flag_t)(0);
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'c':
			stylesheet (1);
			return (0);
		case 'd':
			_setbits (flags, TOOLS_B_DEFINE);
			break;
		case 'm':
			_setbits (flags, TOOLS_B_MARKUP);
			break;
		case 'n':
			name = optarg;
			break;
		case 's':
			_setbits (flags, TOOLS_B_SWITCH);
			break;
		case 'v':
			_setbits (flags, TOOLS_B_DECLARE);
			break;
		case 'x':
			_setbits (flags, TOOLS_B_NUMBER);
			break;
		default:
			break;
		}
	}
	argc-= optind;
	argv+= optind;
	if (!flags) 
	{
		flags = TOOLS_B_NORMAL;
	}
	if (!argc) 
	{
		size = typeload (list, LISTSIZE);
		typesave (list, size, name, flags);
	}
	while ((argc) && (* argv)) 
	{
		if (efreopen (* argv, "rb", stdin)) 
		{
			size = typeload (list, LISTSIZE);
			typesave (list, size, name, flags);
		}
		argc--;
		argv++;
	}
	return (0);
}

