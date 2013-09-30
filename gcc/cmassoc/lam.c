/*====================================================================*
 *
 *   lam.c - laminate files;
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
#include <ctype.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../link/link.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/emalloc.c"
#endif

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
	char const * optv [] =
	{
		"f:nq:stv",
		PUTOPTV_S_FUNNEL,
		"laminate files",
		"f c\tseparate fields with (c)",
		"n\tseparate with newlines",
		"q c\tenclose fields in (c)",
		"s\tseparate with spaces",
		"t\tseparate with tabs",
		"v\tprint as CSV file",
		(char const *) (0)
	};
	typedef struct link
	{
		struct link * next;
		FILE * file;
	}
	LINK;
	struct link * item = (LINK *) (0);
	struct link * list = (LINK *) (0);
	unsigned quote = (char) (0);
	unsigned space = (char) (0);
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'f':
			space = * optarg;
			break;
		case 'n':
			space = '\n';
			break;
		case 'q':
			quote = * optarg;
			break;
		case 's':
			space = ' ';
			break;
		case 't':
			space = '\t';
			break;
		case 'v':
			space = ',';
			quote = '\"';
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		error (1, EINVAL, "No files given");
	}
	while (* argv)
	{
		item = NEW (LINK);
		item->file = fopen (* argv, "rb");
		if (list)
		{
			item->next = list->next;
			list->next = item;
		}
		else 
		{
			item->next = item;
		}
		list = item;
		argv++;
	}
	while (argc)
	{
		item = item->next;
		if (quote)
		{
			putc (quote, stdout);
		}
		if (item->file)
		{
			for (c = getc (item->file); nobreak (c); c = getc (item->file))
			{
				putc (c, stdout);
			}
			if (c == EOF)
			{
				fclose (item->file);
				item->file = (FILE *) (0);
				argc--;
			}
		}
		if (quote)
		{
			putc (quote, stdout);
		}
		if (item == list)
		{
			putc ('\n', stdout);
			continue;
		}
		if (space)
		{
			putc (space, stdout);
			continue;
		}
	}
	while (list->next != list)
	{
		item = list->next;
		list->next = item->next;
		item->next = item;
		free (item);
	}
	free (list);
	exit (0);
}

