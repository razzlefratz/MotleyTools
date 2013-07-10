/*====================================================================*
 *
 *   typelist.c 
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

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/efreopen.c"
#include "../tools/todigit.c" 
#include "../tools/typeload.c" 
#include "../tools/typesave.c" 
#include "../tools/error.c" 
#include "../tools/print.c" 
#include "../tools/indent.c" 
#endif

/*====================================================================*
 *   constants;
 *--------------------------------------------------------------------*/

#define LISTSIZE 1000
#define LISTNAME "LIST"

/*====================================================================*
 *   programs;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	static char const * optv [] = 
	{ 
		"dmnst:v", 
		PUTOPTV_S_FUNNEL, 
		"generate C source code for a type table", 
		"d\tprint preprocessor definitions", 
		"m\tprint markup", 
		"n\tuse numbers instead of names", 
		"s\tprint switch statement", 
		"t s\ttable name is (c) [" LITERAL (LISTNAME) "]", 
		"v\tprint variable declaration", 
		(char const * )(0)
	}; 
	char const * name = LISTNAME; 
	struct _type_ list [LISTSIZE]; 
	size_t size = 0; 
	flag_t flags = (flag_t)(0); 
	signed c; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 'd': 
			_setbits (flags, TOOLS_B_DEFINE); 
			break; 
		case 'm': 
			_setbits (flags, TOOLS_B_MARKUP); 
			break; 
		case 'n': 
			_setbits (flags, TOOLS_B_NUMBER); 
			break; 
		case 's': 
			_setbits (flags, TOOLS_B_SWITCH); 
			break; 
		case 't': 
			name = optarg; 
			break; 
		case 'v': 
			_setbits (flags, TOOLS_B_DECLARE); 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (! flags) 
	{ 
		flags = TOOLS_B_NORMAL; 
	} 
	if (! argc) 
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
		argc-- ; 
		argv++ ; 
	} 
	return (0); 
} 

