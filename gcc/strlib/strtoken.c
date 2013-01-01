/*====================================================================*
 *
 *   signed strtoken (char buffer [], size_t length, char const ** string) 
 *   
 *   strlib.h
 *   
 *   scan string and collect the next token in symbol []; truncate 
 *   symbol on overrun but consume the entire token; return ' ' for
 *   space, 'A' for word or '0' for number; return character value
 *   for any other token.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRTOKEN_SOURCE
#define STRTOKEN_SOURCE

#include <stdio.h>
#include <ctype.h>
#include <memory.h>

#include "../strlib/strlib.h"

signed strtoken (char symbol [], size_t length, char const ** string) 

{
	signed token = 0;
	if ((symbol) && (length)) 
	{
		memset (symbol, 0, length--);
		if ((string) && (*string)) 
		{
			if (isspace (**string)) 
			{
				do 
				{
					if (length) 
					{
						*symbol++ = **string;
						length--;
					}
					(*string)++;
				}
				while (isspace (**string));
				token = ' ';
			}
			else if (isalpha (**string)) 
			{
				do 
				{
					if (length) 
					{
						*symbol++ = **string;
						length--;
					}
					(*string)++;
				}
				while (isalnum (**string));
				token = 'A';
			}
			else if (isdigit (**string)) 
			{
				do 
				{
					if (length) 
					{
						*symbol++ = **string;
						length--;
					}
					(*string)++;
				}
				while (isdigit (**string));
				token = '0';
			}
			else 
			{
				if (length) 
				{
					*symbol++ = **string;
					length--;
				}
				token = *(*string)++;
			}
		}
	}
	return (token);
}


/*====================================================================*
 *   demo/test program;
 *--------------------------------------------------------------------*/

#if 0

#include <unistd.h>

int main (int argc, const char * argv []) 

{
	char symbol [36];
	char string [1024];
	char const * sp = string;
	char token;
	memset (string, 0, sizeof (string));
	read (STDIN_FILENO, string, sizeof (string) - 1);
	while ((token = strtoken (symbol, sizeof (symbol), &sp))) 
	{
		printf ("(%c)[%s]\n", token, symbol);
	}
	return (0);
}


#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

