/*====================================================================*
 *
 *   csstidy.cpp - tidy CSS source code;
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
#include "../classes/oescape.hpp"
#include "../classes/oprogram.hpp"
#include "../classes/oascii.hpp"

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
#include "../classes/oindent.cpp"
#include "../classes/oascii.cpp"
#include "../classes/oprogram.cpp"
#include "../classes/ocollect.cpp"
#include "../classes/otext.cpp"
#endif

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

static oprogram program;

/*====================================================================*
 *
 *   void function (oflagword * flags);
 *
 *   read from stdin and write to stdout; indent C style text based
 *   on '{', ';' and '}' characters; leave '#' comments alone; this
 *   program is suitable for css functions, awk programs and bind 
 *   name.conf files;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static signed function (signed c, signed e) 

{
	unsigned level = 0;
	unsigned space = 0;
	while ((c != e) && (c != EOF)) 
	{
		if (oascii::isspace (c)) 
		{
			c = std::cin.get ();
			continue;
		}
		if ((c == ',') || (c == ';')) 
		{
			c = program.keep (c);
			c = program.find (c);
			continue;
		}
		if (c == '{') 
		{
			program.space (1);
			program.level (level++);
			c = program.keep (c);
			c = program.find (c);
			space = 1;
			continue;
		}
		if (c == '}') 
		{
			program.space (1);
			program.level (--level);
			c = program.keep (c);
			c = program.find (c);
			space = 2;
			continue;
		}
		program.space (space);
		program.level (level);
		c = program.context (c, "{;}</>");
		space = 1;
	}
	program.space (2);
	return (c);
}


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
	signed c;
	while ((c = getopt.getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'c':
			program.indent ("").record ("");
			break;
		case 'm':
			program.margin (escape.unescape ((char *)(getopt.args ())));
			break;
		case 'o':
			program.indent (escape.unescape ((char *)(getopt.args ())));
			break;
		case 's':
			program.indent ("   ");
			break;
		case 't':
			program.indent ("\t");
			break;
		default:
			break;
		}
	}
	if (!getopt.argc ()) 
	{
		function (std::cin.get (), EOF);
	}
	while (getopt.argc () && * getopt.argv ()) 
	{
		char filename [FILENAME_MAX + 1];
		pathspec.fullpath (filename, * getopt.argv ());
		if (fileopen.openedit (filename)) 
		{
			function (std::cin.get (), EOF);
			fileopen.close ();
		}
		getopt++;
	}
	std::exit (0);
}

