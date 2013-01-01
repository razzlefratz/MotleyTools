/*====================================================================*
 *
 *   char * ietfdecode(char const *string, char *buffer, size_t length);
 *
 *   tools.h
 *
 *   replace hexidecimal octet representations with equivalent ascii
 *   character codes;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef IETFDECODE_SOURCE
#define IETFDECODE_SOURCE

#include "../tools/tools.h"
#include "../tools/number.h"

char * ietfdecode (char *string) 

{
	char * buffer = string;
	char * offset = string;
	while ((*offset = *string)) 
	{
		if (*string == '%') 
		{
			unsigned upper = todigit (string [1]);
			unsigned lower = todigit (string [2]);
			if ((upper < 16) && (lower < 16)) 
			{
				*offset = 0;
				*offset += upper << 4;
				*offset += lower << 0;
				string++;
				string++;
			}
		}
		offset++;
		string++;
	}
	return (buffer);
}


/*====================================================================*
 *   test program;
 *--------------------------------------------------------------------*/

#if 0
#include <stdio.h>

#include "../tools/todigit.c"

int main (int argc, char const * argv []) 

{
	char string [] = "%0909hel%9lo%0A%%%world";
	ietfdecode (string);
	printf ("string=[%s]\n", string);
	return;
}


#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

