/*====================================================================*
 *
 *   octal.c - octal encode/decode utility;
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

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../chrlib/chrlib.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/efreopen.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

#ifndef MAKEFILE
#include "../chrlib/chrindex.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define OCT_B_ENCODE (1 << 0)
#define OCT_B_DECODE (1 << 1)

/*====================================================================*
 *
 *   void encode (flag_t flags)
 *
 *   read stdin and write stdout; replace ascii control characters and spaces
 *   and all non-ascii characters with ascii octal trigraphs of the form
 *   "\nnn";
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void encode (flag_t flags)

{
	int c;
	while ((c = getc (stdin)) != EOF)
	{

#ifdef NEEDED

		if ((c <= 0x20) || (c >= 0x7F)) 

#else

		if (! isgraph (c)) 

#endif

		{
			putc ('\\', stdout);
			putc (DIGITS_OCT [(c >> 6) & 0x03], stdout);
			putc (DIGITS_OCT [(c >> 3) & 0x07], stdout);
			putc (DIGITS_OCT [(c >> 0) & 0x07], stdout);
		}
		else 
		{
			putc (c, stdout);
		}
	}
	return;
}

/*====================================================================*
 *
 *   void decode (flag_t flags)
 *
 *   read stdin and write stdout; replace ascii octal trigraphs, in the form
 *   "\nnn", with the equivalent ascii character code;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void decode (flag_t flags)

{
	int c1,
	c2,
	c3;
	int o1,
	o2,
	o3;
	int c;
	while ((c = getc (stdin)) != EOF)
	{
		if (c != '\\')
		{
			putc (c, stdout);
		}
		else if ((c1 = getc (stdin)) == EOF)
		{
			putc (c, stdout);
		}
		else if ((o1 = chrindex (DIGITS_OCT, c1)) > 0x03)
		{
			putc (c, stdout);
			putc (c1, stdout);
		}
		else if ((c2 = getc (stdin)) == EOF)
		{
			putc (c, stdout);
			putc (c1, stdout);
		}
		else if ((o2 = chrindex (DIGITS_OCT, c1)) > 0x07)
		{
			putc (c, stdout);
			putc (c1, stdout);
			putc (c2, stdout);
		}
		else if ((c3 = getc (stdin)) == EOF)
		{
			putc (c, stdout);
			putc (c1, stdout);
			putc (c2, stdout);
		}
		else if ((o3 = chrindex (DIGITS_OCT, c3)) > 0x07)
		{
			putc (c, stdout);
			putc (c1, stdout);
			putc (c2, stdout);
			putc (c3, stdout);
		}
		else 
		{
			c = (o1 << 6) + (o2 << 3) + (o3 << 0);
			putc (c, stdout);
		}
	}
	return;
}

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [])

{
	static char const * optv [] = 
	{
		"de",
		PUTOPTV_S_FUNNEL,
		"encode or decode text files using ANSI octal trigraph format",
		"d\tdecode files ",
		"e\tencode files ",
		NULL
	};
	flag_t flags = (flag_t) (0);
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'd':
			_clrbits (flags, OCT_B_ENCODE);
			_setbits (flags, OCT_B_DECODE);
			break;
		case 'e':
			_clrbits (flags, OCT_B_DECODE);
			_setbits (flags, OCT_B_ENCODE);
			break;
		default: 
			exit (1);
		}
	}
	argc -= optind;
	argv += optind;
	while ((argc) && (* argv))
	{
		if (efreopen (* argv, "rb", stdin))
		{
			switch (flags & (OCT_B_ENCODE | OCT_B_DECODE))
			{
			case OCT_B_ENCODE:
				encode (flags);
				break;
			case OCT_B_DECODE:
				decode (flags);
				break;
			default: 
				while ((c = getc (stdin)) != EOF)
				{
					putc (c, stdout);
				}
				break;
			}
		}
		argc--;
		argv++;
	}
	exit (0);
}

