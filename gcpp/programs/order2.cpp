/*====================================================================*
 *
 *   order.c - topological sort program;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdlib>
#include <fstream>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/ograph.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/oflagword.cpp"
#include "../classes/oerror.cpp"
#include "../classes/oascii.cpp"
#include "../classes/ograph.cpp"
#include "../classes/oedges.cpp"
#include "../classes/onodes.cpp"
#include "../classes/oedge.cpp"
#include "../classes/onode.cpp"
#include "../classes/otext.cpp"
#endif

/*====================================================================*
 *   program constants;  
 *--------------------------------------------------------------------*/

#define ORDER_B_INVERT (1 << 0)
#define ORDER_B_COUNT (1 << 1)
#define ORDER_B_LEVEL (1 << 2)
#define ORDER_B_LEAVE (1 << 3)
#define ORDER_B_ORDER (1 << 4)

#define ORDER_C_SEPARATOR  ':'
#define ORDER_C_TERMINATOR ';'

/*====================================================================*
 *
 *   int main (int argc, char const * argv[]);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	static char const * optv [] = 
	{ 
		"loxst", 
		oPUTOPTV_S_FUNNEL, 
		"topological sort program", 
		"l\tprint level", 
		"o\tprint order", 
		"s\tprint symbol", 
		"t\tprint structure", 
		"x\tinvert order", 
		(char const *) (0)
	}; 
	std::ifstream stream; 
	ogetoptv getopt; 
	oputoptv putopt; 
	ograph graph; 
	signed c; 
	while (~ (c = getopt.getoptv (argc, argv, optv))) 
	{ 
		switch (c) 
		{ 
		case 'l': 
			graph.setbits (oGRAPH_SHOW_LEVEL); 
			break; 
		case 'o': 
			graph.setbits (oGRAPH_SHOW_ORDER); 
			break; 
		case 's': 
			graph.setbits (oGRAPH_SHOW_SYMBOL); 
			graph.clearbits (oGRAPH_SHOW_SYMBOL); 
			break; 
		case 't': 
			graph.setbits (oGRAPH_SHOW_STRUCT); 
			graph.clearbits (oGRAPH_SHOW_STRUCT); 
			break; 
		case 'x': 
			graph.setbits (oGRAPH_MODE_INVERT); 
			break; 
		default: 
			break; 
		} 
	} 
	if (! getopt.argc ()) 
	{ 
		graph.populate (ORDER_C_SEPARATOR, ORDER_C_TERMINATOR); 
	} 
	while (getopt.argc () && * getopt.argv ()) 
	{ 
		stream.open (* getopt.argv (), std::ifstream::in); 
		if (stream.good ()) 
		{ 
			std::cin.rdbuf (stream.rdbuf ()); 
			graph.populate (ORDER_C_SEPARATOR, ORDER_C_TERMINATOR); 
			stream.close (); 
		} 
		getopt++; 
	} 
	graph.discover (); 
	std::exit (0); 
} 

