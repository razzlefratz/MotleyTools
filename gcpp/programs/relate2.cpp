/*====================================================================*
 *
 *   relate.cpp - organize dependency information; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <cstdlib>
#include <fstream>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/oflagword.hpp"
#include "../classes/odepend.hpp"
#include "../classes/oqueue.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/oerror.cpp"
#include "../classes/oflagword.cpp"
#include "../classes/odepend.cpp"
#include "../classes/oqueue.cpp"
#include "../classes/opathspec.cpp"
#include "../classes/owildcard.cpp"
#include "../classes/oascii.cpp"
#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#define RELATE_B_REPORT (1 << 0)
#define RELATE_B_INVERT (1 << 1)

#define RELATE_C_SEPARATOR  ':'
#define RELATE_C_TERMINATOR ';'

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

static odepend depend;

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"nf",
		oPUTOPTV_S_FUNNEL,
		"organize dependency information",
		"n\tneed summary ",
		"f\tfeed summary ",
		(char const *) (0)
	};
	std::ifstream source;
	ogetoptv getopt;
	oflagword flags;
	signed c;
	while ((c = getopt.getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'n':
			flags.setbits (RELATE_B_REPORT);
			flags.clearbits (RELATE_B_INVERT);
			break;
		case 'f':
			flags.setbits (RELATE_B_REPORT);
			flags.setbits (RELATE_B_INVERT);
			break;
		default:
			break;
		}
	}
	if (!getopt.argc ()) 
	{
		depend.populate (RELATE_C_SEPARATOR, RELATE_C_TERMINATOR, flags.anyset (RELATE_B_INVERT));
	}
	while (getopt.argc () && * getopt.argv ()) 
	{
		source.open (* getopt.argv (), std::ifstream::in);
		if (source.good ()) 
		{
			std::cin.rdbuf (source.rdbuf ());
			depend.populate (RELATE_C_SEPARATOR, RELATE_C_TERMINATOR, flags.anyset (RELATE_B_INVERT));
		}
		source.close ();
		getopt++;
	}
	if (flags.anyset (RELATE_B_REPORT)) 
	{
		depend.structure ();
	}
	else 
	{
		odepend::nodes.enumerate ();
	}
	std::exit (0);
}

