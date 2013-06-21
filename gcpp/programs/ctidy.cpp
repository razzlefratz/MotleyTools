/*====================================================================*
 *
 *   ctidy.cpp - tidy C/C++ source files;
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

#include "../classes/ogetoptv.hpp"
#include "../classes/opathspec.hpp"
#include "../classes/ofileopen.hpp"
#include "../classes/oflagword.hpp"
#include "../classes/oescape.hpp"
#include "../classes/octidy.hpp"

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
#include "../classes/oflagword.cpp"
#include "../classes/oescape.cpp"
#include "../classes/okeywords.cpp"
#include "../classes/oindent.cpp"
#include "../classes/ocgotowords.cpp"
#include "../classes/ocexitwords.cpp"
#include "../classes/oascii.cpp"
#include "../classes/ocollect.cpp"
#include "../classes/oinclude.cpp"
#include "../classes/ocomment.cpp"
#include "../classes/octidy.cpp"
#include "../classes/otext.cpp"
#endif

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"m:o:st",
		oPUTOPTV_S_FILTER,
		"format C/C++ source code",
		"m s\tmargin string [" LITERAL (oINDENT_MARGIN) "]",
		"o s\toffset string [" LITERAL (oINDENT_OFFSET) "]",
		"s\toffset is space",
		"t\toffset is tabs",
		(char const *) (0)
	};
	ogetoptv getopt;
	ofileopen fileopen;
	opathspec pathspec;
	oescape escape;
	octidy object;
	int (octidy::* method) (signed, signed) = & octidy::program;
	signed c;
	while ((c = getopt.getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'm':
			object.margin (escape.unescape ((char *)(getopt.args ())));
			break;
		case 'o':
			object.indent (escape.unescape ((char *)(getopt.args ())));
			break;
		case 's':
			object.indent ("   ");
			break;
		case 't':
			object.indent ("\t");
			break;
		default:
			break;
		}
	}
	if (!getopt.argc ()) 
	{
		c = (object.* method) (std::cin.get (), EOF);
	}
	while (getopt.argc () && * getopt.argv ()) 
	{
		char filename [FILENAME_MAX + 1];
		pathspec.fullpath (filename, * getopt.argv ());
		if (fileopen.openedit (filename)) 
		{
			c = (object.* method) (std::cin.get (), EOF);
			fileopen.close ();
		}
		getopt++;
	}
	std::exit (0);
}


