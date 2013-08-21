/*====================================================================*
 *
 *   dnstidy.cpp - tidy DNS config files;
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
#include "../classes/oflagword.hpp"
#include "../classes/opathspec.hpp"
#include "../classes/ofileopen.hpp"
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
#include "../classes/otext.cpp"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define MARGIN ""
#define OFFSET "\t"

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

static oindent indent; 
static osource tidy; 

/*====================================================================*
 *
 *   void function (oflagword * flags);
 *
 *   read from stdin and write to stdout; indent C style text based
 *   only on '{', ';' and '}' characters; leave '#' comments alone; 
 *   this program is suitable for css stylesheets, awk programs and  
 *   bind name.conf files;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void function (oflagword * flags) 

{ 
	size_t level = 0; 
	size_t space = 0; 
	signed c = std::cin.get (); 
	while (c != EOF) 
	{ 
		if (isspace (c)) 
		{ 
			c = std::cin.get (); 
			continue; 
		} 
		if ((c == ',') || (c == ';')) 
		{ 
			c = tidy.keep (c); 
			continue; 
		} 
		if (c == '#') 
		{ 
			indent.endline (space); 
			do 
			{ 
				c = tidy.content (c, '\n'); 
			} 
			while (c == '#'); 
			continue; 
		} 
		if (c == '{') 
		{ 
			if (! level) 
			{ 
				indent.endline (1); 
			} 
			indent.endline (1); 
			indent.newline (level++); 
			c = tidy.keep (c); 
			space = 1; 
			continue; 
		} 
		if (c == '}') 
		{ 
			indent.endline (1); 
			indent.newline (-- level); 
			c = tidy.keep (c); 
			if (c != ';') 
			{ 
				std::cout.put (';'); 
			} 
			if (! level) 
			{ 
				indent.endline (1); 
			} 
			space = 1; 
			continue; 
		} 
		indent.endline (1); 
		indent.newline (level); 
		c = tidy.context (c, "{};"); 
		space = 2; 
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
		"format dns configuration files", 
		"m s\tmargin string is (s) [" LITERAL (MARGIN) "]", 
		"o s\toffset string is (s) [" LITERAL (OFFSET) "]", 
		"s\toffset string is 3 spaces", 
		"t\toffset string is 1 tab", 
		(char const *) (0)
	}; 
	ogetoptv getopt; 
	oescape escape; 
	opathspec pathspec; 
	ofileopen fileopen; 
	oflagword flags; 
	signed c; 
	while (~ (c = getopt.getoptv (argc, argv, optv))) 
	{ 
		switch (c) 
		{ 

#if 0

		case 'm': 
			tidy.margin (escape.unescape ((char *) (getopt.args ()))); 
			break; 
		case 'o': 
			tidy.offset (escape.unescape ((char *) (getopt.args ()))); 
			break; 
		case 's': 
			tidy.offset ("   "); 
			break; 
		case 't': 
			tidy.offset (OFFSET); 
			break; 

#endif

		default: 
			break; 
		} 
	} 
	if (! getopt.argc ()) 
	{ 
		function (& flags); 
	} 
	while (getopt.argc () && * getopt.argv ()) 
	{ 
		if (fileopen.openedit (* getopt.argv ())) 
		{ 
			function (& flags); 
			fileopen.close (); 
		} 
		getopt++; 
	} 
	std::exit (0); 
} 

