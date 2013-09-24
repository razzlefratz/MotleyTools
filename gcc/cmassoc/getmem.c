/*====================================================================*
 *
 *   getmem.c - memory data extractor
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

#include <unistd.h>
#include <stdlib.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/getoptv.h"
#include "../tools/memory.h"
#include "../tools/number.h"
#include "../tools/endian.h"
#include "../tools/error.h"
#include "../tools/types.h"
#include "../tools/flags.h"
#include "../files/files.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/uintspec.c"
#include "../tools/basespec.c"
#include "../tools/memdecode.c"
#include "../tools/todigit.c"
#include "../tools/hexout.c"
#include "../tools/error.c"
#endif

/*====================================================================*
 *   constants;
 *--------------------------------------------------------------------*/

#define GETMEM_VERBOSE (1 << 0)
#define GETMEM_SILENCE (1 << 1)
#define GETMEM_NEWLINE (1 << 2)

/*====================================================================*
 *
 *   void function (int argc, const char * argv [], size_t decode (void const *, size_t, char const *, char const *), flag_t flags);
 *
 *
 *--------------------------------------------------------------------*/

static void function (int argc, const char * argv [], size_t decode (void const *, size_t, char const *, char const *), flag_t flags)

{
	file file;
	unsigned offset = 0;
	unsigned extent = 0;
	unsigned length = 0;
	byte * memory;
	byte * origin;
	file.name = * argv;
	if ((file.file = open (file.name, O_BINARY | O_RDONLY)) == - 1)
	{
		error (1, errno, "Can't open %s", file.name);
	}
	if ((extent = lseek (file.file, 0, SEEK_END)) == - 1)
	{
		error (1, errno, "Can't size %s", file.name);
	}
	if (! (memory = malloc (extent)))
	{
		error (1, errno, "Can't span %s", file.name);
	}
	if (lseek (file.file, 0, SEEK_SET))
	{
		error (1, errno, "Can't seek %s", file.name);
	}
	if (read (file.file, memory, extent) != extent)
	{
		error (1, errno, "Can't load %s", file.name);
	}
	close (file.file);
	argc--;
	argv++;
	if (! argc)
	{
		error (1, ECANCELED, "Need an offset");
	}
	offset = (uint32_t)(basespec (* argv, 16, sizeof (uint32_t)));
	if (offset > extent)
	{
		error (1, ECANCELED, "PIB offset %X exceeds PIB extent %d", offset, extent);
	}
	argc--;
	argv++;
	if (! argc)
	{
		_setbits (flags, GETMEM_VERBOSE);
	}
	origin = memory;
	memory += offset;
	extent -= offset;
	while (argc && * argv)
	{
		offset = decode (memory, extent, * (argv), * (argv +  1));
		putc (' ', stdout);
		memory += offset;
		extent -= offset;
		argv++;
		argc--;
	}
	if (_anyset (flags, GETMEM_NEWLINE))
	{
		putc ('\n', stdout);
	}
	free (origin);
}

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
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
		"qvn",
		"file offset type [size]\n\n" \
		"\t  standard-length types are 'byte'|'word'|'long'|'hfid'|'mac'|'key'\n" \
		"\t  variable-length types are 'data'|'text'",
		"PIB Data Extractor",
		"n\tappend newline",
		"q\tquiet mode",
		"v\tverbose mode",
		(char const *) (0)
	};
	size_t (* decode)(void const *, size_t, char const *, char const *) = memdecode;
	flag_t flags = (flag_t)(0);
	signed c;
	opterr = 1;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'n':
			_setbits (flags, GETMEM_NEWLINE);
			break;
		case 'q':
			_setbits (flags, GETMEM_SILENCE);
			break;
		case 'v':
			_setbits (flags, GETMEM_VERBOSE);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if ((argc) && (* argv))
	{
		function (argc, argv, decode, flags);
	}
	return (0);
}

