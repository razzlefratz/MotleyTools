/*====================================================================*
 *
 *   getst.c - 
 *
 *   unget.h
 *
 *   this implementation is similar to the getch(), ungetch(), getst() and
 *   ungetst() functions seen in c language literature;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef GETST_SOURCE
#define GETST_SOURCE

#include <stdio.h>

#include "../tools/unget.h"

/*====================================================================*
 *
 *   char *getst (char *string, size_t length, FILE *ifp);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char *getst (char *string, size_t length, FILE * ifp) 

{
	char *sp = string;
	signed c;
	if (string != (char *)(0)) 
	{
		if (length-- > 0) 
		{
			while ((length-- > 0) && ((c = getch (ifp)) != EOF) && (c != '\n')) 
			{
				*sp++ = c;
			}
			*sp = (char)(0);
		}
	}
	return (string);
}


/*====================================================================*
 *
 *   signed ungetst (char *string, FILE *ifp);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ungetst (char *string, FILE * ifp) 

{
	char *sp = string;
	signed c;
	if (string != (char *)(0)) 
	{
		while (*sp != (char)(0)) 
		{
			sp++;
		}
		while ((--sp != (char)(0)) && ((c = ungetch (*sp, ifp)) != EOF));
		return (c);
	}
	else 
	{
		return (EOF);
	}
}


#endif

