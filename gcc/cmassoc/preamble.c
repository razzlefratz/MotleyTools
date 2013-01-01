/*====================================================================*
 *
 *   preamble.c - prepend/append text to files;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../clang/clang.h"
#include "../linux/linux.h"
#include "../files/files.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/mergepath.c"
#include "../files/splitpath.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define PREAMBLE_VERBOSE (1 << 0)
#define PREAMBLE_SILENCE (1 << 1)

/*====================================================================*
 *
 *   void function (signed fd1, signed fd2, signed length);
 *
 *   rewind fd1 and fd2; read fd1 and write to stdout; read stdin 
 *   and write to stdout; read fd2 and write to stdout; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static void function (signed fd1, signed fd2, signed length) 

{
	byte buffer [length];
	lseek (fd1, 0, SEEK_SET);
	lseek (fd2, 0, SEEK_SET);
	while ((length = read (fd1, buffer, sizeof (buffer))) > 0) 
	{
		write (STDOUT_FILENO, buffer, length);
	}
	while ((length = read (STDIN_FILENO, buffer, sizeof (buffer))) > 0) 
	{
		write (STDOUT_FILENO, buffer, length);
	}
	while ((length = read (fd2, buffer, sizeof (buffer))) > 0) 
	{
		write (STDOUT_FILENO, buffer, length);
	}
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
		"p:qs:v",
		PUTOPTV_S_FILTER,
		"prepend/append text to files",
		"p s\tprefix file is (s)",
		"q\tquiet mode",
		"s s\tsuffix file is (s)",
		"v\tverbose mode",
		(char const *) (0)
	};
	signed fd1 = -1;
	signed fd2 = -1;
	flag_t flags = (flag_t)(0);
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'p':
			if ((fd1 = open (optarg, O_RDONLY)) == -1) 
			{
				error (1, errno, "%s", optarg);
			}
			break;
		case 's':
			if ((fd2 = open (optarg, O_RDONLY)) == -1) 
			{
				error (1, errno, "%s", optarg);
			}
			break;
		case 'q':
			_setbits (flags, PREAMBLE_SILENCE);
			break;
		case 'v':
			_setbits (flags, PREAMBLE_VERBOSE);
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (!argc) 
	{
		function (fd1, fd2, BUFFERSIZE);
	}
	while ((argc) && (* argv)) 
	{
		if (vfopen (* argv)) 
		{
			function (fd1, fd2, BUFFERSIZE);
		}
		argc--;
		argv++;
	}
	exit (0);
}

