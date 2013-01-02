/*====================================================================*
 *
 *   sort.test.c - sort function test utility;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../sort/sort.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../tools/getopt.c"
#include "../tools/putopt.c"
#include "../tools/fputv.c"
#include "../sort/isort.c"
#include "../sort/ssort.c"
#include "../sort/psort.c"
#include "../sort/hsort.c"
#include "../sort/swap.c"
#include "../sort/sift.c"
#include "../sv/sv_sort.c"

/*====================================================================*
 *   main function;
 *--------------------------------------------------------------------*/

int main (int argc, char const *argv []) 

{
	static char const *usage [] = 
	{
		"[bspeh]",
		PUTOPT_S_FILTER,
		"sort function test utility",
		"b\tbridge (or insertion) sort",
		"s\tshell (or diminishing increment) sort",
		"p\tquick (or partition) sort (1)",
		"e\theap sort",
		"h\thelp summary ",
		NULL
	};
	signed c;
	optind = 1;
	opterr = 1;
	while ((c = getopt (argc, argv, usage [PUTOPT_I_OPTIONS])) != -1) 
	{
		switch (c) 
		{
		case 'b':
			isort ((void *)sv_sort, SV_SORT_MAX, (int (*)(void const *, void const *))(strcmp), swap, sift);
			break;
		case 's':
			ssort ((void *)sv_sort, SV_SORT_MAX, (int (*)(void const *, void const *))(strcmp), swap, sift);
			break;
		case 'p':
			psort ((void *)sv_sort, SV_SORT_MAX, (int (*)(void const *, void const *))(strcmp), swap);
			break;
		case 'e':
			hsort ((void *)sv_sort, SV_SORT_MAX, (int (*)(void const *, void const *))(strcmp), swap);
			break;
		case 'h':
			putopt (usage);
			exit (0);
		case ':':
			exit (1);
		case '?':
			exit (1);
		default:
			break;
		}
	}
	fputv (sv_sort, SV_SORT_MAX, stdout);
	exit (1);
}

