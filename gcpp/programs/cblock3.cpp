/*====================================================================*
 *
 *   ctokens.cpp - output c language source file as a token list; 
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
#include "../classes/oflagword.hpp"
#include "../classes/oscancode.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/oerror.cpp"
#include "../classes/oflagword.cpp"
#include "../classes/okeywords.cpp"
#include "../classes/oscantext.cpp"
#include "../classes/oascii.cpp"
#include "../classes/ochrlwr.cpp"
#include "../classes/ochrupr.cpp"
#include "../classes/ochrtbl.cpp"
#include "../classes/ocursor.cpp"
#include "../classes/ocprocwords.cpp"
#include "../classes/oclangwords.cpp"
#include "../classes/ocpluswords.cpp"
#include "../classes/oconstants.cpp"
#include "../classes/ofunctions.cpp"
#include "../classes/oscanfile.cpp"
#include "../classes/ofileopen.cpp"
#include "../classes/opathspec.cpp"
#include "../classes/ofilespec.cpp"
#include "../classes/owildcard.cpp"
#include "../classes/ocontext.cpp"
#include "../classes/otext.cpp"
#endif

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

static void function () 

{ 
	oscanfile source; 
	while (! source.end ()) 
	{ 
		<< << << < HEAD if (source.scantoken ().isspace ()) == == == = source.scantoken (); 
		if (source.isspace ()) >> >> >> > 6f95020476b52cf467ba9cc9ea46d424fb7d7b40 
		{ 
			source.scanspace (); 
		} 
		<< << << < HEAD else if (source.havetoken ("while")) 
		{ 
		} 
		else if (source.havetoken ("do")) 
		{ 
		} 
		else if (source.havetoken ("switch")) 
		{ 
		} 
		else if (source.havetoken ("if")) 
		{ 
		} 
		else if (source.havetoken ("return")) 
		{ 
		} 
		source.write ().flush (); 
		== == == = source.print ().flush (); 
		>> >> >> > 6f95020476b52cf467ba9cc9ea46d424fb7d7b40
	} 
	return; 
} 

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	static char const * optv [] = 
	{ 
		"", 
		oPUTOPTV_S_FUNNEL, 
		"C Language Block Manger", 
		(char const * ) (0)
	}; 
	ofileopen fileopen; 
	opathspec pathspec; 
	ogetoptv getopt; 
	signed c; 
	while ((c = getopt.getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		default: 
			break; 
		} 
	} 
	if (! getopt.argc ()) 
	{ 
		function (); 
	} 
	while (getopt.argc () && * getopt.argv ()) 
	{ 
		if (fileopen.openedit (* getopt.argv ())) 
		{ 
			function (); 
			fileopen.close (); 
		} 
		getopt++ ; 
	} 
	std::exit (0); 
} 

