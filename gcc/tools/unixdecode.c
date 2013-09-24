/*====================================================================*
 *
 *   unixdecode(char const *string);
 *
 *   tools.h
 *
 *   encode spaces, control characters and non-ascii characters; return the encoded
 *   buffer address; encoded characters appear as octal ascii trigraphs, as in nnn.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef UNIXDECODE_SOURCE
#define UNIXDECODE_SOURCE

#include "../tools/tools.h"
#include "../tools/number.h"
#include "../chrlib/chrlib.h"

char * unixdecode(char * string)

{
	char * buffer = string;
	if (string)
	{
		while ((* buffer = * string))
		{
			if (* string == '\\')
			{
				unsigned m;
				unsigned n;
				unsigned o;
				if ((m = chrindex(DIGITS_OCT, string[1])) > 0x0003)
				{
					continue;
				}
				if ((n = chrindex(DIGITS_OCT, string[2])) > 0x0007)
				{
					continue;
				}
				if ((o = chrindex(DIGITS_OCT, string[3])) > 0x0007)
				{
					continue;
				}
				* buffer = (char)((m << 6) + (n << 3) +  o);
				string += 3;
			}
			buffer++;
			string++;
		}
	}
	return (buffer);
}

#endif



