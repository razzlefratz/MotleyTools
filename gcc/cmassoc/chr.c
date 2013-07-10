/*====================================================================*
 *
 *   chr.c - file character counter program;
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
#include <limits.h>
#include <memory.h>
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
#include "../sv/sv_ascii.c"
#endif

/*====================================================================*
 *   common program constants;
 *--------------------------------------------------------------------*/

#define CHR_B_LOWER (1 << 0)
#define CHR_B_UPPER (1 << 1)
#define CHR_B_TABLE (CHR_B_DEC|CHR_B_OCT|CHR_B_HEX)
#define CHR_B_HEX (1 << 2)
#define CHR_B_DEC (1 << 3)
#define CHR_B_OCT (1 << 4)

/*====================================================================*
 *
 *   void function (flag_t flags) 
 *
 *   display() counts the occurances of each character found in the input
 *   file and displays a tabulated distribution to the output file;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (flag_t flags) 

{ 
	extern char const * sv_ascii []; 
	char const * format = (char const * )(0); 
	unsigned table [UCHAR_MAX + 1]; 
	unsigned row; 
	unsigned rows; 
	unsigned max = SIZEOF (table); 
	unsigned min = 0; 
	unsigned col = 8; 
	signed c; 
	if ((flags & (CHR_B_LOWER | CHR_B_UPPER)) == (CHR_B_LOWER)) 
	{ 
		max = 0x0080; 
	} 
	if ((flags & (CHR_B_LOWER | CHR_B_UPPER)) == (CHR_B_UPPER)) 
	{ 
		min = 0x0080; 
	} 
	if (_anyset (flags, CHR_B_TABLE)) 
	{ 
		for (c = 0; (unsigned)(c) < SIZEOF (table); c++ ) 
		{ 
			table [c] = c; 
		} 
	} 
	else 
	{ 
		memset (table, 0, sizeof (table)); 
		while ((c = fgetc (stdin)) != EOF) 
		{ 
			table [(unsigned)(c)]++ ; 
		} 
	} 
	if (_anyset (flags, CHR_B_DEC)) 
	{ 
		format = "  %3d %-3s"; 
	} 
	else if (_anyset (flags, CHR_B_OCT)) 
	{ 
		format = "  %03o %-3s"; 
	} 
	else if (_anyset (flags, CHR_B_HEX)) 
	{ 
		format = "   %02X %-3s"; 
	} 
	else 
	{ 
		format = " %6d %-3s"; 
	} 
	rows = (max - min + col - 1) / (col); 
	printf ("\n"); 
	for (row = 0; row < rows; row++ ) 
	{ 
		for (c = min + row; (unsigned)(c) < max; c += rows) 
		{ 
			printf (format, table [c], sv_ascii [c]); 
		} 
		printf ("\n"); 
	} 
	printf ("\n"); 
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
		"adlouxt", 
		PUTOPTV_S_DIVINE, 
		"tabulate character occurances in text file", 
		"a\tfull ASCII character set", 
		"d\tprint decimal character codes", 
		"l\tlower ASCII character set only", 
		"u\tupper ASCII character set only", 
		"o\tprint octal character codes", 
		"t\tprint character table", 
		"x\tprint hexadecimal character codes", 
		(char const * )(0)
	}; 
	flag_t flags = CHR_B_LOWER; 
	signed c; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 'a': 
			_setbits (flags, CHR_B_UPPER); 
			_setbits (flags, CHR_B_LOWER); 
			break; 
		case 'l': 
			_clrbits (flags, CHR_B_UPPER); 
			_setbits (flags, CHR_B_LOWER); 
			break; 
		case 'u': 
			_setbits (flags, CHR_B_UPPER); 
			_clrbits (flags, CHR_B_LOWER); 
			break; 
		case 'd': 
			_clrbits (flags, CHR_B_OCT | CHR_B_HEX); 
			_setbits (flags, CHR_B_DEC); 
			break; 
		case 'o': 
			_clrbits (flags, CHR_B_DEC | CHR_B_HEX); 
			_setbits (flags, CHR_B_OCT); 
			break; 
		case 'x': 
			_clrbits (flags, CHR_B_DEC | CHR_B_OCT); 
			_setbits (flags, CHR_B_HEX); 
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

