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
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/ofileopen.hpp"
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
#include "../classes/oclangwords.cpp"
#include "../classes/octidy.cpp"
#include "../classes/osource.cpp"
#include "../classes/oindent.cpp"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define PROFILE_NAME "/etc/cfm.ini"     
#define SECTION_NAME "default"     

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
		"*34AbCf:g:hkLlmoprstw:x",
		oPUTOPTV_S_FILTER,
		"format C/C++ source code with preamble annotations",
		"*\tsquash asterisk strings",
		"3\tindent is 3 blanks",
		"4\tindent is 4 blanks",
		"A\tatheros standard format",
		"b\tinsert preamble comment block",
		"C\tconvert C++ comments to ANSI C comments",
		"f s\tuse profile (s) [" LITERAL (PROFILE_NAME) "]",
		"g s\tuse profile section (s) [" LITERAL (SECTION_NAME) "]",
		"h\tinsert header include guard",
		"k\tmake comments permanent",
		"l\tupdate " LITERAL (oCOMMENT_S_PUBLISH) " comment [" LITERAL (oCOMMENT_C_PUBLISH) "]",
		"L\tupdate " LITERAL (oCOMMENT_S_LICENSE) " comment [" LITERAL (oCOMMENT_C_LICENSE) "]",
		"m\tconvert single-line comments to multi-line comments",
		"o\toutput profile to stdout",
		"p\tupdate " LITERAL (oCOMMENT_S_PACKAGE) " comment [" LITERAL (oCOMMENT_C_PACKAGE) "]",
		"r\tupdate " LITERAL (oCOMMENT_S_RELEASE) " comment [" LITERAL (oCOMMENT_C_RELEASE) "]",
		"s\tinsert source include guard",
		"t\tindent is 1 tab",
		"w n\tbar width is (n)",
		"x\terase markers",
		(char const *) (0)
	};
	char const * profile = PROFILE_NAME;
	char const * section = SECTION_NAME;
	ogetoptv getopt;
	ofileopen fileopen;
	oprofile config;
	octidy object;
	signed (octidy::* method) (signed) = & octidy::charlie;
	signed c;
	while (~ (c = getopt.getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case '*':
			object.setbits (oCOMMENT_B_NOSTARS);
			break;
		case '3':
			object.offset ("   ");
			break;
		case '4':
			object.offset ("    ");
			break;
		case 'A':
			method = & octidy::atheros;
			break;
		case 'b':
			object.setbits (oCOMMENT_B_COMMENT);
			break;
		case 'C':
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
			object.setbits (oCOMMENT_B_FOREVER);
			break;
		case 'l':
			object.setbits (oCOMMENT_B_PUBLISH);
			break;
		case 'L':
			object.setbits (oCOMMENT_B_LICENSE);
			break;
		case 'm':
			object.setbits (oCOMMENT_B_TRIPLE);
			break;
		case 'o':
			config.write (SECTION_NAME);
			config.write (oCOMMENT_S_PACKAGE, oCOMMENT_T_PACKAGE);
			config.write (oCOMMENT_S_RELEASE, oCOMMENT_T_RELEASE);
			config.write (oCOMMENT_S_PUBLISH, oCOMMENT_T_PUBLISH);
			config.write (oCOMMENT_S_LICENSE, oCOMMENT_T_LICENSE);
			exit (0);
		case 'p':
			object.setbits (oCOMMENT_B_PACKAGE);
			break;
		case 'r':
			object.setbits (oCOMMENT_B_RELEASE);
			break;
		case 's':
			object.label ("SOURCE").state (1);
			break;
		case 't':
			object.offset ("\t");
			break;
		case 'w':
			object.width (atoi (getopt.args ()));
			break;
		case 'x':
			object.setbits (oCOMMENT_B_DISCARD);
			break;
		default: 
			break;
		}
	}
	object.package (config.string (profile, section, oCOMMENT_S_PACKAGE, oCOMMENT_T_PACKAGE));
	object.release (config.string (profile, section, oCOMMENT_S_RELEASE, oCOMMENT_T_RELEASE));
	object.publish (config.string (profile, section, oCOMMENT_S_PUBLISH, oCOMMENT_T_PUBLISH));
	object.license (config.string (profile, section, oCOMMENT_S_LICENSE, oCOMMENT_T_LICENSE));
	if (! getopt.argc ())
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
	exit (0);
}

