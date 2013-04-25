/*====================================================================*
 *
 *   odx.c - object driven XML dump;
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
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../tools/markup.h"
#include "../nodes/nodes.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/emalloc.c"
#include "../tools/indent.c"
#endif

#ifndef MAKEFILE
#include "../nodes/xmlschema.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define ODX_VERBOSE  (1 << 0)
#define ODX_SILENCE  (1 << 1)

/*====================================================================*
 *   
 *   void function (file const * file, char const * schema, off_t extent, flag_t flags);
 *   
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (file const * file, char const * schema, off_t extent, flag_t flags) 

{
	unsigned lineno = 1;
	unsigned margin = 0;
	unsigned offset = 0;
	unsigned length = 0;
	char symbol [_NAMESIZE];
	char string [_LINESIZE];
	char * sp;
	signed c;
	indent (margin++, "<%s xmlns:xsi='%s' xsi:noNamespaceSchemaLocation='%s'>", DATA_OBJECT, XML_NAMESPACE, schema);
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
		if (c == '+') { do { c = getc (stdin); } while (isblank (c)); }
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
		*sp = (char)(0);
		while (isblank (c)) 
		{
			c = getc (stdin);
		}
		if (c == '[') 
		{
			c = getc (stdin);
			while (isblank (c)) 
			{
				c = getc (stdin);
			}
			while (isdigit (c)) 
			{
				c = getc (stdin);
			}
			while (isblank (c)) 
			{
				c = getc (stdin);
			}
			if (c != ']') 
			{
				error (1, EINVAL, "Have '%s' but need ']' on line %d", symbol, lineno);
			}
			c = getc (stdin);
		}
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
			byte buffer [length];
			if (read (file->file, buffer, length) == (signed)(length)) 
			{
				indent (margin++, "<%s name='%s'>", DATA_MEMBER, symbol);
				if (*string) 
				{
					indent (margin++, "<text>");
					indent (margin, "%s", string);
					indent (margin--, "</text>");
				}
				indent (margin++, "<%s>", DATA_OFFSET);
				indent (margin, "%04X", offset);
				indent (margin--, "</%s>", DATA_OFFSET);
				indent (margin++, "<%s>", DATA_LENGTH);
				indent (margin, "%u", length);
				indent (margin--, "</%s>", DATA_LENGTH);
				indent (margin++, "<%s>", DATA_MEMORY);
				for (c = 0; c < (signed)(margin); c++) 
				{
					printf ("\t");
				}
				for (c = 0; c < (signed)(length); c++) 
				{
					printf ("%02X", buffer [c]);
				}
				printf ("\n");
				indent (margin--, "</%s>", DATA_MEMORY);
				indent (margin--, "</%s>", DATA_MEMBER);
			}
		}
		offset += length;
		lineno++;
	}
	indent (margin--, "</%s>", DATA_OBJECT);
	if (_allclr (flags, ODX_SILENCE)) 
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
		"f:s:x",
		"file [file] [...]",
		"object driven XML dump utility",
		"f f\tobject definition file",
		"x\tprint an XML schema on stdout",
		(char const *)(0)
	};
	char const * schema = DATA_SCHEMA;
	file file = 
	{
		STDIN_FILENO,
		"stdin"
	};
	flag_t flags = (flag_t)(0);
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'f':
			if (!freopen (optarg, "rb", stdin)) 
			{
				error (1, errno, FILE_CANTOPEN, optarg);
			}
			break;
		case 'q':
			_setbits (flags, ODX_SILENCE);
			break;
		case 's':
			schema = optarg;
			break;
		case 'v':
			_setbits (flags, ODX_VERBOSE);
			break;
		case 'x':
			xmlschema ();
			return (0);
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
			function (&file, schema, statinfo.st_size, flags);
			close (file.file);
		}
	}
	return (0);
}

