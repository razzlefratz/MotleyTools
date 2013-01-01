/*====================================================================*
 *
 *   getch.c - 
 *
 *   unget.h
 *
 *   this implementation is similar to the getch(), ungetch() 
 *   and  ungetst() functions seen in c language literature;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>

#include "../tools/unget.h"
#include "../tools/sizes.h"
#include "../tools/symbol.h"

/*====================================================================*
 *   static variables;
 *--------------------------------------------------------------------*/

static char string [_MAXUNGET];
static char * sp = string;

/*====================================================================*
 *
 *   int getch (FILE *ifp);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int getch (FILE * ifp) 

{
	return ((sp > string)? *--sp: getc (ifp));
}


/*====================================================================*
 *
 *   int ungetch (int c, FILE *ifp);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int ungetch (int c, FILE * ifp) 

{
	if (sp < (string + sizeof (string))) 
	{
		*sp++ = c;
		return (c);
	}
	else 
	{
		return (EOF);
	}
}

