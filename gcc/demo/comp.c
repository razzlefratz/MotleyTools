/*====================================================================*
 *
 *   _main.c - template program;
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>

#include "../strlib/strlib.h"
#include "../strlib/strmcmp.c"

int main (int argc, char const * argv []) 

{
	char const * string1;
	char const * string2;
	signed order;
	if (--argc) 
	{
		string1 = *++argv;
	}
	if (--argc) 
	{
		string2 = *++argv;
	}
	order = strmcmp (string1, string2, toupper);
	printf ("(%d)[%s][%s]\n", order, string1, string2);
	return (0);
}

