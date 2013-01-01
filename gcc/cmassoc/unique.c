/*====================================================================*
 *
 *   uniq.c - reduce duplicate record occurances utility;
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
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"

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
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/match.c"
#endif

/*====================================================================*
 *   program definitions and declarations;
 *--------------------------------------------------------------------*/

#define UNIQ_B_NUMBER (1 << 0)
#define UNIQ_B_UNIQUE (1 << 1)
#define UNIQ_B_MULT   (1 << 2)

/*====================================================================*
 *
 *   void put (size_t count, char *string, flag_t flag, FILE * ofp)
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static void put (size_t count, char * string, flag_t flags, FILE * fp) 

{
	if (_anyset (flags, UNIQ_B_NUMBER)) 
	{
		fprintf (fp, "%4lu ", (unsigned long)(count));
	}
	fputs (string, stdout);
	return;
}


/*====================================================================*
 *
 *   void function (size_t length, flag_t flag, FILE * ifp, FILE *ofp);
 *
 *   read consecutive duplicate lines from ifp and write one line to ofp;
 *
 *   #define  UNIQ_B_NUMBER 0x0001  output all occurances with count;
 *   #define  UNIQ_B_UNIQUE 0x0002  output only unique occurances;
 *   #define  UNIQ_B_MULT   0x0004  output only duplicate occurances;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static void function (size_t length, flag_t flags) 

{
	struct line 
	{
		struct line * next;
		char * text;
	};
	struct line one;
	struct line two;
	struct line * old = two.next = (struct line *) (&one);
	struct line * new = one.next = (struct line *) (&two);
	size_t count = 1;
	one.text = (char *)(malloc (length));
	two.text = (char *)(malloc (length));
	one.text [0] = (char) (0);
	two.text [0] = (char) (0);
	while (fgets (new->text, length, stdin)) 
	{
		char * np = new->text;
		char * op = old->text;
		while ((*np) && (*op) && (*np == *op)) 
		{
			np++;
			op++;
		}
		if ((*np) || (*op)) 
		{
			if (_anyset (flags, UNIQ_B_UNIQUE)) 
			{
				if (count == 1) 
				{
					put (count, new->text, flags, stdout);
				}
			}
			else if (_anyset (flags, UNIQ_B_MULT)) 
			{
				if (count != 1) 
				{
					put (count, new->text, flags, stdout);
				}
			}
			else 
			{
				put (count, new->text, flags, stdout);
			}
			count = 0;
		}
		old = old->next;
		new = new->next;
		count++;
	}
	return;
}


/*====================================================================*
 *   
 *   int main (int argc, char const * argv []);
 *   
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"cdr:u",
		PUTOPTV_S_FUNNEL,
		"output unique lines",
		"c\tcount occurances",
		"d\toutput only duplicate lines",
		"r n\tmaximum line length is (n) bytes [" LITERAL (_LINESIZE) "]",
		"u\toutput only unique lines",
		(char const *) (0)
	};
	size_t length = _LINESIZE;
	flag_t flags = (flag_t) (0);
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'r':
			length = uintspec (optarg, 1, SHRT_MAX);
			break;
		case 'u':
			_setbits (flags, UNIQ_B_UNIQUE);
			break;
		case 'd':
			_setbits (flags, UNIQ_B_MULT);
			break;
		case 'c':
			_setbits (flags, UNIQ_B_NUMBER);
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (!argc) 
	{
		function (length, flags);
	}
	while ((argc) && (* argv)) 
	{
		if (efreopen (* argv, "rb", stdin)) 
		{
			function (length, flags);
		}
		argc--;
		argv++;
	}
	exit (0);
}

