/*====================================================================*
 *
 *   ofilespec.demo.cpp
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/tools.h"
#include "../classes/oflags.h"

#include "../classes/ogetoptv.hpp"
#include "../classes/oputoptv.hpp"
#include "../classes/oversion.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../strlib/ocontext.cpp"
#include "../classes/ofilespec.cpp"
#endif

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [])

{
	static char const * optv [] =
	{
		"",
		"filespec [filespec] ...",
		"ofilespec object class demonstration and test utility",
		(char const *) (0)
	};
	ofilespec filespec;
	ogetoptv getopt (1);
	oputoptv putopt;
	signed c;
	while ((c = getopt.getoptv (argc, argv, optv)) != -1)
	{
		switch (c)
		{
		default: 
			break;
		}
	}
	while ((getopt.argc () > 0) && (* getopt.argv () != (char *) (0)))
	{
		filespec.filespec (* getopt.argv ()).peek ();
		getopt++;
	}
	return (0);
}

