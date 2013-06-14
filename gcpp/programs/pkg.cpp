/*====================================================================*
 *
 *   pkg.cpp - extract and print GNU/Linux package name components;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <cstdio>
#include <cstdlib>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/opackage.hpp"
#include "../classes/oflagword.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/opackage.cpp"
#include "../classes/oflagword.cpp"
#endif

/*====================================================================*
 *   program constants;  
 *--------------------------------------------------------------------*/

#define PKG_B_ARCHIVE (1 << 0)
#define PKG_B_PACKAGE (1 << 1)
#define PKG_B_PRODUCT (1 << 2)
#define PKG_B_RELEASE (1 << 3)
#define PKG_B_TRAILER (1 << 4)

/*====================================================================*
 *   program variables;  
 *--------------------------------------------------------------------*/

opackage package;

/*====================================================================*
 *
 *   void function (char const *string, oflagword * flags);
 *
 *
 *--------------------------------------------------------------------*/

static void function (char const * string, oflagword * flags) 

{
	package = string;
	switch (flags->getbits (PKG_B_ARCHIVE | PKG_B_PACKAGE | PKG_B_PRODUCT | PKG_B_RELEASE | PKG_B_TRAILER)) 
	{
	case PKG_B_ARCHIVE:
		std::cout << package.archive () << "\n";
		break;
	case PKG_B_PACKAGE:
		std::cout << package.package () << "\n";
		break;
	case PKG_B_PRODUCT:
		std::cout << package.product () << "\n";
		break;
	case PKG_B_RELEASE:
		std::cout << package.release () << "\n";
		break;
	case PKG_B_TRAILER:
		std::cout << package.trailer () << "\n";
		break;
	default:
		std::cout << package.archive () << "\n";
		break;
	}
	return;
}


/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"apkrex:",
		oPUTOPTV_S_DIVINE,
		"extract and output package name components",
		"a\tprint archive name",
		"k\tprint package name",
		"p\tprint product name",
		"r\tprint version number",
		"e\tprint file extension",
		"x s\tremove extender s [.tar.bz2]",
		(char const *) (0)
	};
	ogetoptv getopt;
	oflagword flags;
	signed c;
	while ((c = getopt.getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'a':
			flags.setbits (PKG_B_ARCHIVE);
			break;
		case 'k':
			flags.setbits (PKG_B_PACKAGE);
			break;
		case 'p':
			flags.setbits (PKG_B_PRODUCT);
			break;
		case 'r':
			flags.setbits (PKG_B_RELEASE);
			break;
		case 'e':
			flags.setbits (PKG_B_TRAILER);
			break;
		case 'x':
			package.extender (getopt.optarg ());
			break;
		default:
			break;
		}
	}
	if (!getopt.argc ()) 
	{
		char pathname [FILENAME_MAX];
		while (!std::cin.getline (pathname, sizeof (pathname)).eof ()) 
		{
			std::streamsize length = std::cin.gcount ();
			while (isspace (pathname [--length])) 
			{
				pathname [length] = (char) (0);
			}
			function ((char const *) (pathname), &flags);
		}
	}
	while (getopt.argc () && * getopt.argv ()) 
	{
		function (* getopt.argv (), &flags);
		getopt++;
	}
	std::exit (0);
}


