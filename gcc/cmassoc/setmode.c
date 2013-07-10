/*====================================================================*
 *
 *   cat.c - file concatenate program;
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
#include <errno.h>
#include <pwd.h>
#include <grp.h>

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
 *   program constants;
 *--------------------------------------------------------------------*/

#define FSTAT_FILENAME 0
#define FSTAT_CODE 1
#define FSTAT_TYPE 2
#define FSTAT_MODE 2
#define FSTAT_OWNER 3
#define FSTAT_GROUP 4
#define FSTAT_INSTR 5

/*====================================================================*
 *   
 *   static void checkmode (char *vector[]);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void checkmode (char * vector []) 

{ 
	struct stat stat; 
	struct passwd * passwd; 
	struct group * group; 
	mode_t filetype; 
	mode_t filemode; 
	if (lstat (vector [FSTAT_FILENAME], & stat)) 
	{ 
		error (0, errno, "%s is missing or misplaced or not accessible.", vector [FSTAT_FILENAME]); 
	} 
	filetype = (stat.st_mode >> FILE_MODE_BITS) & FILE_TYPE_MASK; 
	if (filetype != atoin (vector [FSTAT_TYPE], "01234567")) 
	{ 
		error (0, 0, "%s filetype has changed.", vector [FSTAT_FILENAME]); 
	} 
	filemode = (stat.st_mode >> 0) & FILE_MODE_MASK; 
	if (filemode != atoin (vector [FSTAT_MODE], "01234567")) 
	{ 
		error (0, 0, "%s filemode has changed.", vector [FSTAT_FILENAME]); 
	} 
	if ((passwd = getpwuid (stat.st_uid)) == (struct passwd * ) (0)) 
	{ 
		error (0, 0, "%s has illegal owner.", vector [FSTAT_FILENAME]); 
	} 
	else if (strcmp (passwd->pw_name, vector [FSTAT_OWNER])) 
	{ 
		error (0, 0, "%s owner has changed.", vector [FSTAT_FILENAME]); 
	} 
	if ((group = getgrgid (stat.st_gid)) == (struct group * ) (0)) 
	{ 
		error (0, 0, "%s has illegal group.", vector [FSTAT_FILENAME]); 
	} 
	else if (strcmp (group->gr_name, vector [FSTAT_GROUP])) 
	{ 
		error (0, 0, "%s group has changed.", vector [FSTAT_FILENAME]); 
	} 
	return; 
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
		"set file modes from snapshot file", 
		(char const * )(0)
	}; 
	FILE * fp; 
	char buffer [255]; 
	char * vector [16]; 
	char ** vp, 
	* sp; 
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
	while ((argc) && (* argv)) 
	{ 
		if ((fp = efopen (* argv, "rb"))) 
		{ 
			vp = vector; 
			* vp++ = sp = buffer; 
			while ((c = fgetc (fp)) != EOF) 
			{ 
				switch (c) 
				{ 
				case LIST_C_EXTENDER: 
					* vp = (char * ) (0); 
					* sp = (char) (0); 
					checkmode (vector); 
					vp = vector; 
					* vp++ = sp = buffer; 
					break; 
				case ITEM_C_EXTENDER: 
					* vp++ = sp + 1; 
					* sp++ = (char) (0); 
					break; 
				case ' ': 
				case '\t': 
				case '\n': 
					break; 
				default: 
					* sp++ = c; 
					break; 
				} 
			} 
			fclose (fp); 
		} 
		argc-- ; 
		argv++ ; 
	} 
	exit (0); 
} 

