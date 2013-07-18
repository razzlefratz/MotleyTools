/*====================================================================*
 *
 *   odc.c - object driven compare;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *   Contributor(s):
 *      Nathan Houghton <nathan@brainwerk.org>
 *	Charles Maier <cmaier@cmassoc.net>
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/getoptv.h"
#include "../tools/number.h"
#include "../tools/memory.h"
#include "../tools/error.h"
#include "../tools/flags.h"
#include "../tools/chars.h"
#include "../tools/sizes.h"
#include "../files/files.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/hexview.c"
#include "../tools/hexoffset.c"
#include "../tools/error.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define ODC_VERBOSE (1 << 0)
#define ODC_SILENCE (1 << 1)

/*====================================================================*
 *
 *   void report (char const * filename [], off_t offset []);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void report (char const * filename [], off_t offset []) 

{ 
	off_t extent [2]; 
	unsigned file; 
	for (file = 0; file < SIZEOF (extent); file++) 
	{ 
		struct stat statinfo; 
		if (stat (filename [file], & statinfo) == - 1) 
		{ 
			error (1, errno, FILE_CANTSIZE, filename [file]); 
		} 
		extent [file] = statinfo.st_size; 
		if (offset [file] < extent [file]) 
		{ 
			error (0, 0, "file %s exceeds definition by " OFF_T_SPEC " bytes", filename [file], extent [file] - offset [file]); 
		} 
		if (offset [file] > extent [file]) 
		{ 
			error (0, 0, "definition exceeds file %s by " OFF_T_SPEC " bytes", filename [file], offset [file] - extent [file]); 
		} 
	} 
	if (extent [0] > extent [1]) 
	{ 
		error (0, 0, "file %s exceeds file %s by " OFF_T_SPEC " bytes", filename [0], filename [1], extent [0] - extent [1]); 
	} 
	if (extent [1] > extent [0]) 
	{ 
		error (0, 0, "file %s exceeds file %s by " OFF_T_SPEC " bytes", filename [1], filename [0], extent [1] - extent [0]); 
	} 
	return; 
} 

/*====================================================================*
 *   
 *   void function (char const * filename [], flag_t flags);
 *   
 *   read definition file to determine the size of next object;
 *   read next object from each binary file and compare; report
 *   differences;
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (char const * filename [], flag_t flags) 

{ 
	off_t origin [2]; 
	off_t offset [2]; 
	file_t fd [2]; 
	unsigned object = 0; 
	unsigned lineno = 1; 
	unsigned file; 
	signed length = 0; 
	signed c; 
	char memory [_ADDRSIZE + 1]; 
	char symbol [_NAMESIZE]; 
	char string [_LINESIZE]; 
	char * sp; 
	memset (origin, 0, sizeof (origin)); 
	for (file = 0; file < SIZEOF (fd); file++) 
	{ 
		if ((fd [file] = open (filename [file], O_BINARY | O_RDONLY)) == - 1) 
		{ 
			error (1, errno, "%s", filename [file]); 
		} 
	} 
	while ((c = getc (stdin)) != EOF) 
	{ 
		if ((c == '#') || (c == ';')) 
		{ 
			do 
			{ 
				c = getc (stdin); 
			} 
			while (nobreak (c)); 
			lineno++; 
			continue; 
		} 
		if (isspace (c)) 
		{ 
			if (c == '\n') 
			{ 
				lineno++; 
			} 
			continue; 
		} 
		if ((c == '+') || (c == '-')) 
		{ 
			do 
			{ 
				c = getc (stdin); 
			} 
			while (isblank (c)); 
		} 
		length = 0; 
		while (isdigit (c)) 
		{ 
			length *= 10; 
			length += c - '0'; 
			c = getc (stdin); 
		} 
		while (isblank (c)) 
		{ 
			c = getc (stdin); 
		} 
		sp = symbol; 
		if (isalpha (c) || (c == '_')) 
		{ 
			do 
			{ 
				* sp++ = (char)(c); 
				c = getc (stdin); 
			} 
			while (isident (c)); 
		} 
		while (isblank (c)) 
		{ 
			c = getc (stdin); 
		} 
		if (c == '[') 
		{ 
			* sp++ = (char)(c); 
			c = getc (stdin); 
			while (isblank (c)) 
			{ 
				c = getc (stdin); 
			} 
			while (isdigit (c)) 
			{ 
				* sp++ = (char)(c); 
				c = getc (stdin); 
			} 
			while (isblank (c)) 
			{ 
				c = getc (stdin); 
			} 
			* sp = (char)(0); 
			if (c != ']') 
			{ 
				error (1, EINVAL, "Have '%s' but need ']' on line %d", symbol, lineno); 
			} 
			* sp++ = (char)(c); 
			c = getc (stdin); 
		} 
		* sp = (char)(0); 
		while (isblank (c)) 
		{ 
			c = getc (stdin); 
		} 
		sp = string; 
		while (nobreak (c)) 
		{ 
			* sp++ = (char)(c); 
			c = getc (stdin); 
		} 
		* sp = (char)(0); 
		if (length) 
		{ 

#if defined (WIN32)

			char * buffer [2]; 
			buffer [0] = (char *)(emalloc (length)); 
			buffer [1] = (char *)(emalloc (length)); 

#else

			byte buffer [2] [length]; 

#endif

			if ((read (fd [0], buffer [0], length) == length) && (read (fd [1], buffer [1], length) == length)) 
			{ 
				if (memcmp (buffer [0], buffer [1], length)) 
				{ 
					if (!object++) 
					{ 
						for (c = 0; c < _ADDRSIZE + 65; c++) 
						{ 
							putc ('-', stdout); 
						} 
						putc ('\n', stdout); 
					} 
					printf ("%s %d %s\n", hexoffset (memory, sizeof (memory), offset [0]), length, symbol); 
					for (c = 0; c < _ADDRSIZE; c++) 
					{ 
						putc ('-', stdout); 
					} 
					printf (" %s\n", filename [0]); 
					hexview (buffer [0], offset [0], length, stdout); 
					for (c = 0; c < _ADDRSIZE; c++) 
					{ 
						putc ('-', stdout); 
					} 
					printf (" %s\n", filename [1]); 
					hexview (buffer [1], offset [1], length, stdout); 
					for (c = 0; c < _ADDRSIZE + 65; c++) 
					{ 
						putc ('-', stdout); 
					} 
					putc ('\n', stdout); 
				} 
			} 

#if defined (WIN32)

			free (buffer [0]); 
			free (buffer [1]); 

#endif

		} 
		offset [0] += length; 
		offset [1] += length; 
		lineno++; 
	} 
	offset [0] += origin [0]; 
	offset [1] += origin [1]; 
	if (_allclr (flags, ODC_SILENCE)) 
	{ 
		report (filename, offset); 
	} 
	close (fd [0]); 
	close (fd [1]); 
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
		"f:qv", 
		"file file", 
		"object driven compare", 
		"f f\tobject definition file", 
		"q\tquiet mode", 
		"v\tverbose mode", 
		(char const *)(0)
	}; 
	flag_t flags = (flag_t)(0); 
	signed c; 
	while (~ (c = getoptv (argc, argv, optv))) 
	{ 
		switch (c) 
		{ 
		case 'f': 
			if (!freopen (optarg, "rb", stdin)) 
			{ 
				error (1, errno, "%s", optarg); 
			} 
			break; 
		case 'q': 
			_setbits (flags, ODC_SILENCE); 
			break; 
		case 'v': 
			_setbits (flags, ODC_VERBOSE); 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (argc != 2) 
	{ 
		error (1, 0, "Need two files to compare."); 
	} 
	function (argv, flags); 
	return (0); 
} 

