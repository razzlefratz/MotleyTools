/*====================================================================*
 *
 *   int cinclude (LIST * files, char const * paths []);
 *
 *   clang.h
 *
 *   fill list with targets for files included by those already in
 *   list; normally, list contains one file on entry but can contain
 *   several;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CINCLUDE_SOURCE
#define CINCLUDE_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../tools/sizes.h"
#include "../tools/error.h"
#include "../files/files.h"
#include "../clang/clang.h"
#include "../list/list.h"
#include "../scan/scan.h"

int cinclude (LIST * files, char const * paths []) 

{
	FILE *fp;
	char target [FILENAME_MAX];
	char source [FILENAME_MAX];
	char buffer [TEXTLINE_MAX];
	char const ** path = paths;
	makepath (target, * path, files->table [files->lower]);
	if ((fp = fopen (target, "r"))) 
	{
		struct _scan_ scan;
		size_t line;
		scaninput (&scan, buffer, sizeof (buffer));
		for (line = 1; fgets (buffer, sizeof (buffer), fp); line++) 
		{
			scanstart (&scan);
			nexttoken (&scan);
			if (!havetoken (&scan, "#")) 
			{
				continue;
			}
			if (!havetoken (&scan, "include")) 
			{
				continue;
			}
			if (!havetoken (&scan, "\"")) 
			{
				continue;
			}
			scanuntil (&scan, "\"");
			for (path = paths; * path; path++) 
			{
				struct stat statinfo;
				makepath (source, * path, tokentext (&scan));
				if (!lstat (source, &statinfo)) 
				{
					listappend (files, source);
					break;
				}
			}
			if (!*path) 
			{
				error_on_line (0, errno, target, line, "can't find %s", tokentext (&scan));
				files->error++;
			}
			scanbreak (&scan, "\"");
		}
		fclose (fp);
	}
	return (files->error);
}


#endif

