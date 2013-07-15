/*============================================================================== 
 *
 *   qc.c - c program quick check utility 
 *
 *   open c language source files and look for their include files;  
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
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../files/files.h"
#include "../list/list.h"
#include "../scan/scan.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/efopen.c"
#include "../tools/emalloc.c"
#include "../tools/error.c"
#include "../tools/erealloc.c"
#include "../tools/fgetline.c"
#endif

#ifndef MAKEFILE
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/fullpath.c"
#include "../files/partpath.c"
#include "../files/partfile.c"
#endif

#ifndef MAKEFILE
#include "../list/listcreate.c"
#include "../list/listdelete.c"
#include "../list/listappend.c"
#include "../list/listexpand.c"
#endif

#ifndef MAKEFILE
#include "../scan/scanalnum.c"
#include "../scan/scandigit.c"
#include "../scan/scaninput.c"
#include "../scan/scanreset.c"
#include "../scan/scanuntil.c"
#include "../scan/scanbreak.c"
#include "../scan/scantoken.c"
#include "../scan/scanspace.c"
#include "../scan/scanflush.c"
#include "../scan/havetoken.c"
#include "../scan/havebreak.c"
#include "../scan/nexttoken.c"
#include "../scan/nextbreak.c"
#include "../scan/tokentext.c"
#include "../scan/istoken.c"
#include "../scan/isbreak.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define QCFLAG_SYSTEM (1 << 0)
#define QCFLAG_CUSTOM (1 << 1)
#define QCFLAG_REPORT (1 << 2)
#define QCFLAG_EVENTS (1 << 3)

/*====================================================================*
 *
 *   void report (char const *filename, flag_t flags);
 *
 *   open the named source file and verify that 1) the file is not 
 *   empty and 2) all include files exist; 
 *
 *   filename contains the file specification; filename points to 
 *   the filename substring within that specification;
 *
 *   we scan one source line at a time with functions that read and 
 *   maintain a scanning structure defined in scan.h; 
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (char const * filename, char const * pathlist [], flag_t flags) 

{ 
	FILE * fp; 
	LIST list; 
	FIND open; 
	SCAN scan; 
	char buffer [TEXTLINE_MAX]; 
	long line; 
	struct stat stat; 
	listcreate (& list, _LISTSIZE); 
	listappend (& list, filename); 
	for (list.index = list.start; list.index < list.count; list.index++) 
	{ 
		if ((fp = efopen (list.table [list.index], "rb"))) 
		{ 
			if (_anyset (flags, QCFLAG_EVENTS)) 
			{ 
				error (0, 0, "checking %s", filename); 
			} 
			strcpy (open.fullname, list.table [list.index]); 
			partpath (open.fullname, open.pathname, open.basename); 
			partfile (open.basename, open.filename, open.extender); 
			scaninput (& scan, buffer, sizeof (buffer)); 
			for (line = 1; fgetline (buffer, TEXTLINE_MAX, fp) != - 1; line++) 
			{ 
				nexttoken (& scan); 
				if (havetoken (& scan, "#")) 
				{ 
					if (havetoken (& scan, "include")) 
					{ 
						if (havetoken (& scan, "<")) 
						{ 
							scanuntil (& scan, ">"); 
							if (_anyset (flags, QCFLAG_SYSTEM)) 
							{ 
								size_t index; 
								for (index = 0; pathlist [index] != (char const *) (0); index++) 
								{ 
									makepath (open.fullname, pathlist [index], tokentext (& scan)); 
									if (lstat (open.fullname, & stat) == 0) 
									{ 
										listappend (& list, open.fullname); 
										break; 
									} 
								} 
								if (pathlist [index] == (char const *) (0)) 
								{ 
									error (0, 0, "%s:%ld system file %s is missing.", open.basename, line, open.fullname); 
								} 
							} 
							scanbreak (& scan, ">"); 
						} 
						else if (havetoken (& scan, "\"")) 
						{ 
							scanuntil (& scan, "\""); 
							if (_anyset (flags, QCFLAG_CUSTOM)) 
							{ 
								makepath (open.fullname, open.pathname, tokentext (& scan)); 
								listappend (& list, open.fullname); 
								if (lstat (open.fullname, & stat) != 0) 
								{ 
									error (0, 0, "%s:%ld custom file %s is missing.", open.basename, line, tokentext (& scan)); 
								} 
							} 
							scanbreak (& scan, "\""); 
						} 
					} 
				} 
				scanreset (& scan); 
			} 
			fclose (fp); 
			if (line == 1) 
			{ 
				error (0, 0, "%s:%ld file is empty.", open.basename, line); 
			} 
		} 
	} 
	if (flags & (QCFLAG_REPORT)) 
	{ 
		for (list.index = list.start; list.index < list.count; list.index++) 
		{ 
			printf ("%s\n", list.table [list.index]); 
		} 
		printf ("\n"); 
	} 
	listdelete (& list); 
	return; 
} 

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	static char const * optv [] = 
	{ 
		"cisv", 
		PUTOPTV_S_FUNNEL, 
		"check c language source and header files for missing include files;", 
		"c\tcustom files ", 
		"i\toutput an inventory ", 
		"s\tsystem files ", 
		"v\tverbose messages", 
		(char const *) (0)
	}; 
	static char const * pathlist [] = 
	{ 
		"/usr/include", 
		"/usr/local/include", 
		"/usr/include/linux", 
		"/usr/include/g++-3", 
		"/usr/lib/i686-linux/2.95.4/include", 
		"/usr/lib/gcc-lib/i386-linux/2.95.4/include", 
		"/usr/lib/gcc-lib/i386-linux/3.0.4/include", 
		(char const *) (0)
	}; 
	flag_t flags = (flag_t)(0); 
	char filename [FILENAME_MAX + 1]; 
	signed c; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 's': 
			_setbits (flags, QCFLAG_SYSTEM); 
			break; 
		case 'c': 
			_setbits (flags, QCFLAG_CUSTOM); 
			break; 
		case 'i': 
			_setbits (flags, QCFLAG_REPORT); 
			break; 
		case 'v': 
			_setbits (flags, QCFLAG_EVENTS); 
			break; 
		default: 
			break; 
		} 
	} 
	if (_allclr (flags, (QCFLAG_CUSTOM | QCFLAG_SYSTEM))) 
	{ 
		_setbits (flags, (QCFLAG_CUSTOM | QCFLAG_SYSTEM)); 
	} 
	argc -= optind; 
	argv += optind; 
	while ((argc) && (* argv)) 
	{ 
		makepath (filename, getenv ("PWD"), * argv); 
		function (filename, pathlist, flags); 
		argc--; 
		argv++; 
	} 
	exit (0); 
} 

