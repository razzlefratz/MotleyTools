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
 *   program variables;
 *--------------------------------------------------------------------*/

static unsigned object = 0;
static unsigned lineno = 0;
static unsigned offset = 0;
static signed length = 0;
static signed column = 0;
static char memory [_ADDRSIZE + 1];
static char symbol [_NAMESIZE];
static char string [_LINESIZE];
static char * sp;
static signed c;

/*====================================================================*
 *
 *   static void dump (struct _file_ const * file, signed length);
 *
 *--------------------------------------------------------------------*/

static void dump (struct _file_ const * file, signed length) 

{
	byte buffer [length];
	if (read (file->file, buffer, length) == length) 
	{
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
	}
	return;
}


/*====================================================================*
 *
 *   static void efsu (struct _file_ const * file, signed length);
 *
 *   print fields in efsu format;
 *
 *--------------------------------------------------------------------*/

static void efsu (struct _file_ const * file, signed length) 

{
	byte buffer [length];
	if (read (file->file, buffer, length) == length) 
	{
		column = 0;
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
	}
	return;
}


/*====================================================================*
 *   
 *   void function (struct _file_ const * file, off_t extent, void output (struct _file_ const *, signed), flag_t flags);
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (struct _file_ const * file, off_t extent, void output (struct _file_ const *, signed), flag_t flags) 

{
	object = 0;
	lineno = 0;
	offset = 0;
	length = 0;
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
		sp = string;
		while (nobreak (c)) 
		{
			*sp++ = (char)(c);
			c = getc (stdin);
		}
		*sp = (char)(0);
		if (length) 
		{
			output (file, length);
		}
		offset += length;
		lineno++;
	}
	if (_allclr (flags, ODD_SILENCE)) 
	{
		if (offset != (unsigned)(extent)) 
		{
			error (0, 0, "%s has %u bytes, not " OFF_T_SPEC " bytes.", file->name, offset, extent);
		}
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
	file file = 
	{
		STDIN_FILENO,
		"stdin"
	};
	void (* output) (struct _file_ const *, signed) = dump;
	flag_t flags = (flag_t)(0);
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
		error (1, ENOTSUP, ERROR_TOOMANY);
	}
	if ((argc) && (* argv)) 
	{
		struct stat statinfo;
		stat (*argv, &statinfo);
		if ((file.file = open (file.name = *argv, O_BINARY|O_RDONLY)) == -1) 
		{
			error (0, errno, "%s", file.name);
		}
		else 
		{
			function (&file, statinfo.st_size, output, flags);
			close (file.file);
		}
		argc--;
		argv++;
	}
	return (0);
}

