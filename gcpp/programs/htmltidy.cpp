/*====================================================================*
 *
 *   htmltidy.cpp - tidy html or xhtml files;
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
#include "../classes/ofilespec.hpp"
#include "../classes/opathspec.hpp"

#include "../classes/oescape.hpp"
#include "../classes/ohtmltidy.hpp"

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
#include "../classes/oindent.cpp"
#include "../classes/oflagword.cpp"
#include "../classes/okeywords.cpp"
#include "../classes/otext.cpp"
#include "../classes/oascii.cpp"
#include "../classes/oescape.cpp"
#include "../classes/ohtmltidy.cpp"
#include "../classes/ocollect.cpp"
#endif

#ifndef MAKEFILE
#include "../classes/oHTMLEmpty.cpp"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define MARGIN ""
#define OFFSET "\t"

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"m:o:st",
		oPUTOPTV_S_FILTER,
		"tidy html and xhtml source files",
		"m s\tmargin string is (s) [" LITERAL (MARGIN) "]",
		"o s\tindent string is (c) [" LITERAL (OFFSET) "]",
		"s\tindent is 3 spaces",
		"t\tindent is 1 tab",
		(char const *) (0)
	};
	ogetoptv getopt;
	ofileopen fileopen;
	opathspec pathspec;
	oescape escape;
	ohtmltidy object;
	int (ohtmltidy::* method) (signed) = & ohtmltidy::page;
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
		c = (object.* method) (std::cin.get ());
	}
	while (getopt.argc () && * getopt.argv ()) 
	{
		char filespec [FILENAME_MAX + 1];
		pathspec.fullpath (filespec, * getopt.argv ());
		if (fileopen.openedit (filespec)) 
		{
			c = (object.* method) (std::cin.get ());
			fileopen.close ();
		}
		getopt++;
	}
	std::exit (0);
}

