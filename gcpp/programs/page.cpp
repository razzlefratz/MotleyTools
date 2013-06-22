/*====================================================================*
 *
 *   cmpp.cpp - C Language Macro Preprocessor;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   system header files
 *--------------------------------------------------------------------*/

#include <cstdlib>
#include <fstream>
#include <iostream>

/*====================================================================*
 *   custom header files
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/opage.hpp"

/*====================================================================*
 *   custom header files
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/opage.cpp"
#include "../classes/otext.cpp"
#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [], char const * envp []) 

{
	static char const * optv [] = 
	{
		"",
		oPUTOPTV_S_FUNNEL,
		"paginate files",
		(char const *) (0)
	};
	ogetoptv getopt;
	std::fstream source;
	opage page ("Standard Input");
	signed c;
	while ((c = getopt.getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		default:
			break;
		}
	}
	if (!getopt.argc ()) 
	{
		page.title ("Standard Input");
		while (page.put (std::cin.get ()) != EOF);
	}
	while ((getopt.argc ()) && (* getopt.argv ())) 
	{
		source.open (* getopt.argv (), std::ifstream::in);
		if (source.good ()) 
		{
			std::cin.rdbuf (source.rdbuf ());
			page.title (* getopt.argv ());
			while (page.put (std::cin.get ()) != EOF);
			source.close ();
		}
		getopt++;
	}
	std::exit (0);
}

