/*====================================================================*
 *
 *   cfm.cpp - format C/C++ source files;
 *
 *   custom C/C++ source code formatter;
 *
 *.  Motley Tools by Charles Maier <cmaier@cmassoc.net>;
 *:  Copyright 2001-2006 by Charles Maier Associates;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

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
		"", 
		oPUTOPTV_S_FILTER, 
		"enumerate character sets", 
		(char const * ) (0)
	}; 
	ogetoptv getopt; 
	signed c; 
	while ((c = getopt.getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		default: 
			break; 
		} 
	} 
	if (! getopt.argc ()) 
	{ 
	} 
	while (getopt.argc () && * getopt.argv ()) 
	{ 
		getopt++ ; 
	} 
	std::printf ("arith"); 
	for (c = 0; c < 127; c++ ) 
	{ 
		if (oascii::isarith (c)) 
		{ 
			std::printf (" %c", c); 
		} 
	} 
	std::printf ("\n"); 
	std::printf ("logic"); 
	for (c = 0; c < 127; c++ ) 
	{ 
		if (oascii::islogic (c)) 
		{ 
			std::printf (" %c", c); 
		} 
	} 
	std::printf ("\n"); 
	std::printf ("group"); 
	for (c = 0; c < 127; c++ ) 
	{ 
		if (oascii::isgroup (c)) 
		{ 
			std::printf (" %c", c); 
		} 
	} 
	std::printf ("\n"); 
	std::printf ("quote"); 
	for (c = 0; c < 127; c++ ) 
	{ 
		if (oascii::isquote (c)) 
		{ 
			std::printf (" %c", c); 
		} 
	} 
	std::printf ("\n"); 
	std::printf ("punct"); 
	for (c = 0; c < 127; c++ ) 
	{ 
		if (oascii::ispunct (c)) 
		{ 
			std::printf (" %c", c); 
		} 
	} 
	std::printf ("\n"); 
	std::exit (0); 
} 

