/*====================================================================*
 *
 *   profile.cpp - demonstrate oprofile object class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cerrno>
#include <cstdlib>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/oprofile.hpp"
#include "../classes/oerror.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/oprofile.cpp"
#include "../classes/oswitch.cpp"
#include "../classes/oerror.cpp"
#include "../classes/oascii.cpp"
#include "../classes/otext.cpp"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define SECTION ""
#define ELEMENT ""
#define DEFAULT ""

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [])

{
	static char const * optv [] = 
	{
		"s:e:d:",
		oPUTOPTV_S_FUNNEL,
		"demonstrate oprofile object class",
		"s s\tsection name is (s) [" SECTION "]",
		"e s\telement name is (s) [" ELEMENT "]",
		"d s\tdefault text is (s) [" DEFAULT "]",
		(char const *) (0)
	};
	oprofile profile;
	char const * section = SECTION;
	char const * element = ELEMENT;
	char const * content = DEFAULT;
	ogetoptv getopt;
	oputoptv putopt;
	signed c;
	while (~ (c = getopt.getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 's':
			section = getopt.args ();
			break;
		case 'e':
			element = getopt.args ();
			break;
		case 'd':
			content = getopt.args ();
			break;
		default: 
			break;
		}
	}
	if (getopt.argc ())
	{
		if ((section == (char *) (0)) || (* section == (char) (0)))
		{
			oerror::error (1, EINVAL, "No profile section specified");
		}
		if ((element == (char *) (0)) || (* element == (char) (0)))
		{
			oerror::error (1, EINVAL, "No section element specified");
		}
	}
	while ((getopt.argc ()) && (* getopt.argv ()))
	{
		std::cout << profile.string (* getopt.argv (), section, element, content) << "\n";
		getopt++;
	}
	std::exit (0);
}

