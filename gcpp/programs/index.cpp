/*====================================================================*
 *
 *   index.cpp - produce html file index;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <cstdlib>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/ofindspec.hpp"
#include "../classes/oHTMLIndex.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/oerror.cpp"
#include "../classes/oattribute.cpp"
#include "../classes/oitem.cpp"
#include "../classes/olist.cpp"
#include "../classes/otext.cpp"
#include "../classes/owildcard.cpp"
#include "../classes/ocontext.cpp"
#include "../classes/owildcard.cpp"
#include "../classes/opathspec.cpp"
#include "../classes/ofindspec.cpp"
#include "../classes/oindent.cpp"
#include "../classes/osession.cpp"
#endif

#ifndef MAKEFILE
#include "../classes/oMetaElement.cpp"
#include "../classes/oPageLinkElement.cpp"
#include "../classes/oSpanElement.cpp"
#include "../classes/oAnchorElement.cpp"
#include "../classes/oCoreAttributes.cpp"
#include "../classes/oi18nAttributes.cpp"
#include "../classes/oLinkAttributes.cpp"
#include "../classes/oHTMLIndex.cpp"
#include "../classes/owebpage.cpp"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define INDEX_COLUMNS 3

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [])

{
	static char const * optv [] = 
	{
		"c:s:St:",
		oPUTOPTV_S_FUNNEL,
		"produce html file index",
		"c n\tdisplay (n) columns [" LITERAL (INDEX_COLUMNS) "]",
		"s s\tuse CSS2 stylesheet (s)",
		"S\tprint CSS2 stylesheet on stdout",
		"t s\ttitle string is (s)",
		(char const *) (0)
	};
	ogetoptv getopt;
	oerror message;
	ofindspec findspec;
	oHTMLIndex page;
	unsigned columns = INDEX_COLUMNS;
	signed c;
	while (~ (c = getopt.getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'c':
			columns = atoi (getopt.optarg ());
			break;
		case 's':
			page.stylesheet (getopt.optarg ());
			break;
		case 'S':
			page.css2 ();
			return (0);
		case 't':
			page.title (getopt.optarg ());
			break;
		default: 
			break;
		}
	}
	while (getopt.argc () && * getopt.argv ())
	{
		findspec.fullname (* getopt.argv ());
		page.collect (findspec.pathname (), findspec.filename ());
		getopt++;
	}
	page.publish (columns);
	std::exit (0);
}

