/*====================================================================*
 *
 *   tokens.cpp - output c language source file as a token list;
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
#include "../classes/oscantext.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/oerror.cpp"
#include "../classes/otext.cpp"
#include "../classes/oflagword.cpp"
#include "../classes/oscantext.cpp"
#include "../classes/oascii.cpp"
#include "../classes/ochrlwr.cpp"
#include "../classes/ochrupr.cpp"
#include "../classes/ochrtbl.cpp"
#include "../classes/ocursor.cpp"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define TOKEN_B_ELABORATE (1 << 0)

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [])

{
	static char const * optv [] =
	{
		"print tokens on stdout",
		oPUTOPTV_S_FUNNEL,
		"e",
		"e\telaborate on tokens with typenames",
		(char const *) (0)
	};
	ogetoptv getopt;
	oflagword flags;
	oscantext source;
	signed c;
	while (~ (c = getopt.getoptv (argc, argv, optv)))
	{
		switch ((char) (c))
		{
		case 'e':
			flags.setbits (TOKEN_B_ELABORATE);
			break;
		default: 
			break;
		}
	}
	while (getopt.argc () && * getopt.argv ())
	{
		if (flags.anyset (TOKEN_B_ELABORATE))
		{
			source.read (* getopt.argv ()).elaborate ();
		}
		else 
		{
			source.read (* getopt.argv ()).enumerate ();
		}
		getopt++;
	}
	std::exit (0);
}

