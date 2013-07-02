/*====================================================================*
 *
 *   sqltidy.cpp - tidy SQL source files;
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
#include <fstream>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/oflagword.hpp"
#include "../classes/ofileopen.hpp"
#include "../classes/ofilespec.hpp"
#include "../classes/opathspec.hpp"
#include "../classes/oindent.hpp"
#include "../classes/oescape.hpp"
#include "../classes/osource.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/oerror.cpp"
#include "../classes/otext.cpp"
#include "../classes/oflagword.cpp"
#include "../classes/ofileopen.cpp"
#include "../classes/ofilespec.cpp"
#include "../classes/opathspec.cpp"
#include "../classes/ocontext.cpp"
#include "../classes/owildcard.cpp"
#include "../classes/oescape.cpp"
#include "../classes/oindent.cpp"
#include "../classes/oascii.cpp"
#include "../classes/osource.cpp"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define MARGIN ""
#define OFFSET "\t"

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

static ofileopen fileopen;
static opathspec pathspec;
static oescape escape;
static oindent indent;
static osource tidy;

/*====================================================================*
 *
 *   void function (oflagword * flags);
 *
 *   read from stdin and write to stdout; indent C style text based
 *   on '{', ';' and '}' characters; leave '#' comments alone; this
 *   program is suitable for css stylesheets, awk programs and bind 
 *   name.conf files;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void function (oflagword * flags) 

{
	size_t level = 0;
	int c = std::cin.get ();
	while (c != EOF) 
	{
		switch ((char) (c)) 
		{
		case ' ':
		case '\t':
		case '\r':
		case '\n':
		case '\f':
		case '\0':
			c = std::cin.get ();
			break;
		case '#':
			indent.endline (2);
			do 
			{
				c = tidy.content (c, '\n');
			}
			while (c == '#');
			break;
		case '(':
			indent.endline (1);
			indent.newline (level++);
			c = tidy.feed (c);
			break;
		case ')':
			indent.endline (1);
			indent.newline (--level);
			c = tidy.feed (c);
			c = tidy.find (c);
			if ((c == ',') || (c == ';')) 
			{
				c = tidy.feed (c);
				break;
			}
			std::cout.put (' ');
			break;
		case ',':
		case ';':
			c = tidy.feed (c);
			break;
		default:
			indent.endline (1);
			indent.newline (level);
			c = tidy.context (c, "(,)#");
			break;
		}
	}
	indent.endline (2);
	return;
}

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"m:o:st",
		oPUTOPTV_S_FILTER,
		"tidy SQL source files",
		"m s\tmargin string [" LITERAL (MARGIN) "]",
		"o s\toffset string [" LITERAL (OFFSET) "]",
		"s\toffset is 3 spaces",
		"t\toffset is 1 tab",
		(char const *) (0)
	};
	ogetoptv getopt;
	oflagword flags;
	signed c;
	while ((c = getopt.getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{

#if 0

		case 'm':
			tidy.margin (escape.unescape ((char *)(getopt.args ())));
			break;
		case 'o':
			tidy.offset (escape.unescape ((char *)(getopt.args ())));
			break;
		case 's':
			tidy.offset ("    ");
			break;
		case 't':
			tidy.offset ("\t");
			break;

#endif

		default:
			break;
		}
	}
	if (!getopt.argc ()) 
	{
		function (& flags);
	}
	while (getopt.argc () && * getopt.argv ()) 
	{
		char filename [FILENAME_MAX + 1];
		pathspec.fullpath (filename, * getopt.argv ());
		if (fileopen.openedit (filename)) 
		{
			function (& flags);
			fileopen.close ();
		}
		getopt++;
	}
	std::exit (0);
}

