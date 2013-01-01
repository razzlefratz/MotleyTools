/*====================================================================*
 *
 *   getmem.c - memory data extractor
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
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

#define SETPIB_VERBOSE (1 << 0)
#define SETPIB_SILENCE (1 << 1)
#define SETPIB_NEWLINE (1 << 2)

/*====================================================================*
 *
 *   void function (int argc, const char * argv [], flag_t flags);
 *
 *
 *--------------------------------------------------------------------*/

static void function (int argc, const char * argv [], flag_t flags) 

{
	file file;
	size_t offset = 0;
	size_t extent = 0;
	size_t length = 0;
	byte * memory;
	byte * origin;
	file.name = * argv;
	if ((file.file = open (file.name, O_BINARY|O_RDONLY)) == -1) 
	{
		error (1, errno, "Can't open %s", file.name);
	}
	if ((extent = lseek (file.file, 0, SEEK_END)) == -1) 
	{
		error (1, errno, "Can't size %s", file.name);
	}
	if (!(memory = malloc (extent))) 
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
	if (!argc) 
	{
		error (1, ECANCELED, "Need an offset");
	}
	offset = (uint32_t)(basespec (* argv, 16, sizeof (uint32_t)));
	if (offset > extent) 
	{
		error (1, ECANCELED, "PIB offset %zX exceeds PIB extent %zX", offset, extent);
	}
	argc--;
	argv++;
	if (!argc) 
	{
		_setbits (flags, SETPIB_VERBOSE);
	}
	origin = memory;
	memory += offset;
	extent -= offset;
	while (argc && * argv) 
	{
		offset = memdecode (memory, extent, *(argv), *(argv + 1));
		putc (' ', stdout);
		memory += offset;
		extent -= offset;
		argv++;
		argc--;
	}
	if (_anyset (flags, SETPIB_NEWLINE)) 
	{
		putc ('\n', stdout);
	}
	free (origin);
}


/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
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
		"qvn",
		"file offset type [size]\n\n\t  standard-length types are 'byte'|'word'|'long'|'hfid'|'mac'|'key'\n\t  variable-length types are 'data'|'text'",
		"PIB Data Extractor",
		"n\tappend newline",
		"q\tquiet mode",
		"v\tverbose mode",
		(char const *) (0)
	};
	flag_t flags = (flag_t)(0);
	signed c;
	opterr = 1;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'n':
			_setbits (flags, SETPIB_NEWLINE);
			break;
		case 'q':
			_setbits (flags, SETPIB_SILENCE);
			break;
		case 'v':
			_setbits (flags, SETPIB_VERBOSE);
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if ((argc) && (* argv)) 
	{
		function (argc, argv, flags);
	}
	return (0);
}

