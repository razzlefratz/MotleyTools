/*====================================================================*
 *
 *   argv.c - display argument vector;
 *
 *   this program tests function makepath(); argv[1] should contain a
 *   basename like ".", "..", "/" or "/abc/def"; remaining argv[] strings
 *   may contain either absolute or relative filename references; results
 *   are printed on stdout; each filename is merged with the basename and
 *   displayed; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>

#include "../files/files.h"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"

int main (int argc, char const *argv []) 

{
	int argn;
	char fullname [FILENAME_MAX];
	for (argn = 2; argn < argc; argn++) 
	{
		makepath (fullname, argv [1], argv [argn]);
		printf ("pathname=[%s] filename=[%s] fullname=[%s]\n", argv [1], argv [argn], fullname);
	}
	printf ("\n");
	return (0);
}

