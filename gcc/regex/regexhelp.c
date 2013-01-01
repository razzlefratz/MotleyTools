/*====================================================================*
 *
 *   void regexhelp(void);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef REGEXHELP_SOURCE
#define REGEXHELP_SOURCE

#include <stdio.h>

#include "../regex/regex.h"

void regexhelp (void) 

{
	printf ("\n");
	printf (" character sequences:\n");
	printf (" '%c' means any character;\n", REGEX_C_ANY);
	printf (" '%c' means zero or more of prior character;\n", REGEX_C_KLEENE_STAR);
	printf (" '%c' means zero or one of prior character;\n", REGEX_C_KLEENE_ONCE);
	printf (" '%c' means one or more of prior character;\n", REGEX_C_KLEENE_PLUS);
	printf (" '%c' means next character is literal;\n", REGEX_C_ESC);
	printf ("\n");
	printf (" character sets:\n");
	printf (" '%c' and '%c' bound the character set;\n", REGEX_C_SRT, REGEX_C_END);
	printf (" '%c' means exclude characters in set;\n", REGEX_C_NOT);
	printf (" '%c' means range of characters;\n", REGEX_C_RNG);
	printf ("\n");
	return;
}


#endif

