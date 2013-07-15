/*====================================================================*
 *
 *   chtml.cpp - print C language source file as html page; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <cstdlib>
#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/ochtml.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/oerror.cpp"
#include "../classes/oitem.cpp"
#include "../classes/olist.cpp"
#include "../classes/otext.cpp"
#include "../classes/oglossary.cpp"
#include "../classes/owildcard.cpp"
#include "../classes/ocontext.cpp"
#include "../classes/ocursor.cpp"
#include "../classes/oscantext.cpp"
#include "../classes/ochrtbl.cpp"
#include "../classes/ochrlwr.cpp"
#include "../classes/ochrupr.cpp"
#include "../classes/oascii.cpp"
#include "../classes/ofilespec.cpp"
#include "../classes/opathspec.cpp"
#include "../classes/okeywords.cpp"
#include "../classes/oindent.cpp"
#include "../classes/osession.cpp"
#include "../classes/oscancode.cpp"
#include "../classes/ochtml.cpp"
#include "../classes/ocprocwords.cpp"
#include "../classes/oclangwords.cpp"
#include "../classes/ocpluswords.cpp"
#include "../classes/oconstants.cpp"
#include "../classes/ofunctions.cpp"
#include "../classes/oISOGlyph.cpp"
#include "../classes/oMetaElement.cpp"
#include "../classes/oPageLinkElement.cpp"
#include "../classes/oSpanElement.cpp"
#include "../classes/oAnchorElement.cpp"
#include "../classes/oCoreAttributes.cpp"
#include "../classes/oi18nAttributes.cpp"
#include "../classes/oLinkAttributes.cpp"
#include "../classes/oAttribute.cpp"
#include "../classes/owebpage.cpp"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define STYLESHEET "clang.css"

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	static char const * optv [] = 
	{ 
		"s:S", 
		oPUTOPTV_S_FUNNEL, 
		"c to html file formatter having absolutely no features !", 
		"s s\tuse CSS2 stylesheet (s) [" LITERAL (STYLESHEET) "]", 
		"S\tprint CSS2 stylesheet on stdout", 
		(char const *) (0)
	}; 
	ochtml page (STYLESHEET); 
	ogetoptv getopt; 
	signed c; 
	while ((c = getopt.getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 's': 
			page.stylesheet (getopt.optarg ()); 
			break; 
		case 'S': 
			page.css2 (); 
			return (0); 
		default: 
			break; 
		} 
	} 
	while (getopt.argc () && * getopt.argv ()) 
	{ 
		page.html (* getopt.argv ()); 
		getopt++; 
	} 
	std::exit (0); 
} 

