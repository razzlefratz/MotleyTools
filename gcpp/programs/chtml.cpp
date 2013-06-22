/*====================================================================*
 *
 *   chtml.cpp - output c language source file as html pages; 
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
#include "../classes/oattribute.cpp"
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
#include "../classes/oenviron.cpp"
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
#include "../classes/owebpage.cpp"
#endif

#define STYLESHEET "/styles/clang.css"

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
		"s f\tdefault stylesheet is (f) [" LITERAL (STYLESHEET) "]",
		"S\tprint default stylesheet on stdout",
		(char const *) (0)
	};
	ochtml chtml (STYLESHEET);
	ogetoptv getopt;
	signed c;
	while ((c = getopt.getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 's':
			chtml.stylesheet (getopt.optarg ());
			break;
		case 'S':
			chtml.stylesheet ();
			return (0);
		default:
			break;
		}
	}
	while (getopt.argc () && * getopt.argv ()) 
	{
		chtml.html (* getopt.argv ());
		getopt++;
	}
	std::exit (0);
}

