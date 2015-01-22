/*====================================================================*
 *
 *   space2.cpp - minimize white space;
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
#include "../classes/osource.hpp"
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
#include "../classes/ocontext.cpp"
#include "../classes/owildcard.cpp"
#include "../classes/oflagword.cpp"
#include "../classes/osource.cpp"
#include "../classes/oescape.cpp"
#include "../classes/oascii.cpp"
#include "../classes/otext.cpp"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define SPACE_NEWLINE '\t'
#define SPACE_ENDLINE '\0'

/*====================================================================*
 *
 *   signed pack (signed c, signed o, signed (* get)(signed));
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed pack (signed c, signed newline, signed (get) (signed))

{
	do 
	{
		c = get (c);
	}
	while (oascii::isblank (c));
	if (oascii::nobreak (c))
	{
		if (newline)
		{
			std::cout.put (newline);
		}
	}
	return (c);
}

/*====================================================================*
 *
 *   void function (signed c, signed newline, signed endline);
 *
 *   read stdin and write stdout; replace leading spaces and tabs
 *   with character o unless it is NUL; replace embedded spaces and
 *   tabs with one space; discard trailing spaces and tabs; replace
 *   newline with character e unless it is NUL;
 *
 *   write literal strings, enclosed in quotes or apostrophes, as
 *   as read; ignore escaped newlines for lines that start in first
 *   column;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed function (signed c, signed newline, signed endline)

{
	while (c != EOF)
	{
		signed (* get) (signed) = & osource::peek;
		if (oascii::isblank (c))
		{
			get = & osource::feed;
			c = pack (c, newline, get);
		}
		while (oascii::nobreak (c))
		{
			if (c == '#')
			{
				c = osource::consume (c);
				continue;
			}
			if (oascii::isquote (c))
			{
				c = osource::literal (c);
				continue;
			}
			if (oascii::isblank (c))
			{
				c = pack (c, ' ', get);
				continue;
			}
			c = osource::keep (c);
		}
		if (endline)
		{
			std::cout.put (endline);
		}
		c = osource::keep (c);
	}
	return (c);
}

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [])

{
	static char const * optv [] =
	{
		"minimize white space",
		oPUTOPTV_S_FILTER,
		"c:r:",
		(char const *) (0)
	};
	ogetoptv getopt;
	ofileopen fileopen;
	signed newline = SPACE_NEWLINE;
	signed endline = SPACE_ENDLINE;
	signed c;
	while (~ (c = getopt.getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'c':
			newline = * oescape::unescape ((char *) (getopt.args ()));
			break;
		case 'r':
			endline = * oescape::unescape ((char *) (getopt.args ()));
			break;
		default: 
			break;
		}
	}
	if (! getopt.argc ())
	{
		function (std::cin.get (), newline, endline);
	}
	while (getopt.argc () && * getopt.argv ())
	{
		if (fileopen.openedit (* getopt.argv ()))
		{
			function (std::cin.get (), newline, endline);
			fileopen.close ();
		}
		getopt++;
	}
	std::exit (0);
}

