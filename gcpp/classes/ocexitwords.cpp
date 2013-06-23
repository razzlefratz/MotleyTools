/*====================================================================*
 *
 *   ocexitwords.cpp - definition of ocexitwords class.
 *
 *   symbol table of C Language labels;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCEXITWORD_SOURCE
#define oCEXITWORD_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ocexitwords.hpp"
#include "../classes/types.h"

/*====================================================================*
 *
 *   ocexitwords();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ocexitwords::ocexitwords () 

{
	static char const * table [] = 
	{
		"_Exit",
		"_exit",
		"atexit",
		"exit",
		"return",
		(char const *)(0)
	};
	okeywords::mtitle = "cexitwords";
	okeywords::mcount = SIZEOF (table) - 1;
	okeywords::mtable = table;
	okeywords::mcheck ();
	return;
}

/*====================================================================*
 *
 *   ~ocexitwords();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ocexitwords::~ocexitwords () 

{
	return;
}

/*====================================================================*
 *   end definition
 *--------------------------------------------------------------------*/

#endif

