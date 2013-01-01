/*====================================================================*
 *
 *   odc.c - object driven compare;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
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
 *   void function (char const * filename [], flag_t flags);
 *   
 *   read definition file to determine the size of next object;
 *   read next object from each binary file and compare; report
 *   differences;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void function (char const * filename [], flag_t flags) 

{
	unsigned object = 0;
	unsigned lineno = 1;
	unsigned offset = 0;
	signed length = 0;
	file_t file [2];
	char memory [_ADDRSIZE+1];
	char symbol [_NAMESIZE];
	char string [_LINESIZE];
	char * sp;
	signed c;
	for (c = 0; c < 2; c++) 
	{
		if ((file [c] = open (filename [c], O_BINARY|O_RDONLY)) == -1) 
		{
			error (1, errno, "%s", filename [c]);
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
				error (1, EINVAL, "Have '%s' but need ']' on line %d", symbol, lineno);
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

#if defined (WIN32)

			char * buffer [2];
			buffer [0] = (char *)(emalloc (length));
			buffer [1] = (char *)(emalloc (length));

#else

			byte buffer [2][length];

#endif

			if ((read (file [0], buffer [0], length) == length) && (read (file [1], buffer [1], length) == length)) 
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
					printf ("%s %d %s\n", hexoffset (memory, sizeof (memory), offset), length, symbol);
					for (c = 0; c < _ADDRSIZE; c++) 
					{
						putc ('-', stdout);
					}
					printf (" %s\n", filename [0]);
					hexview (buffer [0], offset, length, stdout);
					for (c = 0; c < _ADDRSIZE; c++) 
					{
						putc ('-', stdout);
					}
					printf (" %s\n", filename [1]);
					hexview (buffer [1], offset, length, stdout);
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
		offset += length;
		lineno++;
	}
	if (_allclr (flags, ODC_SILENCE)) 
	{
		unsigned extent [2];
		for (c = 0; c < 2; c++) 
		{
			if ((signed)(extent [c] = lseek (file [c], 0, SEEK_END)) == -1) 
			{
				error (1, errno, FILE_CANTSIZE, filename [c]);
			}
			if (offset < extent [c]) 
			{
				error (0, 0, "%s exceeds definition by " SIZE_T_SPEC " bytes", filename [c], (size_t)(extent [c] - offset));
			}
			if (offset > extent [c]) 
			{
				error (0, 0, "definition exceeds %s by " SIZE_T_SPEC " bytes", filename [c], (size_t)(offset - extent [c]));
			}
		}
		if (extent [0] > extent [1]) 
		{
			error (0, 0, "%s exceeds %s by " SIZE_T_SPEC " bytes", filename [0], filename [1], (size_t)(extent [0] - extent [1]));
		}
		if (extent [1] > extent [0]) 
		{
			error (0, 0, "%s exceeds %s by " SIZE_T_SPEC " bytes", filename [1], filename [0], (size_t)(extent [1] - extent [0]));
		}
	}
	close (file [0]);
	close (file [1]);
	return;
}


/*====================================================================*
 *   
 *   int main (int argc, char const * argv []);
 *   
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
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
	while ((c = getoptv (argc, argv, optv)) != -1) 
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

