/*====================================================================*
 *
 *   mmf2.cpp - basic makefile generator;
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
#include "../classes/omakefile.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/olist.cpp"
#include "../classes/oitem.cpp"
#include "../classes/otext.cpp"
#include "../classes/omakefile.cpp"
#include "../classes/oerror.cpp"
#include "../classes/osection.cpp"
#include "../classes/owildcard.cpp"
#include "../classes/ocontext.cpp"
#include "../classes/oscantext.cpp"
#include "../classes/oascii.cpp"
#include "../classes/ocursor.cpp"
#include "../classes/ochrupr.cpp"
#include "../classes/ochrlwr.cpp"
#include "../classes/ofilespec.cpp"
#include "../classes/opathspec.cpp"
#include "../classes/oflagword.cpp"
#include "../classes/ochrtbl.cpp"
#endif

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	static char const * optv [] = 
	{ 
		"c:f:ulp", 
		oPUTOPTV_S_FUNNEL, 
		"write an auto-execute makefile from source files named on the command line", 
		"c s\tcompiler command is s", 
		"f s\tread targets from file s ", 
		"u\ttargets are utilities ", 
		"l\ttargets are libraries ", 
		"p\ttargets are programs ", 
		(char const * ) (0)
	}; 
	ogetoptv getopt; 
	omakefile makefile; 
	signed c; 
	while ((c = getopt.getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 'c': 
			makefile.compiler (getopt.optarg ()); 
			break; 
		case 'f': 
			makefile.projectfile (getopt.optarg ()); 
			break; 
		case 'u': 
			makefile.setbits (oMAKEFILE_UTILITY); 
			makefile.clearbits (oMAKEFILE_LIBRARY); 
			break; 
		case 'l': 
			makefile.clearbits (oMAKEFILE_UTILITY); 
			makefile.setbits (oMAKEFILE_LIBRARY); 
			break; 
		case 'p': 
			makefile.clearbits (oMAKEFILE_UTILITY); 
			makefile.clearbits (oMAKEFILE_LIBRARY); 
			break; 
		default: 
			break; 
		} 
	} 
	makefile.linebreak (); 
	while (getopt.argc () && * getopt.argv ()) 
	{ 
		makefile.includefile (* getopt.argv ()); 
		getopt++ ; 
	} 
	makefile.publish (); 
	std::exit (0); 
} 

