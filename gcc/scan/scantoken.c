/*====================================================================*
 *
 *   char scantoken (SCAN * content);
 *
 *   scan.h
 *
 *   append input buffer characters to the current token substring while
 *   they are members of like character class; stop on the first character
 *   that is unlike the others; if the next input buffer character is of a
 *   particular class then subsequent characters of the same class are
 *   appended; recognized classes are space, letter, number and other;
 *
 *   the space class consists of all characters in global character string
 *   gcsSpace; spaces include ascii blank, horizontal tab, carriage return
 *   line feed and form feed;
 *
 *   the letter class consists of all characters in global character string
 *   gcsAlpha; letters include upper and lower case letters from western
 *   european alphabets;
 *
 *   the number class consists of all characters in global character string
 *   gcsDigit; numbers include arabic numerals comprising the common decimal
 *   characters set;
 *
 *   other classes each consist of one character;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANTOKEN_SOURCE
#define SCANTOKEN_SOURCE

#include <ctype.h>

#include "../scan/scan.h"
#include "../tools/chars.h"

void scantoken (SCAN * content) 

{
	if (content->final >= content->limit) 
	{
		content->class = (char) (0);
		return;
	}
	if (isspace (*content->final)) 
	{
		content->class = TOKEN_SPACE;
		scanspace (content);
		return;
	}
	if (isalpha (*content->final)) 
	{
		content->class = TOKEN_ALPHA;
		scanalnum (content);
		while (havebreak (content, "-")) 
		{
			content->class = TOKEN_IDENT;
			scanalnum (content);
		}
		return;
	}
	if (isdigit (*content->final)) 
	{
		content->class = TOKEN_DIGIT;
		scandigit (content);
		return;
	}

#if TOKEN_QUOTE

	if (isquote (*content->final)) 
	{
		content->class = TOKEN_QUOTE;
		nextbreak (content);
		scanquotematch (content);
		nextbreak (content);
		return;
	}

#endif

	content->class = *content->final++;

#ifdef TOKEN_CNOTE

/*
 *	detect C language-style comments; this token type is used by
 *	C language parsing applications;
 */

	if (isclass (content, "/") && isbreak (content, "*")) 
	{
		content->class = TOKEN_CNOTE;
		scanblock (content, "/*");
		return;
	}

#endif
#ifdef TOKEN_BOUND

/*
 *	detect multipart boundary on multipart/form-data messages; this
 *	token type is used by CGI applications;
 */

	if (isclass (content, "-") && isbreak (content, "-")) 
	{
		content->class = TOKEN_BOUND;
		nextbreak (content);
		return;
	}

#endif

	return;
}


#endif

