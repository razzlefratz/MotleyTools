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

void chkoptv (char const ** optv)

{
	extern char const * program_name;
	char const ** action;
	char const * option;
	signed index;
	optv++;
	optv++;
	for (option = * optv++; * option; option++)
	{
		if (* option == ':')
		{
			continue;
		}
		for (action = optv; * action; action++)
		{
			if (* option == ** action)
			{
				break;
			}
		}
		if (* action)
		{
			continue;
		}
		fprintf (stderr, "%s: option '%c' is no action text.\n", program_name, * option);
	}
	for (action = optv--; * action; action++)
	{
		for (option = * optv; * option; option++)
		{
			if (* option == ':')
			{
				continue;
			}
			if (* option == ** action)
			{
				break;
			}
		}
		if (* option)
		{
			continue;
		}
		fprintf (stderr, "%s: action text \"%s\" has no option.\n", program_name, * action);
	}
	return;
}

#endif



