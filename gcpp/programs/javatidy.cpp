/*====================================================================*
 *
 *   javatidy.cpp - tidy java source code;
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
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/ofileopen.hpp"
#include "../classes/opathspec.hpp"
#include "../classes/oescape.hpp"
#include "../classes/oprogram.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/oerror.cpp"
#include "../classes/oflagword.cpp"
#include "../classes/ofileopen.cpp"
#include "../classes/ofilespec.cpp"
#include "../classes/opathspec.cpp"
#include "../classes/ocontext.cpp"
#include "../classes/owildcard.cpp"
#include "../classes/oescape.cpp"
#include "../classes/oascii.cpp"
#include "../classes/osource.cpp"
#include "../classes/oindent.cpp"
#include "../classes/oprogram.cpp"
#include "../classes/otext.cpp"
#endif

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [])

{
	static char const * optv [] =
	{
		"cm:o:st",
		oPUTOPTV_S_FILTER,
		"format java source code",
		"c\tcompact source",
		"m s\tmargin string is (s) [" LITERAL (oINDENT_MARGIN) "]",
		"o s\toffset string is (s) [" LITERAL (oINDENT_OFFSET) "]",
		"s\toffset string is 3 spaces",
		"t\toffset string is 1 tab",
		(char const *) (0)
	};
	ogetoptv getopt;
	oescape escape;
	opathspec pathspec;
	ofileopen fileopen;
	oprogram source;
	signed (oprogram::* format) (signed) = & oprogram::java;
	signed c;
	while (~ (c = getopt.getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'c':
			source.margin ("");
			source.offset ("");
			source.finish ("");
			source.record ("");
			break;
		case 'm':
			source.margin (escape.unescape ((char *) (getopt.args ())));
			break;
		case 'o':
			source.offset (escape.unescape ((char *) (getopt.args ())));
			break;
		case 's':
			source.offset ("   ");
			break;
		case 't':
			source.offset ("\t");
			break;
		default: 
			break;
		}
	}
	if (! getopt.argc ())
	{
		(source.* format) (std::cin.get ());
	}
	while (getopt.argc () && * getopt.argv ())
	{
		if (fileopen.openedit (* getopt.argv ()))
		{
			(source.* format) (std::cin.get ());
			fileopen.close ();
		}
		getopt++;
	}
	std::exit (0);
}

