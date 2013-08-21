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
#include "../classes/osource.cpp"
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
 *--------------------------------------------------------------------*/

signed pack (signed c, signed (* get)(signed))
{
	do 
	{ 
		c = get (c); 
	} 
	while (oascii::isblank (c)); 
	if (oascii::nobreak (c)) 
	{ 
		std::cout.put (' '); 
	} 
	return (c);
}

/*====================================================================*
 *
 *   void function (signed c, signed o, signed e);
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

signed function (signed c) 

{ 
	while (c != EOF) 
	{ 
		int (* get) (int) = osource::span; 
		if (oascii::isblank (c)) 
		{ 
			get = osource::next; 
			c = pack (c, get);
		} 
		while (oascii::nobreak (c)) 
		{ 
			if (c == '#') 
			{ 
				do 
				{ 
					c = osource::keep (c); 
				} 
				while (oascii::nobreak (c)); 
				continue; 
			} 
			if (oascii::isquote (c)) 
			{ 
				c = osource::literal (c); 
				continue; 
			} 
			if (oascii::isblank (c)) 
			{ 
				c = pack (c, get);
				continue; 
			} 
			c = osource::keep (c); 
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
		"", 
		oPUTOPTV_S_FILTER, 
		"minimize white space", 
		(char const *) (0)
	}; 
	ogetoptv getopt; 
	opathspec pathspec; 
	ofileopen fileopen; 
	signed c; 
	while (~ (c = getopt.getoptv (argc, argv, optv))) 
	{ 
		switch (c) 
		{ 
		default: 
			break; 
		} 
	} 
	if (! getopt.argc ()) 
	{ 
		function (std::cin.get ()); 
	} 
	while (getopt.argc () && * getopt.argv ()) 
	{ 
		if (fileopen.openedit (* getopt.argv ())) 
		{ 
			function (std::cin.get ()); 
			fileopen.close (); 
		} 
		getopt++; 
	} 
	std::exit (0); 
} 

