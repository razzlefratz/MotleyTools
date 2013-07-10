/*====================================================================*
 *
 *   hex.c - hexidecimal encode/decode utility;
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

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/efreopen.c"
#include "../tools/todigit.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/match.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define HEX_B_ENCODE (1 << 0)
#define HEX_B_DECODE (1 << 1)

/*====================================================================*
 *
 *   void encode(flag_t flag, FILE *ifp, FILE *ofp)
 *
 *   read stdin and write stdout; replace ascii control characters 
 *   and spaces and all non-ascii characters with ascii hexidecimal 
 *   octet notation in the form "%nn";
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void encode (flag_t flags) 

{ 
	signed c; 
	while ((c = getc (stdin)) != EOF) 
	{ 

#if 0

		if ((c <= 0x20) || (c >= 0x7F)) 

#else

		if (! isgraph (c)) 

#endif

		{ 
			putc ('%', stdout); 
			putc (DIGITS_HEX [(c >> 4) & 0x0F], stdout); 
			putc (DIGITS_HEX [(c >> 0) & 0x0F], stdout); 
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
 *   void decode(flag_t flags)
 *
 *   read stdin and write stdout; replace ascii hexidecimal octets, 
 *   in the form "%nn", with the equivalent ascii character code;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void decode (flag_t flags) 

{ 
	signed c; 
	signed upper; 
	signed lower; 
	unsigned value; 
	while ((c = getc (stdin)) != EOF) 
	{ 
		if (c != '%') 
		{ 
			putc (c, stdout); 
			continue; 
		} 
		if ((upper = getc (stdin)) == EOF) 
		{ 
			putc (c, stdout); 
			continue; 
		} 
		value = todigit (upper); 
		if (errno) 
		{ 
			putc (c, stdout); 
			putc (upper, stdout); 
			continue; 
		} 
		if ((lower = getc (stdin)) == EOF) 
		{ 
			putc (c, stdout); 
			putc (upper, stdout); 
			putc (lower, stdout); 
			continue; 
		} 
		value = (value << 4) + todigit (lower); 
		if (errno) 
		{ 
			putc (c, stdout); 
			putc (upper, stdout); 
			putc (lower, stdout); 
			continue; 
		} 
		putc (value, stdout); 
	} 
	return; 
} 

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

void function (flag_t flags) 

{ 
	signed c; 
	switch (flags & (HEX_B_ENCODE | HEX_B_DECODE)) 
	{ 
	case HEX_B_ENCODE: 
		encode (flags); 
		break; 
	case HEX_B_DECODE: 
		decode (flags); 
		break; 
	default: 
		while ((c = getc (stdin)) != EOF) 
		{ 
			putc (c, stdout); 
		} 
		break; 
	} 
	return; 
} 

/*====================================================================*
 *
 *  main program;
 *
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	static char const * optv [] = 
	{ 
		"deh", 
		PUTOPTV_S_FUNNEL, 
		"encode or decode text files in IETF hexidecimal octet format", 
		"d\tdecode files ", 
		"e\tencode files ", 
		(char const * )(0)
	}; 
	flag_t flags = (flag_t) (0); 
	signed c; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 'd': 
			_clrbits (flags, HEX_B_ENCODE); 
			_setbits (flags, HEX_B_DECODE); 
			break; 
		case 'e': 
			_clrbits (flags, HEX_B_DECODE); 
			_setbits (flags, HEX_B_ENCODE); 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (! argc) 
	{ 
		function (flags); 
	} 
	while ((argc) && (* argv)) 
	{ 
		if (efreopen (* argv, "rb", stdin)) 
		{ 
			function (flags); 
		} 
		argc-- ; 
		argv++ ; 
	} 
	exit (0); 
} 

