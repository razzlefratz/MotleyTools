/*====================================================================*
 *
 *   signed token (char buffer[], size_t length, unsigned * lineno, void * bp, int get(void * bp), int unget(int c, void * bp));
 * 
 *   symbol.h
 *
 *   fetch next token from stdin and return the token class;
 *
 *   earlier version of this function used do {...} while instead of
 *   while {...} to avoid an unecessary loop exit test; this test is
 *   now tolerated because we check for buffer overrun for each damn 
 *   character; 
 *
 *   this version includes optional code that treats literal strings
 *   and c language comments as distinct tokens; the extra character
 *   variable is used to read ahead, allowing c to store the initial
 *   character value; this decision keeps the logic very general; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef GETCLASS_SOURCE
#define GETCLASS_SOURCE

#include <stdio.h>
#include <ctype.h>

#include "../tools/symbol.h"
#include "../tools/chars.h"

signed token(char buffer[], size_t length, unsigned * lineno, void * bp, int get(void * bp), int unget(int c, void * bp))

{
	unsigned column = 0;
	signed c = EOF;

#ifdef CMASSOC_SAFEMODE

	if (! buffer)
	{
		return (EOF);
	}
	if (! length)
	{
		return (EOF);
	}
	if (! bp)
	{
		return (EOF);
	}
	if (! get)
	{
		return (EOF);
	}
	if (! unget)
	{
		return (EOF);
	}

#endif

	c = get(bp);
	if (isspace(c))
	{
		do 
		{
			if (length)
			{
				* buffer = c;
				buffer++;
				length--;
			}
			if (lineno)
			{
				if (c == '\n')
				{
					++ * lineno;
				}
			}
			c = get(bp);
		}
		while (isspace(c));
		unget (c, bp);
		c = TOKEN_SPACE;
	}
	else if(isalpha(c))
	{
		do 
		{
			if (length)
			{
				* buffer = c;
				buffer++;
				length--;
			}
			c = get(bp);
		}
		while (isalpha(c));
		unget (c, bp);
		c = TOKEN_ALPHA;
	}
	else if(isdigit(c))
	{
		do 
		{
			if (length)
			{
				* buffer = c;
				buffer++;
				length--;
			}
			c = get(bp);
		}
		while (isdigit(c));
		unget (c, bp);
		c = TOKEN_DIGIT;
	}

#if 1

/*
 * treat literal strings as distinct tokens; literal strings start 
 * and end with the same character; the character is usually a quote 
 * mark but could be any character; internal characters may be 
 * escaped to permit embedded delimiters; append terminator if 
 * missing; 
 */

	else if(isquote(c))
	{
		signed o = c;
		do 
		{
			if (length)
			{
				* buffer = o;
				buffer++;
				length--;
			}
			o = get(bp);
			if (o == '\\')
			{
				if (length)
				{
					* buffer = o;
					buffer++;
					length--;
				}
				o = get(bp);
				if (o != EOF)
				{
					if (length)
					{
						* buffer = o;
						buffer++;
						length--;
					}
					o = get(bp);
				}
			}
		}
		while ((o != c) && (o != EOF));
		if (length)
		{
			* buffer = c;
			buffer++;
			length--;
		}
	}

#endif

#if 1

/*
 * treat c language comments as distinct tokens
 */

	else if(c == '/')
	{
		if (length)
		{
			* buffer = c;
			buffer++;
			length--;
		}
		c = get(bp);
		if (c == '*')
		{
			while ((c != '/') && (c != EOF))
			{
				while ((c != '*') && (c != EOF))
				{
					if (length)
					{
						* buffer = c;
						buffer++;
						length--;
					}
					c = get(bp);
				}
				if (length)
				{
					* buffer = c;
					buffer++;
					length--;
				}
				c = get(bp);
			}
			if (length)
			{
				* buffer = '/';
				buffer++;
				length--;
			}
			c = 'C';
		}
		else if(c == '/')
		{
			do 
			{
				if (length)
				{
					* buffer = c;
					buffer++;
					length--;
				}
				c = get(bp);
			}
			while ((c != '\n') && (c != EOF));
			unget (c, bp);
			c = 'C';
		}
		else 
		{
			unget (c, bp);
		}
	}

#endif

	else if(c != EOF)
	{
		if (length)
		{
			* buffer = c;
			buffer++;
			length--;
		}
	}
	if (column < length)
	{
		if (length)
		{
			* buffer = (char) (0);
			buffer++;
			length--;
		}
	}
	return (c);
}

/*====================================================================*
 *   demo/test program;
 *--------------------------------------------------------------------*/

#if 0
#include <stdio.h>

int main(int argc, char const * argv[])

{
	char buffer[4096];
	char c;
	while ((c = token(buffer, sizeof(buffer), stdin, getc, ungetc)) != EOF)
	{
		printf ("[%c]=[%s]\n", c, buffer);
	}
	return (0);
}

#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



