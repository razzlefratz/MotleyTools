/*====================================================================*
 *
 *   srt.c - file sort program;
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
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../sort/sort.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/emalloc.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

#ifndef MAKEFILE
#include "../sort/adheap.c"
#include "../sort/enheap.c"
#include "../sort/deheap.c"
#include "../sort/reheap.c"
#include "../sort/swap.c"
#endif

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

static signed order = 1;

/*====================================================================*
 *
 *   signed comp(char const * one, char const * two);
 *
 *   compare two heap members; return -1, 0 or 1 to indicate that 
 *   the first string precedes, matches or follows the second; this 
 *   function is passed to heap primatives enheap() and reheap();
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

signed comp (char const * one, char const * two)

{
	return (order * strcmp (one, two));
}

/*====================================================================*
 *
 *   size_t loadheap(char * heap[], size_t heapsize, size_t linesize, FILE *ifp);
 *
 *   read lines from stdin and store as a heap; return when the heap
 *   fills or stdin exhausts;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

size_t loadheap (char * heap [], size_t heapsize, size_t linesize, FILE * ifp)

{
	size_t heapitem = 0;
	char buffer [linesize];
	while ((heapitem < heapsize) && fgets (buffer, linesize, ifp))
	{
		heap [heapitem] = (char *)(emalloc (strlen (buffer) +  1));
		memcpy (heap [heapitem], buffer, strlen (buffer) +  1);
		adheap ((void *) (heap), ++ heapitem, (int (*) (void const *, void const *)) (comp), swap);
	}
	return (heapitem);
}

/*====================================================================*
 *
 *   size_t saveheap (char * heap [], size_t heapsize, FILE * ofp);
 *
 *   write heap to stdout; 
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

size_t saveheap (char * heap [], size_t heapsize, FILE * ofp)

{
	while ((heapsize > 0) && (fputs (heap [0], ofp) != EOF))
	{
		swap ((void *) (heap), 0, -- heapsize);
		reheap ((void *) (heap), heapsize, (int (*)(void const *, void const *)) (comp), swap);
		free (heap [heapsize]);
	}
	return (heapsize);
}

/*====================================================================*
 *
 *   void function (size_t heapsize, size_t linesize);
 *
 *   allocate a heap of specified size with lines of specified length; 
 *   load heap from stdin and save to stdout until stdin is exhausted; 
 *
 *   this implementation sorts the input stream in blocks of heapsize; 
 *   heapsize should equal or exceed the number of input lines to sort
 *   an entire file; 
 *
 *   this implementation alerts users when the file line count exceeds 
 *   the heapsize;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

size_t function (size_t heapsize, size_t linesize)

{
	char * heap [heapsize];
	size_t heapitem;
	size_t line = 0;
	size_t pass = 0;
	while ((heapitem = loadheap (heap, heapsize, linesize, stdin)))
	{
		saveheap (heap, heapitem, stdout);
		line += heapitem;
		pass++;
	}
	if (pass > 1)
	{
		error (0, EFBIG, "sorted %zd lines as %zd %zd-line blocks", line, pass, heapsize);
	}
	return (pass);
}

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [])

{
	extern signed order;
	static char const * optv [] = 
	{
		"b:dl:",
		PUTOPTV_S_FILTER,
		"sort files",
		"b n\tmaximum sort block is (n) lines [0x1000]",
		"d\tarrange output in descending order",
		"l n\tmaximum line length is (n) bytes [0x0400]",
		(char const *) (0)
	};
	size_t heapsize = _HEAPSIZE;
	size_t linesize = _LINESIZE;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'd':
			order = - 1;
			break;
		case 'b':
			heapsize = uintspec (optarg, 1, UINT_MAX);
			break;
		case 'l':
			linesize = uintspec (optarg, 1, UINT_MAX);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function (heapsize, linesize);
	}
	while ((argc) && (* argv))
	{
		if (vfopen (* argv))
		{
			function (heapsize, linesize);
		}
		argc--;
		argv++;
	}
	exit (0);
}

