/*====================================================================*
 *
 *   void codesave (struct _code_ list [], size_t size, char const * name);
 *
 *   save struct _code_ list[] as C Preprocessor define statements 
 *   plus a table declaration;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CODESAVE_SOURCE
#define CODESAVE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/tools.h"
#include "../tools/error.h"

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

void codesave (struct _code_ list [], size_t size, char const * name, flag_t flags) 

{
	size_t item;
	for (item = 1; item < size; item++) 
	{
		if (list [item].code == list [item-1].code) 
		{
			error (1, EINVAL, "item %zd is a duplicate", item);
		}
		if (list [item].code < list [item-1].code) 
		{
			error (1, EINVAL, "item %zd is out of order", item);
		}
	}
	if (flags & TOOLS_B_DEFINE) 
	{
		printf ("/*=*\n *   constants;\n *-*/\n\n");
		for (item = 0; item < size; item++) 
		{
			printf ("#define %s 0x%04X\n", list [item].name, list [item].code);
		}
		printf ("\n\n");
	}
	if (flags & TOOLS_B_DECLARE) 
	{
		printf ("/*=*\n *   constants;\n *-*/\n\n");
		printf ("#define %sSIZE %zd\n", name, size);
		printf ("\n/*=*\n *   variables;\n *-*/\n\n");
		printf ("static struct _code_ %s [%sSIZE] = \n\n{\n", name, name);
		for (item = 0; item < size; item++) 
		{
			if (flags & TOOLS_B_NUMBER) 
			{
				printf ("\t{\n\t\t0x%04X,\n\t\t\"%s\"\n\t},\n", list [item].code, list [item].name);
			}
			else 
			{
				printf ("\t{\n\t\t%s,\n\t\t\"%s\"\n\t},\n", list [item].name, list [item].name);
			}
		}
		printf ("};\n\n");
	}
	if (flags & TOOLS_B_SWITCH) 
	{
		printf ("/*=*\n *   variables;\n *-*/\n\n");
		printf ("\tswitch(code)\n\t{\n");
		for (item = 0; item < size; item++) 
		{
			if (flags & TOOLS_B_NUMBER) 
			{
				printf ("\tcase 0x%04X:\n\t\tbreak;\n", list [item].code);
			}
			else 
			{
				printf ("\tcase %s:\n\t\tbreak;\n", list [item].name);
			}
		}
		printf ("\tdefault:\n\t\tbreak;\n");
		printf ("};\n\n");
	}
	return;
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

