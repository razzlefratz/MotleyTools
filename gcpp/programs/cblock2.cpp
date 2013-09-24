/*====================================================================*
 *
 *   cblock.cpp - C Language blocker;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>
#include <cstdlib>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/ogetoptv.hpp"
#include "../classes/ofileopen.hpp"
#include "../classes/ofilespec.hpp"
#include "../classes/opathspec.hpp"
#include "../classes/ocontext.hpp"
#include "../classes/oescape.hpp"
#include "../classes/ocblock.hpp"
#include "../classes/oerror.hpp"

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
#include "../classes/osource.cpp"
#include "../classes/ocblock.cpp"
#include "../classes/oascii.cpp"
#include "../classes/otext.cpp"
#endif

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int main(int argc, char const * argv[])

{
	static char const * optv[] = 
	{
		"p",
		oPUTOPTV_S_FILTER,
		"C/C++ source code blocker",
		(char const *)(0)
	};
	ogetoptv getopt;
	oescape escape;
	opathspec pathspec;
	ofileopen fileopen;
	ocblock object;
	signed (ocblock::* method)(signed) = & ocblock::program;
	signed c;
	while (~ (c = getopt.getoptv(argc, argv, optv)))
	{
		switch (c)
		{
		default: 
			break;
		}
	}
	if (! getopt.argc())
	{
		(object.* method)(std::cin.get());
	}
	while (getopt.argc() && * getopt.argv())
	{
		if (fileopen.openedit(* getopt.argv()))
		{
			(object.* method)(std::cin.get());
			fileopen.close();
		}
		getopt++;
	}
	std::exit(0);
}

