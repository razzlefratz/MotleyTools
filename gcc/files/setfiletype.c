/*====================================================================*
 *
 *   char *setfiletype (char *filename, char const *filetype);
 *
 *   replace the file extension with another, if present, or append
 *   the new extension, if not present; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SETFILETYPE_SOURCE
#define SETFILETYPE_SOURCE

#include "../files/files.h"

char *setfiletype (char *filename, char const *extender) 

{
	char *sp;
	char *cp;
	if (filename != (char *) (0)) 
	{
		for (sp = cp = filename; *cp != (char) (0); cp++) 
		{
			if ((*cp == PATH_C_EXTENDER) || (*cp == FILE_C_EXTENDER)) 
			{
				sp = cp;
			}
		}
		if (*sp != FILE_C_EXTENDER) 
		{
			sp = cp;
		}
		if (extender != (char *) (0)) 
		{
			while (*extender != (char) (0)) 
			{
				*sp++ = *extender++;
			}
		}
		*sp = (char) (0);
	}
	return (filename);
}


#endif

