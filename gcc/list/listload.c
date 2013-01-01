/*====================================================================*
 *
 *    void listload (LIST * list, char const *file, char buffer[], size_t length)
 * 
 *   read the project file containing a list of C Language filenames  
 *   and append them to list;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef LISTLOAD_SOURCE
#define LISTLOAD_SOURCE

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "../list/list.h"
#include "../tools/tools.h"
#include "../tools/chars.h"
#include "../files/files.h"

void listload (LIST * list, char const *file, char buffer [], size_t length) 

{
	FILE *fp;
	char *sp;
	if ((fp = efopen (file, "r")) != (FILE *) (0)) 
	{
		while (fgetline (buffer, length, fp) != -1) 
		{
			for (sp = buffer; isblank (*sp); ++sp);
			if (strchr ("#;\n", *sp) == (char *) (0)) 
			{
				listinsert (list, sp);
			}
		}
		fclose (fp);
	}
	return;
}


#endif

