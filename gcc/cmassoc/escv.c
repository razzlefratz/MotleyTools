/*====================================================================*
 *
 *   escv.c - display command line arguments on stdout;
 *
 *   this program is similar to argv except that command line arguments
 *   are modified by struesc() before being printed on stdout; struesc()
 *   detects and translates character escape sequences;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stddef.h>

#include "../strlib/strlib.h"
#include "../chrlib/chrlib.h"

#ifndef MAKEFILE
#include "../strlib/struesc.c"
#include "../chrlib/chrindex.c"
#include "../chrlib/chruesc.c"
#include "../tools/todigit.c"
#endif

int main(int argc, char * argv[])

{
	printf ("\n");
	for (argc = 1; argv[argc]; argc++)
	{
		printf (" argv[%02d] = \"%s\"\n", argc, struesc(argv[argc]));
	}
	printf (" argv[%02d] = NULL\n", argc);
	printf ("\n");
	return (0);
}

