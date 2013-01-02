/*====================================================================*
 *
 *   cf.c - simple sample c lang formatter demonstrating oscantext object;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <cstdio>
#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oflags.h"
#include "../classes/stdafx.hpp"
#include "../classes/ogetopt.hpp"
#include "../classes/oputopt.hpp"
#include "../classes/octext.hpp"
#include "../classes/oformat.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "strlib.h"
#include "strxcmp.c"
#include "../classes/ogetopt.cpp"
#include "../classes/oscantext.cpp"
#include "../classes/ocursor.cpp"
#include "../classes/oformat.cpp"
#include "../classes/ochrupr.cpp"
#include "../classes/ochrlwr.cpp"
#include "../classes/ochrclass.cpp"

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const *argv []) 

{
	static char const *usage [] = 
	{
		"oformat.demo",
		"h",
		PUTOPT_S_FUNNEL,
		"demo and test the oformat object",
		"h\thelp summary ",
		NULL
	};
	ogetopt options (1);
	oformat format;
	signed c;
	while ((c = options.getopt (argc, argv, usage [PUTOPT_I_OPTIONS])) != -1) 
	{
		switch (c) 
		{
		case 'h':
			options.putopt (usage);
		default:
			break;
		}
	}
	format.indent (4).offset (0);
	for (c = 0; c < 100; c++) 
	{
		if (c%13==0) 
		{
			format.flush (1);
			format.offset (0);
			format.print ("xxx");
			format.offset (4);
		}
		format.print ("abcd");
		format.space (2);
		format.shift (16);
	}
	format.flush (0);
	exit (0);
}

