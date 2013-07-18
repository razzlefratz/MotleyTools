/*====================================================================*
 *
 *   chk-bld.c - 
 *
 *   search bash build script file for "pkg=" environment string
 *   definitions; search specfied folder for the file; this only
 *   applies to our own build scripts;
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
#include <sys/stat.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../files/files.h"
#include "../scan/scan.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/efreopen.c"
#include "../tools/emalloc.c"
#include "../tools/fgetline.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../scan/scaninput.c"
#include "../scan/scanreset.c"
#include "../scan/scantoken.c"
#include "../scan/scanuntil.c"
#include "../scan/scanspace.c"
#include "../scan/scanalnum.c"
#include "../scan/scandigit.c"
#include "../scan/scanflush.c"
#include "../scan/havetoken.c"
#include "../scan/havebreak.c"
#include "../scan/nexttoken.c"
#include "../scan/nextbreak.c"
#include "../scan/tokentext.c"
#include "../scan/isbreak.c"
#include "../scan/istoken.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define PKG_S_SOURCEDIR "./src"
#define PKG_B_PRESENT (1 << 0)
#define PKG_B_MISSING (2 << 1)

/*====================================================================*
 *
 *   static void func(char const *pathname, char const *filename, flag_t flags);
 *
 *   read a CMLinux package description file and string and write 
 *   dependencies to stdout;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void func (char const * filename, char * pathname, char * extender [], flag_t flags) 

{ 
	struct stat statinfo; 
	if (lstat (pathname, & statinfo)) 
	{ 
		error (0, errno, "can't stat %s.", pathname); 
	} 
	else if (!S_ISDIR (statinfo.st_mode)) 
	{ 
		error (0, errno, "ignoring %s", pathname); 
	} 
	else if (efreopen (filename, "rb", stdin)) 
	{ 
		SCAN scan; 
		char buffer [TEXTLINE_MAX]; 
		unsigned line; 
		char * filename; 
		for (filename = pathname; * filename != (char) (0); filename++); 
		* filename++ = PATH_C_EXTENDER; 
		scaninput (& scan, buffer, sizeof (buffer)); 
		for (line = 0; fgetline (buffer, sizeof (buffer), stdin) != - 1; line++) 
		{ 
			scantoken (& scan); 
			if (havetoken (& scan, "pkg")) 
			{ 
				if (havetoken (& scan, "=")) 
				{ 
					char ** item; 
					scanuntil (& scan, " \t\r\n"); 
					for (item = extender; * item != (char *) (0); item++) 
					{ 
						strcpy (filename, tokentext (& scan)); 
						strcat (filename, * item); 
						if (!lstat (pathname, & statinfo)) 
						{ 
							break; 
						} 
					} 
					if (* item != (char *) (0)) 
					{ 
						if (flags & PKG_B_PRESENT) 
						{ 
							printf ("+ %s\n", pathname); 
						} 
					} 
					else 
					{ 
						if (flags & PKG_B_MISSING) 
						{ 
							strcpy (filename, tokentext (& scan)); 
							printf ("- %s\n", pathname); 
						} 
					} 
				} 
			} 
			scanreset (& scan); 
		} 
	} 
	return; 
} 

/*====================================================================*
 *
 *   int main (int argc, char const * argv[])
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	static char const * optv [] = 
	{ 
		"d:mp", 
		PUTOPTV_S_FILTER, 
		"confirm existance of pkg= files", 
		"m\tlist files that are missing", 
		"p\tlist files that are present", 
		"d s\tsource folder is s [" PKG_S_SOURCEDIR "]", 
		(char const *)(0)
	}; 
	char pathname [FILENAME_MAX] = PKG_S_SOURCEDIR; 
	char * extender [100] = 
	{ 
		".tar.gz", 
		".tar.bz2", 
		(char *) (0)
	}; 
	flag_t flags = (flag_t) (0); 
	signed c; 
	while (~ (c = getoptv (argc, argv, optv))) 
	{ 
		switch (c) 
		{ 
		case 'p': 
			_setbits (flags, PKG_B_PRESENT); 
			break; 
		case 'm': 
			_setbits (flags, PKG_B_MISSING); 
			break; 
		case 'd': 
			strcpy (pathname, optarg); 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (_allclr (flags, (PKG_B_PRESENT | PKG_B_MISSING))) 
	{ 
		_setbits (flags, (PKG_B_PRESENT | PKG_B_MISSING)); 
	} 
	while ((argc) && (* argv)) 
	{ 
		func (* argv, pathname, extender, flags); 
		argc--; 
		argv++; 
	} 
	exit (0); 
} 

