/*====================================================================*
 *
 *   char *getIPv4 (char buffer[], size_t length, FILE *fp);
 *
 *   IPAddr.h
 *
 *   read stdin and write stdout; print an ordered slist of dotted   
 *   decimal IPv4 addresses with optional counts;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *%  Packaged as cmassoc-tools-1.4.2 by cmaier@cmassoc.net;
 *
 *--------------------------------------------------------------------*/

#ifndef GETIPV4_SOURCE
#define GETIPV4_SOURCE

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "../ether/IPAddr.h"

char * getIPv4 (char buffer [], size_t length, FILE * fp) 

{
	signed c;
	while ((c = getc (fp)) != EOF) 
	{
		if (isdigit (c)) 
		{
			char *sp = buffer;
			while (isdigit (c) || ((char)(c) == IP_ADDR_EXTENDER)) 
			{
				if ((size_t)(sp - buffer) < length) 
				{
					*sp++ = (char) (c);
				}
				c = getc (fp);
			}
			*sp = (char) (0);
			ungetc (c, fp);
			if (isIPv4 (buffer)) 
			{
				return (buffer);
			}
		}
	}
	return ((char *)(0));
}


#endif

