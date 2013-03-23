/*====================================================================*
 *
 *   cfm.cpp - format C/C++ source files;
 *
 *   custom C/C++ source code formatter;
 *
 *.  Motley Tools by Charles Maier <cmaier@cmassoc.net>;
 *:  Copyright 2001-2006 by Charles Maier Associates;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdlib>
#include <cstring>
#include <iostream>            

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/oerror.hpp"
#include "../classes/oescape.hpp"
#include "../classes/ofileopen.hpp"
#include "../classes/opathspec.hpp"
#include "../classes/oprofile.hpp"
#include "../classes/octidy.hpp"

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
#include "../classes/okeywords.cpp"
#include "../classes/opathspec.cpp"
#include "../classes/oprofile.cpp"
#include "../classes/ocontext.cpp"
#include "../classes/owildcard.cpp"
#include "../classes/oescape.cpp"
#include "../classes/oswitch.cpp"
#include "../classes/otext.cpp"
#include "../classes/oascii.cpp"
#include "../classes/oinclude.cpp"
#include "../classes/ocomment.cpp"
#include "../classes/ocgotowords.cpp"
#include "../classes/ocexitwords.cpp"
#include "../classes/oindent.cpp"
#include "../classes/octidy.cpp"
#include "../classes/ocollect.cpp"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define CFM_S_PROFILE "/etc/cfm.ini"     
#define CFM_S_SECTION "default"     
#define CFM_S_PACKAGE "Motley Tools by Charles Maier <cmaier@cmassoc.net>"
#define CFM_S_RELEASE "Copyright (c) 2001-2006 by Charles Maier."
#define CFM_S_LICENSE "Permission to use, copy, modify, and/or distribute this software\n *   for any purpose with or without fee is hereby granted, provided\n *   that the above copyright notice and this permission notice appear\n *   in all copies.\n *\n *   THE SOFTWARE IS PROVIDED \"AS IS\" AND THE AUTHOR DISCLAIMS ALL\n *   WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED\n *   WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL\n *   THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR\n *   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM\n *   LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,\n *   NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN\n *   CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE."
#define CFM_S_PREFACE ""
#define CFM_S_SPECIAL ""

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
		"34acf:g:hklLmopPrstw:x",
		oPUTOPTV_S_FILTER,
		"format C/C++ source code with preamble annotations",
		"3\tindent is 3 blanks",
		"4\tindent is 4 blanks",
		"a\tatheros standard format",
		"c\tconvert C++ comments to standard C comments",
		"f s\tuse profile (s) [" LITERAL (CFM_S_PROFILE) "]",
		"g s\tuse profile section (s) [" LITERAL (CFM_S_SECTION) "]",
		"h\tinsert header include guard",
		"k\tmake comments permanent",
		"l\tupdate " LITERAL (oCOMMENT_S_LICENSE) " comment",
		"L\tupdate " LITERAL (oCOMMENT_S_SPECIAL) " comment",
		"m\tconvert single-line comments to multi-line comments",
		"o\toutput profile to stdout",
		"p\tupdate " LITERAL (oCOMMENT_S_PACKAGE) " comment",
		"P\tupdate " LITERAL (oCOMMENT_S_PREFACE) " comment",
		"r\tupdate " LITERAL (oCOMMENT_S_RELEASE) " comment",
		"s\tinsert source include guard",
		"t\tindent is 1 tab",
		"w n\tbar width is (n)",
		"x\terase markers",
		(char const *) (0)
	};
	ogetoptv getopt;
	ofileopen fileopen;
	opathspec pathspec;
	oprofile config;
	octidy object;
	int (octidy::* method) (signed, signed) = &octidy::charlie;
	char const * profile = CFM_S_PROFILE;
	char const * section = CFM_S_SECTION;
	char const * package = CFM_S_PACKAGE;
	char const * release = CFM_S_RELEASE;
	char const * license = CFM_S_LICENSE;
	char const * preface = CFM_S_PREFACE;
	char const * special = CFM_S_SPECIAL;
	signed c;
	while ((c = getopt.getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case '3':
			object.indent ("   ");
			break;
		case '4':
			object.indent ("    ");
			break;
		case 'a':
			method = &octidy::atheros;
			break;
		case 'c':
			object.setbits (oCOMMENT_B_DOUBLE);
			break;
		case 'f':
			profile = getopt.args ();
			break;
		case 'g':
			section = getopt.args ();
			break;
		case 'h':
			object.label ("HEADER").state (1);
			break;
		case 'k':
			object.setbits (oCOMMENT_B_PERMANENT);
			break;
		case 'l':
			object.setbits (oCOMMENT_B_LICENSE);
			break;
		case 'L':
			object.setbits (oCOMMENT_B_SPECIAL);
			break;
		case 'm':
			object.setbits (oCOMMENT_B_TRIPLE);
			break;
		case 'o':
			config.write (CFM_S_SECTION);
			config.write (oCOMMENT_S_PACKAGE, CFM_S_PACKAGE);
			config.write (oCOMMENT_S_RELEASE, CFM_S_RELEASE);
			config.write (oCOMMENT_S_LICENSE, CFM_S_LICENSE);
			config.write (oCOMMENT_S_PREFACE, CFM_S_PREFACE);
			config.write (oCOMMENT_S_SPECIAL, CFM_S_SPECIAL);
			std::cout << std::endl;
			std::exit (0);
		case 'p':
			object.setbits (oCOMMENT_B_PACKAGE);
			break;
		case 'P':
			object.setbits (oCOMMENT_B_PREFACE);
			break;
		case 'r':
			object.setbits (oCOMMENT_B_RELEASE);
			break;
		case 's':
			object.label ("SOURCE").state (1);
			break;
		case 't':
			object.indent ("\t");
			break;
		case 'w':
			object.width (std::atoi (getopt.args ()));
			break;
		case 'x':
			object.setbits (oCOMMENT_B_DISCARD);
			break;
		default:
			break;
		}
	}
	package = config.string (profile, section, oCOMMENT_S_PACKAGE, package);
	release = config.string (profile, section, oCOMMENT_S_RELEASE, release);
	license = config.string (profile, section, oCOMMENT_S_LICENSE, license);
	preface = config.string (profile, section, oCOMMENT_S_PREFACE, preface);
	special = config.string (profile, section, oCOMMENT_S_SPECIAL, special);
	object.package (package);
	object.release (release);
	object.license (license);
	object.preface (preface);
	object.special (special);
	if (!getopt.argc ()) 
	{
		c = (object.*method) (std::cin.get (), EOF);
	}
	while (getopt.argc () && * getopt.argv ()) 
	{
		char filename [FILENAME_MAX];
		pathspec.fullpath (filename, * getopt.argv ());
		if (fileopen.openedit (filename)) 
		{
			object.filename (filename);
			c = (object.*method) (std::cin.get (), EOF);
			fileopen.close ();
		}
		getopt++;
	}
	std::exit (0);
}

