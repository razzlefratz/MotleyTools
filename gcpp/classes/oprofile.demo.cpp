/*====================================================================*
 *
 *   ofilespec.demo.cpp 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/oputoptv.hpp"
#include "../classes/oversion.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/oprofile.cpp"
#endif

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main(int argc, char const * argv[])

{
	static char const * optv[] = 
	{
		"",
		"filespec [filespec] ...",
		"ofilespec object class demonstration and test utility",
		(char const *)(0)
	};
	oprofile profile;
	ogetoptv getopt(1);
	oputoptv putopt;
	signed c;
	while ((c = getopt.getoptv(argc, argv, optv)) != - 1)
	{
		switch (c)
		{
		default: 
			break;
		}
	}

#if 0 while ((getopt.argc () > 0) && (*getopt.argv () != (char *) (0))) {getopt++; } #else cout << profile.lookup ("profile.ini", "cbar", "release", "Published 2006 by Charles Maier Associates Limited for internal use;") << "\n"; cout << profile.lookup ("profile.ini", "cbar", "license", "Licensed under the GNU General Public License version 2 or later;") << "\n"; #endif return (0); } 

	

