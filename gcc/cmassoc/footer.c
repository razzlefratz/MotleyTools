/*====================================================================*
 *
 *   footer.c - output file footer;
 *
 *   copy last n lines from one or more text files to stdout;
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
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../linux/linux.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/efreopen.c"
#include "../tools/emalloc.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#endif

#ifndef MAKEFILE
#include "../linux/getviewport.c"
#endif

/*====================================================================*
 *
 *   void function (signed count, signed width);
 *
 *   copy the last n lines of stdin to stdout; this implementation makes
 *   one pass through the file, expanding a circular linked list of text
 *   buffers until n buffers are allocated; after that existing buffers
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (signed count, signed width)

{
	struct line
	{
		struct line * next;
		char * text;
		signed size;
	};
	struct line * tail;
	struct line * temp;
	signed c = getc (stdin);
	tail = NEW (struct line);
	tail->text = STR (width);
	tail->next = tail;
	tail->size = 0;
	while (c != EOF)
	{
		if (tail->size < width)
		{
			tail->text [tail->size++] = c;
		}
		if (c == '\n')
		{
			tail->text [tail->size++] = c;
			if (count)
			{
				temp = NEW (struct line);
				temp->text = STR (width);
				temp->next = tail->next;
				tail->next = temp;
				count--;
			}
			tail = tail->next;
			tail->size = 0;
		}
		c = getc (stdin);
	}
	for (temp = tail->next; temp != tail; temp = temp->next)
	{
		for (width = 0; width < temp->size; width++)
		{
			putc (temp->text [width], stdout);
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
		"l:w:",
		PUTOPTV_S_FILTER,
		"copy one or more file footers to stdout",
		"l n\tdisplay line count is (n) [" LITERAL (VT_LINES) "]",
		"w n\tdisplay line width is (n) [" LITERAL (VT_LIMIT) "]",
		(char const *) (0)
	};
	unsigned lines = VT_LINES;
	unsigned width = VT_LIMIT;
	signed c;
	getviewport (& lines, & width);
	lines--;
	lines--;
	width--;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'l':
			lines = uintspec (optarg, 1, SHRT_MAX);
			break;
		case 'w':
			width = uintspec (optarg, 1, SHRT_MAX);
			break;
		default: 
			break;
		}
	};
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function (lines, width);
	}
	while ((argc) && (* argv))
	{
		if (efreopen (* argv, "rb", stdin))
		{
			function (lines, width);
		}
		argc--;
		argv++;
	}
	exit (0);
}

