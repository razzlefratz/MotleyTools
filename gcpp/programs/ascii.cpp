/*====================================================================*
 *
 *   ascii.cpp - enumerate character classes;
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
#include "../classes/oascii.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/oerror.cpp"
#include "../classes/oascii.cpp"
#include "../classes/otext.cpp"
#endif

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
		"display character classes",
		oPUTOPTV_S_DIVINE,
		"em",
		"e\tenumerate classes on stdout",
		"m\tprint class matrix on stdout",
		(char const *) (0)
	};
	ogetoptv getopt;
	oascii ascii;
	signed c;
	while (~ (c = getopt.getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'e':
			ascii.enumerate ();
			break;
		case 'm':
			ascii.matrix ();
			break;
		default: 
			break;
		}
	}
	if (! getopt.argc ())
	{
	}
	while (getopt.argc () && * getopt.argv ())
	{
		getopt++;
	}
	std::exit (0);
}

