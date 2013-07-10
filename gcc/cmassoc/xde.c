/*====================================================================*
 *
 *   xde.c - XML driven editor;
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
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

/*====================================================================*
 *  custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../nodes/nodes.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/emalloc.c"
#include "../tools/todigit.c"
#include "../tools/hexdump.c"
#include "../tools/uintspec.c"
#include "../tools/indent.c"
#endif

#ifndef MAKEFILE
#include "../nodes/xmledit.c"
#include "../nodes/xmlfree.c"
#include "../nodes/xmlnode.c"
#include "../nodes/xmlopen.c"
#include "../nodes/xmlschema.c"
#include "../nodes/xmlsample.c"
#include "../nodes/xmlscan.c"
#include "../nodes/reorder.c"
#endif

#ifndef MAKEFILE
#include "../strlib/svindex.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define XDE_VERBOSE (1 << 0)
#define XDE_SILENCE (1 << 1)

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
		"qvsx", 
		"datafile xmlfile [xmlfile] [...]", 
		"data XML editor", 
		"o\tprint schema", 
		"q\tquiet mode", 
		"v\tverbose mode", 
		(char const * )(0)
	}; 
	struct node * markup; 
	char const * filename; 
	byte * buffer; 
	signed length; 
	signed fd; 
	flag_t flags = (flag_t)(0); 
	signed c; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 'q': 
			_setbits (flags, XDE_SILENCE); 
			break; 
		case 'v': 
			_setbits (flags, XDE_VERBOSE); 
			break; 
		case 's': 
			xmlsample (); 
			return (0); 
		case 'x': 
			xmlschema (); 
			return (0); 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (! argc) 
	{ 
		error (1, ECANCELED, "No data file given"); 
	} 
	filename = * argv; 
	if ((fd = open (filename, O_BINARY | O_RDONLY)) == - 1) 
	{ 
		error (1, errno, FILE_CANTOPEN, filename); 
	} 
	if ((length = lseek (fd, 0, SEEK_END)) == - 1) 
	{ 
		error (1, errno, FILE_CANTSIZE, filename); 
	} 
	if (lseek (fd, 0, SEEK_SET)) 
	{ 
		error (1, errno, FILE_CANTHOME, filename); 
	} 
	if (! (buffer = malloc (length+ 1))) 
	{ 
		error (1, errno, "Need %d bytes", length); 
	} 
	if (read (fd, buffer, length) < length) 
	{ 
		error (1, errno, FILE_CANTREAD, filename); 
	} 
	close (fd); 
	argc-- ; 
	argv++ ; 
	while ((argc) && (* argv)) 
	{ 
		markup = xmlopen (* argv); 
		xmledit (markup, buffer, length); 
		xmlfree (markup); 
		argc-- ; 
		argv++ ; 
	} 
	if (_anyset (flags, XDE_VERBOSE)) 
	{ 
		hexdump (buffer, 0, length, stdout); 
	} 
	if ((fd = open (filename, O_BINARY | O_WRONLY)) == - 1) 
	{ 
		error (1, errno, FILE_CANTOPEN, filename); 
	} 
	if (write (fd, buffer, length) < length) 
	{ 
		error (1, errno, FILE_CANTSAVE, filename); 
	} 
	close (fd); 
	return (0); 
} 

