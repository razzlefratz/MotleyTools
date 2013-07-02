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
#include "../classes/ofileopen.hpp"
#include "../classes/opathspec.hpp"
#include "../classes/ophptidy.hpp"
#include "../classes/oescape.hpp"

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
#include "../classes/oascii.cpp"
#include "../classes/osource.cpp"
#include "../classes/oindent.cpp"
#include "../classes/ophptidy.cpp"
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

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"cm:o:st",
		oPUTOPTV_S_FILTER,
		"format C/C++ source code",
		"c\tcompact source",
		"m s\tmargin string [" LITERAL (oINDENT_MARGIN) "]",
		"o s\toffset string [" LITERAL (oINDENT_OFFSET) "]",
		"s\toffset is space",
		"t\toffset is tabs",
		(char const *) (0)
	};
	ogetoptv getopt;
	oescape escape;
	opathspec pathspec;
	ofileopen fileopen;
	ophptidy object;
	int (ophptidy::* function) (signed) = & ophptidy::page;
	signed c;
	while ((c = getopt.getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'c':
			object.margin ("");
			object.offset ("");
			object.finish ("");
			object.record ("");
			break;
		case 'm':
			object.margin (escape.unescape ((char *)(getopt.args ())));
			break;
		case 'o':
			object.offset (escape.unescape ((char *)(getopt.args ())));
			break;
		case 's':
			object.offset ("   ");
			break;
		case 't':
			object.offset ("\t");
			break;
		default:
			break;
		}
	}
	if (!getopt.argc ()) 
	{
		c = (object.* function) (std::cin.get ());
	}
	while (getopt.argc () && * getopt.argv ()) 
	{
		char filename [FILENAME_MAX + 1];
		pathspec.fullpath (filename, * getopt.argv ());
		if (fileopen.openedit (filename)) 
		{
			c = (object.* function) (std::cin.get ());
			fileopen.close ();
		}
		getopt++;
	}
	std::exit (0);
}

