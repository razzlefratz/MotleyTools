/*====================================================================*
 *
 *   radix.c - radix convertion utility;
 *
 *   convert one or more numbers from one radix to another;
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
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>

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
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/error.c"
#endif

/*====================================================================*
 *   program constants;   
 *--------------------------------------------------------------------*/

#define DIGITS_MAX 36

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
	static char const * optv [] = 
	{
		"f:t:h",
		"[options] number [number] [...]",
		"convert one or more numbers from one radix (number base) to another",
		"f n\tfrom base n in range 2 to 36 ",
		"t n\tto base n in range 2 to 36 ",
		(char const *)(0)
	};
	char number [DIGITS_MAX+1];
	unsigned base1 = 10;
	unsigned base2 = 10;
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'f':
			base1 = uintspec (optarg, RADIX_MIN, RADIX_MAX);
			break;
		case 't':
			base2 = uintspec (optarg, RADIX_MIN, RADIX_MAX);
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	while ((argc) && (* argv)) 
	{
		char const * string = * argv;
		unsigned index = sizeof (number);
		unsigned digit;
		uint64_t value = 0;
		while (*string) 
		{
			if ((digit = todigit (*string)) < base1) 
			{
				value *= base1;
				value += digit;
				string++;
				continue;
			}
			error (1, EINVAL, "%s", * argv);
		}
		number [--index] = (char)(0);
		do 
		{
			number [--index] = DIGITS_B36 [value % base2];
			value /= base2;
		}
		while ((index) && (value));
		printf ("%s %s\n", * argv, &number [index]);
		argc--;
		argv++;
	}
	exit (0);
}

