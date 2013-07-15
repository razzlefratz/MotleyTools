/*====================================================================*
 *
 *   hex2bin.c - hexadecimal to binary file concatenate;
 *
 *   copy one or more files to stdout; if no files are specified 
 *   then copy stdin to stdout;
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
#include <unistd.h>
#include <limits.h>
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
#include "../tools/error.c"
#endif

/*====================================================================*
 *
 *   void function (char const * filename);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (char const * filename) 

{ 
	byte byte; 
	unsigned line = 1; 
	unsigned digit = 0; 
	unsigned value = 0; 
	while (read (STDIN_FILENO, & byte, sizeof (byte)) > 0) 
	{ 
		if (isspace (byte)) 
		{ 
			if (byte == '\n') 
			{ 
				line++; 
			} 
			continue; 
		} 
		if ((byte >= '0') && (byte <= '9')) 
		{ 
			value *= 16; 
			value += byte - '0'; 
			if (digit++ & 1) 
			{ 
				write (STDOUT_FILENO, & value, sizeof (char)); 
				value = 0; 
			} 
			continue; 
		} 
		if ((byte >= 'A') && (byte <= 'F')) 
		{ 
			value *= 16; 
			value += 10; 
			value += byte - 'A'; 
			if (digit++ & 1) 
			{ 
				write (STDOUT_FILENO, & value, sizeof (char)); 
				value = 0; 
			} 
			continue; 
		} 
		if ((byte >= 'a') && (byte <= 'f')) 
		{ 
			value *= 16; 
			value += 10; 
			value += byte - 'a'; 
			if (digit++ & 1) 
			{ 
				write (STDOUT_FILENO, & value, sizeof (char)); 
				value = 0; 
			} 
			continue; 
		} 
		error (1, ENOTSUP, "Illegal hex digit '%c' (0x%02X) on line %d", byte, byte, line); 
	} 
	if (digit & 1) 
	{ 
		error (1, ENOTSUP, "Odd digit count (%d) from %s", digit, filename); 
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
		"", 
		PUTOPTV_S_FUNNEL, 
		"hexadecimal to binary file concatenate", 
		(char const *)(0)
	}; 
	signed c; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
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
		function ("standard input"); 
	} 
	while ((argc) && (* argv)) 
	{ 
		if (!freopen (* argv, "rb", stdin)) 
		{ 
			error (1, errno, "%s", * argv); 
		} 
		function (* argv); 
		argc--; 
		argv++; 
	} 
	return (0); 
} 

