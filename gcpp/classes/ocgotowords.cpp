/*====================================================================*
 *
 *   ocgotowords.cpp - definition of ocgotowords class.
 *
 *   symbol table of C Language labels;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCGOTOWORD_SOURCE
#define oCGOTOWORD_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ocgotowords.hpp"
#include "../../gcc/tools/types.h"

/*====================================================================*
 *
 *   ocgotowords();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ocgotowords::ocgotowords () 

{
	static char const * table [] = 
	{
		"default",
		"private",
		"protected",
		"public",
		(char const *)(0)
	};
	okeywords::mtitle = "cgotowords";
	okeywords::mcount = SIZEOF (table) - 1;
	okeywords::mtable = table;
	okeywords::mcheck ();
	return;
}

/*====================================================================*
 *
 *   ~ocgotowords();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ocgotowords::~ocgotowords () 

{
	return;
}

/*====================================================================*
 *   end definition
 *--------------------------------------------------------------------*/

#endif

