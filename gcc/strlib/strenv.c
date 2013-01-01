/*====================================================================*
 *
 *   char const * strenv (char const * vector [], char const * string, signed c);
 *
 *   search a string vec
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRENV_SOURCE
#define STRENV_SOURCE

#include "../strlib/strlib.h"

char const * strenv (char const * vector [], char const * string, signed c) 

{
	char const * sp;
	char const * vp;
	while (*vector) 
	{
		sp = string;
		vp = * vector;
		while ((*sp) && (*sp == *vp)) 
		{
			sp++;
			vp++;
		}
		if ((!*sp) && (!*vp)) 
		{
			return (++vp);
		}
		vector++;
	}
	return ((char *)(0));
}


/*====================================================================*
 *   test/demo program;
 *--------------------------------------------------------------------*/

#if 0
#include <stdio.h>

int main (int argc, char const * argv [], char const * envp []) 

{
	while (*++argv) 
	{
		printf ("%s=[%s]\n", *argv, strenv (envp, *argv, '='));
	}
	return;
}


#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif

