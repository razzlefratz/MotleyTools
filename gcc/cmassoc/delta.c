/*====================================================================*
 *
 *   delta.c - print difference between consecutive integers;
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
#include <ctype.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/efreopen.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/error_on_line.c"
#include "../tools/error.c"
#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define DIGITS 6

/*====================================================================*
 *
 *   void function ();
 *
 *   read stdin and write stdout; read consecutive unsigned decimal 
 *   integer values and print the difference between them;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function(char const * file, unsigned width, flag_t flags)

{
	char number[width +  1];
	unsigned prior = 0;
	unsigned value = 0;
	unsigned count = 0;
	unsigned line = 1;
	signed c = getc(stdin);
	while (c != EOF)
	{
		while (isspace(c))
		{
			if (c == '\n')
			{
				line++;
			}
			c = getc(stdin);
			continue;
		}
		if ((c == '#') || (c == ';'))
		{
			do 
			{
				c = getc(stdin);
			}
			while (nobreak(c));
			continue;
		}
		if (! isdigit(c))
		{
			c = getc(stdin);
			continue;
		}
		value = 0;
		while (isdigit(c))
		{
			value *= 10;
			value += c - '0';
			c = getc(stdin);
		}
		if (value < prior)
		{
			error_on_line (1, ENOTSUP, file, line, "%d less than %d", value, prior);
		}
		if (count)
		{
			unsigned digit = width;
			unsigned delta = value - prior;
			number [digit] = (char) (0);
			while (digit)
			{
				number [-- digit] = DIGITS_DEC[delta % 10];
				delta /= 10;
			}
			while (digit < width)
			{
				putc (number[digit++], stdout);
			}
			putc ('\n', stdout);
		}
		prior = value;
		count++;
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

int main(int argc, char const * argv[])

{
	static char const * optv[] = 
	{
		"w",
		PUTOPTV_S_FUNNEL,
		"print difference between consecutive unsigned decimal integers",
		"w n\twidth in digits is (n) [" LITERAL(DIGITS) "]",
		(char const *) (0)
	};
	unsigned width = DIGITS;
	flag_t flags = (flag_t) (0);
	signed c;
	while (~ (c = getoptv(argc, argv, optv)))
	{
		switch (c)
		{
		case 'w':
			width = (unsigned) (uintspec(optarg, 1, 16));
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function ("stdin", width, flags);
	}
	while ((argc) && (* argv))
	{
		if (efreopen(* argv, "rb", stdin))
		{
			function (* argv, width, flags);
		}
		argc--;
		argv++;
	}
	return (0);
}

