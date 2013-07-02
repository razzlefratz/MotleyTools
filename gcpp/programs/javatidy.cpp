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
		"program CSS functions",
		"c\tcompact stylesheet",
		"m s\tmargin string [" LITERAL (oINDEX_MARGIN) "]",
		"o s\toffset string [" LITERAL (oINDEX_OFFSET) "]",
		"s\toffset is space",
		"t\toffset is tabs",
		(char const *) (0)
	};
	ogetoptv getopt;
	ofileopen fileopen;
	opathspec pathspec;
	oescape escape;
	oprogram program;
	signed (oprogram::* method) (signed) = & oprogram::java;
	signed c;
	while ((c = getopt.getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'c':
			program.offset ("").record ("");
			break;
		case 'm':
			program.margin (escape.unescape ((char *)(getopt.args ())));
			break;
		case 'o':
			program.offset (escape.unescape ((char *)(getopt.args ())));
			break;
		case 's':
			program.offset ("   ");
			break;
		case 't':
			program.offset ("\t");
			break;
		default:
			break;
		}
	}
	if (!getopt.argc ()) 
	{
		(program.* method) (std::cin.get ());
	}
	while (getopt.argc () && * getopt.argv ()) 
	{
		char filename [FILENAME_MAX + 1];
		pathspec.fullpath (filename, * getopt.argv ());
		if (fileopen.openedit (filename)) 
		{
			(program.* method) (std::cin.get ());
			fileopen.close ();
		}
		getopt++;
	}
	std::exit (0);
}

