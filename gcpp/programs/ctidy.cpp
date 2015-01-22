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
#include "../classes/osource.cpp"
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
		"format c/c++ source code",
		oPUTOPTV_S_FILTER,
		"cm:o:st",
		"c\tcompact source",
		"m s\tmargin string is (s) [" LITERAL (oINDENT_MARGIN) "]",
		"o s\tindent string is (s) [" LITERAL (oINDENT_INDENT) "]",
		"s\tindent string is 3 spaces",
		"t\tindent string is 1 tab",
		(char const *) (0)
	};
	ogetoptv getopt;
	oescape escape;
	opathspec pathspec;
	ofileopen fileopen;
	octidy source;
	signed (octidy::* format) (signed) = & octidy::program;
	signed c;
	while (~ (c = getopt.getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'c':
			source.margin ("");
			source.indent ("");
			source.finish ("");
			source.record ("");
			break;
		case 'm':
			source.margin (escape.unescape ((char *) (getopt.args ())));
			break;
		case 'o':
			source.indent (escape.unescape ((char *) (getopt.args ())));
			break;
		case 's':
			source.indent ("   ");
			break;
		case 't':
			source.indent ("\t");
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

