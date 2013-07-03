/*====================================================================*
 *
 *   dep.filepp - output c language include file dependency list;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <cstddef>
#include <cstring>

#include <dirent.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/oputoptv.hpp"
#include "../classes/oversion.hpp"
#include "../classes/oscantext.hpp"
#include "../classes/ofilespec.hpp"
#include "../classes/ofileopen.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/ofileopen.cpp"
#include "../classes/ofilespec.cpp"
#include "../classes/otext.cpp"
#include "../classes/oerror.cpp"
#include "../classes/ocontext.cpp"
#include "../classes/oscantext.cpp"
#include "../classes/ochrtbl.cpp"
#include "../classes/ochrupr.cpp"
#include "../classes/ochrlwr.cpp"
#include "../classes/oascii.cpp"
#include "../classes/ocursor.cpp"
#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

ofileopen fileopen;

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"",
		PUTOPTV_S_FILTER,
		"demonstrate ofileopen object featureS",
		(char const *) (0)
	};
	ogetoptv getopt (1);
	oputoptv putopt;
	flag_t flags = (flag_t) (0);
	signed c;
	while ((c = getopt.getoptv (argc, argv, optv)) != -1) 
	{
		switch ((char) (c)) 
		{
		default:
			break;
		}
	}
	while ((getopt.argc () > 0) && (* getopt.argv () != (char *) (0))) 
	{
		if (fileopen.opensave (* getopt.argv (), "bak")) 
		{
		}
		getopt++;
	}
	return (0);
}

