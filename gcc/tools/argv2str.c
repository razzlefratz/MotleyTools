/*====================================================================*
 *
 *   char * argv2str (char * argv []);
 *
 *   convert argument vector to a command line on linux systems only;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ARGV2STR_SOURCE
#define ARGV2STR_SOURCE

#include <ctype.h>

char * argv2str(char * argv[])

{
	char * sp = * argv;
	char * cp = * argv;
	if (* argv) while(* ++ argv)
	{
		while (cp < * argv)
		{
			if (iscntrl(* cp))
			{
				* cp = ' ';
			}
			cp++;
		}
	}
	return (sp);
}

#endif



