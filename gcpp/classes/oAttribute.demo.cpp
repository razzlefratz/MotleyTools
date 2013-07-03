/*====================================================================*
 *
 *   cf.c - simple sample c lang formatter demonstrating oscantext object;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <cstdio>
#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/ogetopt.hpp"
#include "../classes/oputopt.hpp"
#include "../classes/tools.h"
#include "../../gcc/tools/types.h"
#include "../classes/flags.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../classes/oAttribute.cpp"
#include "../classes/ogetopt.cpp"
#include "../classes/oputopt.cpp"

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * usage [] = 
	{
		"oAttribute.demo",
		"h",
		PUTOPT_S_FUNNEL,
		"oAttribute object class demonstration and test utility",
		"h\thelp summary ",
		NULL
	};
	ogetopt options (1);
	oAttribute attrib;
	flag_t flags = (flag_t) (0);
	signed c;
	while ((c = options.getopt (argc, argv, usage [PUTOPT_I_OPTIONS])) != -1) 
	{
		switch (c) 
		{
		case 'h':
			options.putopt (usage);
		default:
			break;
		}
	}

/*
 * attrib.nameString("id");
 */

/*
 * attrib.textString("hello world!");
 */

/*
 * printf("%s\n", attrib.string());
 */

/*
 * attrib.flush();
 */

	return (0);
}

