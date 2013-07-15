/*====================================================================*
 *
 *   faudit.c - audit file states against snapshot file; 
 *
 *   copy one or more files to stdout; if no files are specified then copy
 *   stdin to stdout;
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
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../linux/linux.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/efopen.c"
#include "../tools/error.c"
#include "../tools/atoin.c"
#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#define CODE 0
#define TYPE 1
#define MODE 2
#define OWNER 3
#define GROUP 4
#define INSTR 5
#define NAME 6

/*====================================================================*
 *   
 *   static void faudit (char *vector[]);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

int faudit (char * filestate []) 

{ 
	struct stat statinfo; 
	struct passwd * passwd; 
	struct group * group; 
	mode_t type; 
	mode_t mode; 
	int errors = 0; 
	if (stat (filestate [NAME], & statinfo)) 
	{ 
		error (0, errno, "%s", filestate [NAME]); 
		return (1); 
	} 
	type = (statinfo.st_mode >> FILE_MODE_BITS) & FILE_TYPE_MASK; 
	if (type != atoin (filestate [TYPE], "01234567")) 
	{ 
		error (0, 0, "%s: type was %s now %04o", filestate [NAME], filestate [TYPE], type); 
		errors++; 
	} 
	mode = (statinfo.st_mode >> 0) & FILE_MODE_MASK; 
	if (mode != atoin (filestate [MODE], "01234567")) 
	{ 
		error (0, 0, "%s: mode was %s now %04o", filestate [NAME], filestate [MODE], mode); 
		errors++; 
	} 
	if ((passwd = getpwuid (statinfo.st_uid)) == (struct passwd *) (0)) 
	{ 
		error (0, errno, "%s: unknown owner", filestate [NAME]); 
		errors++; 
	} 
	else if (strcmp (passwd->pw_name, filestate [OWNER])) 
	{ 
		error (0, 0, "%s: owner was %s now %s", filestate [NAME], filestate [OWNER], passwd->pw_name); 
		errors++; 
	} 
	if ((group = getgrgid (statinfo.st_gid)) == (struct group *) (0)) 
	{ 
		error (0, errno, "%s: unknown group", filestate [NAME]); 
		errors++; 
	} 
	else if (strcmp (group->gr_name, filestate [GROUP])) 
	{ 
		error (0, 0, "%s: group was %s now %s", filestate [NAME], filestate [GROUP], group->gr_name); 
		errors++; 
	} 
	return (errors); 
} 

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	static char const * optv [] = 
	{ 
		"", 
		PUTOPTV_S_FUNNEL, 
		"audit file states against snapshot file;", 
		(char const *)(0)
	}; 
	FILE * fp; 
	char buffer [255]; 
	char * attributes [16]; 
	char ** attribute; 
	char * string; 
	signed errors = 0; 
	signed index = 0; 
	signed c; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (!argc) 
	{ 
	} 
	while ((argc) && (* argv)) 
	{ 
		if ((fp = efopen (* argv, "rb"))) 
		{ 
			* attribute++ = string = buffer; 
			while ((c = fgetc (fp)) != EOF) 
			{ 
				switch (c) 
				{ 
				case LIST_C_EXTENDER: 
					* attribute = (char *) (0); 
					* string = (char) (0); 
					errors += faudit (attributes); 
					index++; 
					attribute = attributes; 
					* attribute++ = string = buffer; 
					break; 
				case ITEM_C_EXTENDER: 
					* attribute++ = string + 1; 
					* string++ = (char) (0); 
					break; 
				case ' ': 
				case '\t': 
				case '\n': 
					break; 
				default: 
					* string++ = c; 
					break; 
				} 
			} 
			fclose (fp); 
		} 
		argc--; 
		argv++; 
	} 
	if (errors > 0) 
	{ 
		error (0, 0, "found %d changes to %d index", errors, index); 
	} 
	exit ((bool) (errors)); 
} 

