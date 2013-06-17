/*====================================================================*
 *
 *   ofilespec.demo.cpp 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <cstdio>
#include <iostream>
#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/ogetopt.hpp"
#include "../classes/oputopt.hpp"
#include "../classes/oregex.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetopt.cpp"
#include "../classes/oputopt.cpp"
#include "../classes/oregex.cpp"
#include "../classes/oescape.cpp"
#include "../classes/oascii.cpp"

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * usage [] = 
	{
		"h",
		"expression [expression] ...",
		"demonstrate/test oregex opbject",
		"h\thelp summary ",
		NULL
	};
	ogetopt getopt (1);
	oputopt putopt;
	oregex * regex;
	signed c;
	while ((c = getopt.getopt (argc, argv, usage [PUTOPT_I_OPTIONS])) != -1) 
	{
		switch (c) 
		{
		case 'h':
			putopt.putopt (usage);
		default:
			break;
		}
	}
	while (getopt.optcnt ()) 
	{
		regex = new oregex (argv [getopt.optind ()]);
		regex->show ();
		getopt++;
	}
	return (0);
}


