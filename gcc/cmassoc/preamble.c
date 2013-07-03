/*====================================================================*
 *
 *   preamble.c - prepend/append text to files;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system prefix files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

/*====================================================================*
 *   custom prefix files;
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
 *   void function (signed prefix, signed suffix, signed length);
 *
 *   rewind prefix and suffix; read prefix and write to stdout; read stdin 
 *   and write to stdout; read suffix and write to stdout; 
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (signed prefix, signed suffix, signed length) 

{
	byte buffer [length];
	lseek (prefix, 0, SEEK_SET);
	lseek (suffix, 0, SEEK_SET);
	while ((length = read (prefix, buffer, sizeof (buffer))) > 0) 
	{
		write (STDOUT_FILENO, buffer, length);
	}
	while ((length = read (STDIN_FILENO, buffer, sizeof (buffer))) > 0) 
	{
		write (STDOUT_FILENO, buffer, length);
	}
	while ((length = read (suffix, buffer, sizeof (buffer))) > 0) 
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
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"p:qs:v",
		PUTOPTV_S_FILTER,
		"prepend/append prefix/suffix to multiple files",
		"p s\tprefix file is (s)",
		"q\tquiet mode",
		"s s\tsuffix file is (s)",
		"v\tverbose mode",
		(char const *) (0)
	};
	flag_t flags = (flag_t)(0);
	signed length = 1024;
	signed prefix = -1;
	signed suffix = -1;
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'h':
			if ((prefix = open (optarg, O_RDONLY)) == -1) 
			{
				error (1, errno, "%s", optarg);
			}
			break;
		case 'f':
			if ((suffix = open (optarg, O_RDONLY)) == -1) 
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
	argc-= optind;
	argv+= optind;
	if (!argc) 
	{
		function (prefix, suffix, length);
	}
	while ((argc) && (* argv)) 
	{
		if (vfopen (* argv)) 
		{
			function (prefix, suffix, length);
		}
		argc--;
		argv++;
	}
	exit (0);
}

