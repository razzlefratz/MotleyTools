/*====================================================================*
 *
 *   oedit.c - object driven editor;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*"
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
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
#include "../tools/dataspec.c"
#include "../tools/basespec.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/memencode.c"
#include "../tools/hexpeek.c"
#include "../tools/hexdump.c"
#endif

/*====================================================================*
 *   constants;
 *--------------------------------------------------------------------*/

#define ODE_VERBOSE (1 << 0)
#define ODE_SILENCE (1 << 1)
#define ODE_HEADERS (1 << 2)

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
		"qvw:", 
		"file base [type item] [type item] [...]\n\n\t  where type is 'byte'|'word'|'long'|'huge'|'data'|'zero'|'fill'|'skip'", 
		"object driven editor", 
		"q\tquiet moedit", 
		"v[v]\tverbose moedit", 
		"w n\twindow is n bytes [32]", 
		(char const *) (0)
	}; 
	file file; 
	byte * memory; 
	unsigned extent = 0; 
	unsigned offset = 0; 
	unsigned origin = 0; 
	unsigned window = 32; 
	flag_t flags = (flag_t)(0); 
	signed c; 
	opterr = 1; 
	while (~ (c = getoptv (argc, argv, optv))) 
	{ 
		switch (c) 
		{ 
		case 'q': 
			_setbits (flags, ODE_SILENCE); 
			break; 
		case 'v': 
			if (_anyset (flags, ODE_VERBOSE)) 
			{ 
				_setbits (flags, ODE_HEADERS); 
			} 
			_setbits (flags, ODE_VERBOSE); 
			break; 
		case 'w': 
			window = (unsigned)(uintspec (optarg, 0, UINT_MAX)); 
			_setbits (flags, ODE_VERBOSE); 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (!argc) 
	{ 
		error (1, ECANCELED, "No file."); 
	} 
	file.name = * argv; 
	if ((file.file = open (file.name, O_BINARY | O_RDONLY)) == - 1) 
	{ 
		error (1, errno, "%s", file.name); 
	} 
	if ((signed)(extent = lseek (file.file, 0, SEEK_END)) == - 1) 
	{ 
		error (1, errno, "%s", file.name); 
	} 
	if ((memory = malloc (extent)) == 0) 
	{ 
		error (1, errno, "Need %u bytes", extent); 
	} 
	if (lseek (file.file, 0, SEEK_SET)) 
	{ 
		error (1, errno, "%s", file.name); 
	} 
	if (read (file.file, memory, extent) != (signed)(extent)) 
	{ 
		error (1, errno, "%s", file.name); 
	} 
	close (file.file); 
	argc--; 
	argv++; 
	if (!argc) 
	{ 
		error (1, ECANCELED, "No offset"); 
	} 
	origin = offset = (unsigned)(basespec (* argv, 16, sizeof (offset))); 
	if (offset > extent) 
	{ 
		error (1, ECANCELED, "Offset %X exceeds extent %X", offset, extent); 
	} 
	argc--; 
	argv++; 
	if (!argc) 
	{ 
		_setbits (flags, ODE_VERBOSE); 
	} 
	while ((argc > 1) && (* argv)) 
	{ 
		offset += memencode (memory + offset, extent - offset, argv [0], argv [1]); 
		argc -= 2; 
		argv += 2; 
	} 
	if (argc) 
	{ 
		error (1, ECANCELED, "%s needs a value", * argv); 
	} 
	if ((file.file = open (file.name, O_BINARY | O_TRUNC | O_RDWR)) == - 1) 
	{ 
		error (1, errno, "%s", file.name); 
	} 
	if (write (file.file, memory, extent) < (signed)(extent)) 
	{ 
		error (1, errno, "%s", file.name); 
	} 
	close (file.file); 
	if (_anyset (flags, ODE_VERBOSE)) 
	{ 
		if (_anyset (flags, ODE_HEADERS)) 
		{ 
			printf (HEXDUMP_HEADER); 
		} 
		hexpeek (memory, origin, offset, extent, window, stdout); 
	} 
	return (0); 
} 

