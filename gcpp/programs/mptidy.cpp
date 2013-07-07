/*====================================================================*
 *
 *   mptidy.cpp - man page tidy program;
 *
 *.  Motley Tools by Charles Maier <cmaier@cmassoc.net>;
 *:  Copyright 2010-2013 by Charles Maier Associates;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/opathspec.hpp"
#include "../classes/ofileopen.hpp"
#include "../classes/oprofile.hpp"
#include "../classes/omptidy.hpp"

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
#include "../classes/oprofile.cpp"
#include "../classes/ocontext.cpp"
#include "../classes/owildcard.cpp"
#include "../classes/oescape.cpp"
#include "../classes/oascii.cpp"
#include "../classes/osource.cpp"
#include "../classes/oindent.cpp"
#include "../classes/oswitch.cpp"
#include "../classes/otext.cpp"
#include "../classes/omptidy.cpp"
#endif

#define PROFILE_NAME "/etc/mp.ini"     
#define SECTION_NAME "default"     

#define MPTIDY_S_PROJECT "Motley Tools"     
#define MPTIDY_S_PACKAGE "mtools-1.9.0"     
#define MPTIDY_S_PROGRAM "mtools.7"     
#define MPTIDY_S_RELEASE __DATE__

/*====================================================================*
 *   
 *   int main (int argc, char const * argv []);
 *   
 *   
 *.  Motley Tools by Charles Maier <cmaier@cmassoc.net>;
 *:  Copyright 2001-2006 by Charles Maier Associates;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	static char const * optv [] = 
	{ 
		"op:s:", 
		oPUTOPTV_S_FILTER, 
		"format C/C++ source code with preamble annotations", 
		"o\tprint default profile on stdout", 
		"p s\tprofile is (s) [" LITERAL (PROFILE_NAME) "]", 
		"s s\tsection is (s) [" LITERAL (SECTION_NAME) "]", 
		(char const *) (0)
	}; 
	ogetoptv getopt; 
	ofileopen fileopen; 
	opathspec pathspec; 
	oprofile config; 
	omptidy object; 
	char const * profile = PROFILE_NAME; 
	char const * section = SECTION_NAME; 
	signed (omptidy::* method) (signed) = & omptidy::tidy; 
	signed c; 
	while ((c = getopt.getoptv (argc, argv, optv)) != -1) 
	{ 
		switch (c) 
		{ 
		case 'o': 
			config.write (SECTION_NAME); 
			config.write (oMPTIDY_S_PROJECT, MPTIDY_S_PROJECT); 
			config.write (oMPTIDY_S_PACKAGE, MPTIDY_S_PACKAGE); 
			config.write (oMPTIDY_S_PROGRAM, MPTIDY_S_PROGRAM); 
			config.write (oMPTIDY_S_RELEASE, MPTIDY_S_RELEASE); 
			std::exit (0); 
		case 'p': 
			profile = getopt.optarg (); 
			break; 
		case 's': 
			section = getopt.optarg (); 
			break; 
		default:
			break; 
		} 
	} 
	object.project (config.string (profile, section, oMPTIDY_S_PROJECT, MPTIDY_S_PROJECT)); 
	object.package (config.string (profile, section, oMPTIDY_S_PACKAGE, MPTIDY_S_PACKAGE)); 
	object.program (config.string (profile, section, oMPTIDY_S_PROGRAM, MPTIDY_S_PROGRAM)); 
	object.release (config.string (profile, section, oMPTIDY_S_RELEASE, MPTIDY_S_RELEASE)); 
	if (!getopt.argc ()) 
	{ 
		(object.* method) (std::cin.get ()); 
	} 
	while (getopt.argc () && * getopt.argv ()) 
	{ 
		if (fileopen.openedit (* getopt.argv ())) 
		{ 
			object.filename (* getopt.argv ()); 
			(object.* method) (std::cin.get ()); 
			fileopen.close (); 
		} 
		getopt++; 
	} 
	std::exit (0); 
} 

