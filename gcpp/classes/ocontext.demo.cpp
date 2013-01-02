/*====================================================================*
 *
 *   ocontext.demo.cpp 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <cstddef>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/tools.h"
#include "../classes/oflags.h"
#include "../classes/ogetoptv.hpp"
#include "../classes/oputoptv.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/oerror.cpp"
#include "../classes/ocontext.cpp"
#endif

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

static ocontext context;

/*====================================================================*
 *   
 *   static void show(char const *literal, char const *charset, bool mode);
 *
 *--------------------------------------------------------------------*/

static void show (char const *literal, unsigned c, bool mode) 

{
	std::cout << "literal=[" << literal << "]\n";
	std::cout << "charset=[" << c << "]\n";
	std::cout << "require=[" << mode << "]\n";
	std::cout << "prefix=[" << context.prefix () << "]\n";
	std::cout << "suffix=[" << context.suffix () << "]\n";
	std::cout << "\n";
	return;
}


/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const *argv []) 

{
	static char const *optv [] = 
	{
		"p:s:h",
		PUTOPTV_S_FILTER,
		"no description",
		"p cs\tprefix charset is cs [\"/\"]",
		"s cs\tsuffix charset is cs [\".\"]",
		"h\thelp summary",
		(char *) (0)
	};
	ogetoptv getopt (1);
	oputoptv putopt;
	static char prefix = '/';
	static char suffix = '.';
	signed c;
	while ((c = getopt.getoptv (argc, argv, optv)) != -1) 
	{
		switch ((char) (c)) 
		{
		case 'p':
			prefix = *getopt.optarg ();
			break;
		case 's':
			suffix = *getopt.optarg ();
			break;
		default:
			break;
		}
	}
	while ((getopt.argc () > 0) && (*getopt.argv () != (char *) (0))) 
	{
		std::cout << "first\n";
		context.split (*getopt.argv (), prefix, true, true);
		show (*getopt.argv (), prefix, true);
		context.split (*getopt.argv (), prefix, true, false);
		show (*getopt.argv (), prefix, false);
		context.split (*getopt.argv (), suffix, true, true);
		show (*getopt.argv (), suffix, true);
		context.split (*getopt.argv (), suffix, true, false);
		show (*getopt.argv (), suffix, false);
		std::cout << "split\n";
		context.split (*getopt.argv (), prefix, false, true);
		show (*getopt.argv (), prefix, true);
		context.split (*getopt.argv (), prefix, false, false);
		show (*getopt.argv (), prefix, false);
		context.split (*getopt.argv (), suffix, false, true);
		show (*getopt.argv (), suffix, true);
		context.split (*getopt.argv (), suffix, false, false);
		show (*getopt.argv (), suffix, false);
		std::cout << "\n";
		getopt++;
	}
	exit (0);
}

