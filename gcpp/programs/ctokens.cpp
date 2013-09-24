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
#include "../classes/oscancode.cpp"
#include "../classes/otext.cpp"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define CTOKEN_B_ELABORATE (1 << 0)

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main(int argc, char const * argv[])

{
	static char const * optv[] = 
	{
		"e",
		oPUTOPTV_S_FUNNEL,
		"print C/C++ language tokens on stdout",
		"e\telaborate on tokens with typenames",
		(char const *)(0)
	};
	oflagword flags;
	oscancode source;
	ogetoptv getopt;
	signed c;
	while (~ (c = getopt.getoptv(argc, argv, optv)))
	{
		switch (c)
		{
		case 'e':
			flags.setbits(CTOKEN_B_ELABORATE);
			break;
		default: 
			break;
		}
	}
	while ((getopt.argc()) && (* getopt.argv()))
	{
		if (flags.anyset(CTOKEN_B_ELABORATE))
		{
			source.read(* getopt.argv()).elaborate();
		}
		else 
		{
			source.read(* getopt.argv()).enumerate();
		}
		getopt++;
	}
	std::exit(0);
}

