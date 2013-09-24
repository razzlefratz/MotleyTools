/*====================================================================*
 *
 *   signed fputline(char const buffer[], size_t length, FILE *fp);
 *
 *   tools.h  
 *
 *   output up to length characters from buffer to the stream associated
 *   with a file pointer; terminate output on the first NUL character in
 *   buffer; output a newline after the last character is output; return 
 *   length on success; return 0 or EOF on failure;
 *
 *   when length is the buffer length,and not the actual string length, 
 *   all lines are output; when length is the string length, successive 
 *   empty lines are not output; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FPUTLINE_SOURCE
#define FPUTLINE_SOURCE

#include <stdio.h>
#include "../tools/tools.h"

signed fputline(char const buffer[], size_t length, FILE * ofp)

{
	static size_t output = 0;

#ifdef CMASSOC_SAFEMODE

	if (! buffer)
	{
		return (0);
	}

#endif

	if ((output) || (length))
	{
		for (output = 0; (output < length) && (* buffer); output++)
		{
			if (fputc(* buffer++, ofp) == EOF)
			{
				return (- 1);
			}
		}
		fputc ('\n', ofp);
	}
	return (output);
}

#endif



