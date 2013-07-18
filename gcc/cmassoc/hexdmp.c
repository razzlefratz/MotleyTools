/*====================================================================*
 *
 *   hexdmp.c - hexadecimal stream dump utility;
 *
 *   print one or more files on stdout in hexadecimal format; if no 
 *   files are specified on the command line then read from stdin;
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

#include <unistd.h>
#include <stdlib.h>
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
#include "../tools/error.c"
#endif

/*====================================================================*
 *
 *   signed function (signed extent, unsigned column);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function () 

{ 
	byte binary [RADIX_HEX]; 
	char buffer [sizeof (void *) + sizeof (void *)]; 
	size_t offset = 0; 
	size_t length = 0; 
	while ((length = read (STDIN_FILENO, & binary, sizeof (binary))) > 0) 
	{ 
		size_t memory = offset; 
		size_t column = sizeof (buffer); 
		while (column--) 
		{ 
			buffer [column] = DIGITS_HEX [memory % RADIX_HEX]; 
			memory /= RADIX_HEX; 
		} 

#if 0

		if ((offset) && ((offset % 0x0400) == 0)) 
		{ 
			write (STDOUT_FILENO, "\n", sizeof (char)); 
		} 

#endif

		write (STDOUT_FILENO, buffer, sizeof (buffer)); 
		write (STDOUT_FILENO, " ", sizeof (char)); 
		for (column = 0; column < length; column++) 
		{ 
			byte byte = binary [column]; 
			write (STDOUT_FILENO, " ", sizeof (char)); 
			write (STDOUT_FILENO, & DIGITS_HEX [(byte >> 4) & 0x0F], sizeof (char)); 
			write (STDOUT_FILENO, & DIGITS_HEX [(byte >> 0) & 0x0F], sizeof (char)); 
		} 
		while (column < sizeof (binary)) 
		{ 
			write (STDOUT_FILENO, " ", sizeof (char)); 
			write (STDOUT_FILENO, " ", sizeof (char)); 
			write (STDOUT_FILENO, " ", sizeof (char)); 
			column++; 
		} 
		write (STDOUT_FILENO, " ", sizeof (char)); 
		write (STDOUT_FILENO, " ", sizeof (char)); 
		for (column = 0; column < length; column++) 
		{ 
			char byte = binary [column]; 
			write (STDOUT_FILENO, isprint (byte)? & byte: ".", sizeof (char)); 
		} 
		write (STDOUT_FILENO, "\n", sizeof (char)); 
		offset += sizeof (binary); 
	} 
	write (STDOUT_FILENO, "\n", sizeof (char)); 
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
		"", 
		PUTOPTV_S_FUNNEL, 
		"hexadecimal stream dump utility", 
		(char const *)(0)
	}; 
	signed c; 
	while (~ (c = getoptv (argc, argv, optv))) 
	{ 
		switch (c) 
		{ 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (!argc) 
	{ 
		function (); 
	} 
	while ((argc) && (* argv)) 
	{ 
		if (efreopen (* argv, "rb", stdin)) 
		{ 
			function (); 
		} 
		argc--; 
		argv++; 
	} 
	exit (0); 
} 

