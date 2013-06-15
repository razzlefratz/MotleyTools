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

static void show (char const * literal, unsigned c, bool mode) 

{
	std::cout << "literal=[" << literal << "]" << std::endl;
	std::cout << "charset=[" << c << "]" << std::endl;
	std::cout << "require=[" << mode << "]" << std::endl;
	std::cout << "prefix=[" << context.prefix () << "]" << std::endl;
	std::cout << "suffix=[" << context.suffix () << "]" << std::endl;
	std::cout << std::endl;
	return;
}


/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
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
			prefix = * getopt.optarg ();
			break;
		case 's':
			suffix = * getopt.optarg ();
			break;
		default:
			break;
		}
	}
	while ((getopt.argc () > 0) && (* getopt.argv () != (char *) (0))) 
	{
		std::cout << "first" << std::endl;
		context.split (* getopt.argv (), prefix, true, true);
		show (* getopt.argv (), prefix, true);
		context.split (* getopt.argv (), prefix, true, false);
		show (* getopt.argv (), prefix, false);
		context.split (* getopt.argv (), suffix, true, true);
		show (* getopt.argv (), suffix, true);
		context.split (* getopt.argv (), suffix, true, false);
		show (* getopt.argv (), suffix, false);
		std::cout << "split" << std::endl;
		context.split (* getopt.argv (), prefix, false, true);
		show (* getopt.argv (), prefix, true);
		context.split (* getopt.argv (), prefix, false, false);
		show (* getopt.argv (), prefix, false);
		context.split (* getopt.argv (), suffix, false, true);
		show (* getopt.argv (), suffix, true);
		context.split (* getopt.argv (), suffix, false, false);
		show (* getopt.argv (), suffix, false);
		std::cout << std::endl;
		getopt++;
	}
	exit (0);
}


