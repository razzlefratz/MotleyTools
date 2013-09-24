/*====================================================================*
 *
 *   void chkoptv (char const * optv []);
 *
 *   putoptv.c
 *
 *   search a cmassoc option vector and report any mismatches;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CHKOPTV_SOURCE
#define CHKOPTV_SOURCE

#include <stdio.h>

#include "../tools/putoptv.h"

void chkoptv(char const * optv[])

{
	extern char const * program_name;
	char const * option;
	signed index;
	for (option = * optv; * option; option++)
	{
		if (* option == ':')
		{
			continue;
		}
		for (index = PUTOPTV_I_DETAILS; optv[index]; index++)
		{
			if (* option == * optv[index])
			{
				break;
			}
		}
		if (optv[index])
		{
			continue;
		}
		fprintf (stderr, "%s: option '%c' is no string.\n", program_name, * option);
	}
	for (index = PUTOPTV_I_DETAILS; optv[index]; index++)
	{
		for (option = optv[PUTOPTV_I_OPTIONS]; * option; option++)
		{
			if (* option == ':')
			{
				continue;
			}
			if (* option == * optv[index])
			{
				break;
			}
		}
		if (* option)
		{
			continue;
		}
		fprintf (stderr, "%s: string \"%s\" has no option.\n", program_name, optv[index]);
	}
	return;
}

#endif



