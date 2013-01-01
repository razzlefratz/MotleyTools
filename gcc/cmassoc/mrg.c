/*====================================================================*
 *
 *   mrg.c - merge sort program;
 *
 *   this implementations uses a heap to merge two or more files 
 *   into one; it will merge one file into one but that is a pointless 
 *   operation;
 *
 *   we are limited by the number of files that can be opened at one 
 *   time; this means that the heap can't exceed FOPEN_MAX files; 
 *   this problem can be overcome by repeated merging;
 *
 *   heap elements maintain a file pointer and a text buffer; as files are
 *   added to the heap, the first line of the file is used to re-order the
 *   growing heap; actual sorting occurs on output;
 *
 *   we write the text at the heap root, read the next line from that file
 *   and re-order the heap; we then write the new heap root; when the root
 *   file exhausts, we close it, free the memory, move the last element to
 *   the root, decrement the count and re-order the heap; this continues
 *   until the heap is empty;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
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
#include "../tools/efopen.c"
#include "../tools/emalloc.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#endif

#ifndef MAKEFILE
#include "../sort/enheap.c"
#include "../sort/reheap.c"
#include "../sort/adheap.c"
#include "../sort/swap.c"
#endif

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

static signed order = 1;
typedef struct line 

{
	FILE * file;
	char * name;
	char * text;
	unsigned line;
}

LINE;

/*====================================================================*
 *
 *   signed comp (const LINE * one, const LINE * two);
 *
 *   compare the text assigned to each of two LINE structures; return -1,
 *   0 or 1 to indicate that the first line precedes, matches or follows
 *   the second; this function is passed to enheap() and reheap() which
 *   implement the heap sort primatives;
 *
 *--------------------------------------------------------------------*/

static signed compare (char const * one, char const * two) 

{
	extern signed order;
	return (order * strcmp (one, two));
}

static signed comp (const LINE * one, const LINE * two) 

{
	return (compare (one->text, two->text));
}


/*====================================================================*
 *
 *   LINE * makeitem (FILE * stream, char const * name, size_t linesize);
 *
 *   create a LINE structure for the named file; read the first line 
 *   of text from that file; return the structure address on success 
 *   or NULL on recoverable failure;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static LINE * makeitem (FILE * stream, char const * name, size_t linesize) 

{
	char * text = emalloc (linesize);
	if (fgets (text, linesize, stream)) 
	{
		LINE * line = NEW (LINE);
		line->file = stream;
		line->name = strdup (name);
		line->text = text;
		line->line = 1;
		return (line);
	}
	free (text);
	return ((LINE *) (0));
}


/*====================================================================*
 *
 *   LINE * freeitem (LINE * line);
 *
 *   free the memory allocated to a LINE structure and return NULL;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static LINE * freeitem (LINE * line) 

{
	fclose (line->file);
	free (line->name);
	free (line->text);
	line->file = (FILE *) (0);
	line->name = (char *) (0);
	line->text = (char *) (0);
	free (line);
	return ((LINE *)(0));
}


/*====================================================================*
 *
 *   static void function (LINE * heap [], size_t heapsize, size_t linesize);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static void function (LINE * heap [], size_t heapsize, size_t linesize, int comp (void const *, void const *), void swap (void const * [], size_t, size_t)) 

{
	enheap ((void *) (heap), heapsize, (void *) (comp), (void *) (swap));
	while (heapsize) 
	{
		char text [linesize];
		memcpy (text, (* heap)->text, sizeof (text));
		if (fgets ((* heap)->text, linesize, (* heap)->file)) 
		{
			(* heap)->line++;
		}
		else 
		{
			*heap = freeitem (* heap);
			swap ((void *)(heap), 0, --heapsize);
		}
		if (heapsize) 
		{
			reheap ((void *) (heap), heapsize, (void *) (comp), (void *) (swap));
			if (compare ((* heap)->text, text) < 0) 
			{
				error (1, 0, "%s (%d): input out of order", (* heap)->name, (*heap)->line);
			}
		}
		fputs (text, stdout);
	}
	return;
}


/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	extern signed order;
	static char const * optv [] = 
	{
		"dl:",
		PUTOPTV_S_FUNNEL,
		"merge sorted files into one",
		"d\tinput files are in descending order",
		"l n\tmaximum line length is (n) bytes [0x0400]",
		(char const *)(0)
	};
	FILE * stream;
	LINE * heap [FOPEN_MAX];
	size_t heapsize = FOPEN_MAX;
	size_t heapitem = 0;
	size_t linesize = _LINESIZE;
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'd':
			order = -1;
			break;
		case 'l':
			linesize = uintspec (optarg, 1, SHRT_MAX);
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (!argc) 
	{
		if ((heap [heapitem] = makeitem (stdin, "stdin", linesize))) 
		{
			heapitem++;
		}
	}
	while ((argc) && (* argv)) 
	{
		if ((stream = efopen (* argv, "rb"))) 
		{
			if (heapitem >= heapsize) 
			{
				error (1, EMFILE, "Bailing Out!");
			}
			if ((heap [heapitem] = makeitem (stream, * argv, linesize))) 
			{
				heapitem++;
			}
		}
		argc--;
		argv++;
	}
	function (heap, heapitem, linesize, (void *)(comp), (void *)(swap));
	exit (0);
}

