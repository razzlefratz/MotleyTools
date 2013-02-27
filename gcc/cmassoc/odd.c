/*====================================================================*
 *
 *   odd.c - object driven dump utility;
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
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/getoptv.h"
#include "../tools/putoptv.h"
#include "../tools/version.h"
#include "../tools/memory.h"
#include "../tools/number.h"
#include "../tools/error.h"
#include "../tools/chars.h"
#include "../tools/flags.h"
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

#define ODD_VERBOSE  (1 << 0)
#define ODD_SILENCE  (1 << 1)

/*====================================================================*
 *
 *   static void dump (int fd, char const * symbol, off_t offset, byte const * buffer, signed length);
 *
 *
 *
 *--------------------------------------------------------------------*/

static void dump (int fd, char const * symbol, off_t offset, byte const * buffer, signed length) 

{
	static unsigned object = 0;
	char memory [_ADDRSIZE + 1];
	char c;
	if (!object++) 
	{
		for (c = 0; c < _ADDRSIZE + 65; c++) 
		{
			putc ('-', stdout);
		}
		putc ('\n', stdout);
	}
	printf ("%s %u %s\n", hexoffset (memory, sizeof (memory), offset), length, symbol);
	hexview (buffer, offset, length, stdout);
	for (c = 0; c < _ADDRSIZE + 65; c++) 
	{
		putc ('-', stdout);
	}
	putc ('\n', stdout);
	return;
}


/*====================================================================*
 *
 *   static void efsu (int fd, char const * symbol, off_t offset, byte const * buffer, signed length);
 *
 *   print fields in efsu format;
 *
 *--------------------------------------------------------------------*/

static void efsu (int fd, char const * symbol, off_t offset, byte const * buffer, signed length) 

{
	signed column = 0;
	printf ("# %s\n", symbol);
	putc ('\n', stdout);
	while (column < length) 
	{
		printf ("%02X", buffer [column++]);
		putc (column%16? ' ': '\n', stdout);
	}
	if (column%16) 
	{
		putc ('\n', stdout);
	}
	putc ('\n', stdout);
	return;
}


/*====================================================================*
 *   
 *   void function (int fd, char const * filename, void output (int, off_t, char const *, byte const *, signed));
 *
 *   read offset description file and output binary fields in dump or
 *   efsu format;
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static size_t function (int fd, char const * filename, void output (int, char const *, off_t, byte const *, signed)) 

{
	size_t offset = 0;
	signed length = 0;
	signed lineno = 0;
	char symbol [_NAMESIZE];
	char * sp;
	signed c;
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
				*sp++ = (char)(c);
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
			*sp++ = (char)(c);
			c = getc (stdin);
			while (isblank (c)) 
			{
				c = getc (stdin);
			}
			while (isdigit (c)) 
			{
				*sp++ = (char)(c);
				c = getc (stdin);
			}
			while (isblank (c)) 
			{
				c = getc (stdin);
			}
			*sp = (char)(0);
			if (c != ']') 
			{
				error (1, EINVAL, "Have '%s' without ']' on line %d", symbol, lineno);
			}
			*sp++ = (char)(c);
			c = getc (stdin);
		}
		*sp = (char)(0);
		while (isblank (c)) 
		{
			c = getc (stdin);
		}
		while (nobreak (c)) 
		{
			c = getc (stdin);
		}
		if (length) 
		{
			byte buffer [length];
			if (read (fd, buffer, length) == length) 
			{
				output (fd, symbol, offset, buffer, length);
			}
		}
		offset += length;
		lineno++;
	}
	return (offset);
}


/*====================================================================*
 *
 *   void report (char const * filename, off_t offset);
 *
 *   compare file offset to file size and report any discrepency;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void report (char const * filename, off_t offset) 

{
	struct stat statinfo;
	stat (filename, &statinfo);
	if (offset != statinfo.st_size) 
	{
		error (0, 0, "file %s has " OFF_T_SPEC " bytes, not " OFF_T_SPEC " bytes.", filename, statinfo.st_size, offset);
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
		"def:qv",
		"file [file] [...]",
		"object driven dump",
		"d\toutput in dump format",
		"e\toutput in efsu format",
		"f f\tobject definition file",
		"q\tquiet mode",
		"v\tverbose mode",
		(char const *)(0)
	};
	void (* output) (int, char const *, off_t, byte const *, signed) = dump;
	flag_t flags = (flag_t)(0);
	signed fd = -1;
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'd':
			output = dump;
			break;
		case 'e':
			output = efsu;
			break;
		case 'f':
			if (!freopen (optarg, "rb", stdin)) 
			{
				error (1, errno, "%s", optarg);
			}
			break;
		case 'q':
			_setbits (flags, ODD_SILENCE);
			break;
		case 'v':
			_setbits (flags, ODD_VERBOSE);
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (argc > 1) 
	{
		error (1, 0, ERROR_TOOMANY);
	}
	while ((argc) && (* argv)) 
	{
		off_t offset;
		if ((fd = open (* argv, O_BINARY|O_RDONLY)) == -1) 
		{
			error (1, errno, "%s", * argv);
		}
		offset = function (fd, * argv, output);
		if (_allclr (flags, ODD_SILENCE)) 
		{
			report (* argv, offset);
		}
		close (fd);
		argc--;
		argv++;
	}
	return (0);
}

