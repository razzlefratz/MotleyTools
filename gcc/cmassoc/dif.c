/*====================================================================*
 *
 *   dif.c - file comparison;
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

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../link/link.h"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/uintspec.c"
#include "../tools/efopen.c"
#include "../tools/efreopen.c"
#include "../tools/emalloc.c"
#include "../tools/todigit.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../link/makeitem.c"
#include "../link/queue.c"
#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define _SHOWALL   0x0001
#define _SHOWBREAK 0x0002
#define _WIDTH 68
#define DASH "--------------------------------------------------------------------------------"
#define SCAN "%04lu %-*.*s "
#define LINE "     %*.*s "

/*====================================================================*
 *
 *   char *next(char *string, FILE *fp);
 *
 *   This function returns a pointer to a string read from the standard
 *   input stream. Characters are read until a newline occurs, than all
 *   trailing spaces are removed and the string is terminated with NUL.
 *   NULL is returned on end-of-file or error.
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void *next (size_t line, LINK * ip, FILE * fp) 

{
	register signed c = (char) (0);
	char string [TEXTLINE_MAX];
	char *sp = string;
	char *cp = string;
	for (c = getc (fp); (c != EOF) && (c != '\n'); c = getc (fp)) 
	{
		if ((cp - string) < (sizeof (string) - 1)) 
		{
			*cp++ = (char) (c);
		}
		if ((c != ' ') && (c != '\t')) 
		{
			sp = cp;
		}
	}
	*sp = (char) (0);
	ip->name = (void *) (strdup (string));
	ip->data = (void *) (line);
	return ((c != EOF)? (void *) (ip->name): (void *) (0));
}


/*====================================================================*
 *
 *   LINK *find(LINK *list, LINK *item, int comp(void const *, void const *))
 *
 *   This function searches a circular linked list for the first occurance
 *   of an item and returns a pointer to the matching list element. NULL is
 *   returned of no matching element is found.
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

LINK *find (LINK * list, LINK * item, int comp (char const *, char const *)) 

{
	LINK *temp;
	if (list == (LINK *) (0)) 
	{
		return ((LINK *) (0));
	}
	if (item == (LINK *) (0)) 
	{
		return ((LINK *) (0));
	}
	if (item->name == (void *) (0)) 
	{
		return ((LINK *) (0));
	}
	if (*(char *) (item->name) == (char) (0)) 
	{
		return ((LINK *) (0));
	}
	for (temp = list->next; temp != list; temp = temp->next) 
	{
		if (temp->name == (void *) (0)) 
		{
			continue;
		}
		if (*(char *) (temp->name) == (char) (0)) 
		{
			continue;
		}
		if (comp (temp->name, item->name) == 0) 
		{
			return (temp);
		}
	}
	return ((LINK *) (0));
}


/*====================================================================*
 *
 *   void show(LINK *op, LINK *np, unsigned width, flag_t flags);
 *
 *   This function produces a side-by-side listing of two circular linked
 *   lists of different length. Corresponding list elements are output in
 *   pairs, and then discarded, until both lists are exhausted. Since one
 *   list will normally exhaust first, null lines are displayed until the
 *   the other list exhausts.
 *
 *   An exhausted list consists of one element that is not discarded. The
 *   last elements in each list are output as a pair just before exit. In
 *   this program, those elements are always identical.
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void show (LINK * op, LINK * np, int width, flag_t flag) 

{
	LINK *tp;
	if (_anyset (flag, _SHOWBREAK)) 
	{
		if ((op != op->next) || (np != np->next)) 
		{
			printf (LINE, width, width, DASH);
			printf (LINE, width, width, DASH);
			printf ("\n");
		}
	}
	while (op != op->next) 
	{
		tp = queue (op, op->next);
		printf (SCAN, (long unsigned) (tp->data), width, width, (char *) (tp->name));
		printf (LINE, width, width, "");
		printf ("\n");
		free (tp->name);
		free (tp);
	}
	while (np != np->next) 
	{
		tp = queue (np, np->next);
		printf (LINE, width, width, "");
		printf (SCAN, (long unsigned) (tp->data), width, width, (char *) (tp->name));
		printf ("\n");
		free (tp->name);
		free (tp);
	}
	if (_anyset (flag, _SHOWALL)) 
	{
		printf (SCAN, (long unsigned) (op->data), width, width, (char *) (op->name));
		printf (SCAN, (long unsigned) (np->data), width, width, (char *) (np->name));
		printf ("\n");
	}
	strcpy (op->name, "");
	strcpy (np->name, "");
	return;
}


/*====================================================================*
 *
 *   void func (size_t width, flag_t flag, FILE * ofp, FILE * nfp)
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (size_t width, flag_t flag, FILE * ofp, FILE * nfp) 

{
	LINK *op,
	*otp;
	LINK *np,
	*ntp;
	unsigned match;
	unsigned count;
	op = makeitem ((LINK *) (0), (LINK *) (0));
	np = makeitem ((LINK *) (0), (LINK *) (0));
	for (match = count = 1; next (count, op, ofp) != next (count, np, nfp); count++) 
	{
		if (*(char *)(op->name) == (char)(0)) 
		{
			continue;
		}
		if (*(char *)(np->name) == (char)(0)) 
		{
			continue;
		}
		if (strcmp (op->name, np->name) == 0) 
		{
			show (op, np, width, flag);
			continue;
		}
		if ((otp = find (op, np, strcmp)) != (void *) (0)) 
		{
			otp = queue (op, otp);
			show (otp, np, width, flag);
			op = queue (op, otp);
			match++;
			continue;
		}
		if ((ntp = find (np, op, strcmp)) != (void *) (0)) 
		{
			ntp = queue (np, ntp);
			show (op, ntp, width, flag);
			np = queue (np, ntp);
			match++;
			continue;
		}
		op = queue (op, makeitem ((void *) (0), (void *) (0)));
		np = queue (np, makeitem ((void *) (0), (void *) (0)));
	}
	show (op, np, width, flag);
	if (!match) 
	{
		printf ("\n no match\n");
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
		"w:abh",
		"file1 file2",
		"displays the differences between two text files",
		"a\tshow all lines",
		"b\tshow line breaks",
		"w n\tscreen width is n characters",
		(char const *)(0)
	};
	FILE *ofp,
	*nfp;
	size_t width = _WIDTH;
	flag_t flag = NONE;
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'a':
			_setbits (flag, _SHOWALL);
			break;
		case 'b':
			_setbits (flag, _SHOWBREAK);
			break;
		case 'w':
			width = uintspec (optarg, 0, _WIDTH);
			break;
		case 'h':
			putoptv (optv);
			exit (0);
		default:
			exit (1);
		}
	}
	argc -= optind;
	argv += optind;
	if (argc == 2) 
	{
		ofp = efopen (* argv++, "rb");
		nfp = efopen (* argv++, "rb");
		function (width >> 1, flag, ofp, nfp);
	}
	exit (0);
}

