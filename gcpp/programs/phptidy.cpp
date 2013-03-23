/*====================================================================*
 *
 *   phptidy.cpp - tidy PHP source files;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdlib>
#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/ocontext.hpp"
#include "../classes/owildcard.hpp"
#include "../classes/ofileopen.hpp"
#include "../classes/ofilespec.hpp"
#include "../classes/opathspec.hpp"
#include "../classes/ophptidy.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/oerror.cpp"
#include "../classes/ofileopen.cpp"
#include "../classes/ofilespec.cpp"
#include "../classes/opathspec.cpp"
#include "../classes/ocontext.cpp"
#include "../classes/owildcard.cpp"
#include "../classes/oescape.cpp"
#include "../classes/oindent.cpp"
#include "../classes/oascii.cpp"
#include "../classes/ocollect.cpp"
#include "../classes/ophptidy.cpp"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define MARGIN ""
#define OFFSET "\t"

/*====================================================================*
 *   
 *   int main (int argc, char const * argv []);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"",
		oPUTOPTV_S_FILTER,
		"format PHP source code",
		(char const *) (0)
	};
	ogetoptv getopt;
	opathspec pathspec;
	ofileopen fileopen;
	ophptidy tidy;
	int (ophptidy::*function) (signed) = &ophptidy::page;
	signed c;
	while ((c = getopt.getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		default:
			break;
		}
	}
	if (!getopt.argc ()) 
	{
		c = (tidy.*function) (std::cin.get ());
	}
	while (getopt.argc () && * getopt.argv ()) 
	{
		char filename [FILENAME_MAX + 1];
		pathspec.fullpath (filename, * getopt.argv ());
		if (fileopen.openedit (filename)) 
		{
			c = (tidy.*function) (std::cin.get ());
			fileopen.close ();
		}
		getopt++;
	}
	std::exit (0);
}

