/*====================================================================*
 *
 *   ocprocwords.cpp - definition of ocprocwords class.
 *
 *   symbol table of C Language Macro Processor keywords;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCPROCWORDS_SOURCE
#define oCPROCWORDS_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ocprocwords.hpp"

/*====================================================================*
 *
 *   ocprocwords();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ocprocwords::ocprocwords ()

{
	static char const * table [] = 
	{
		"define",
		"elif",
		"else",
		"endif",
		"error",
		"if",
		"ifdef",
		"ifndef",
		"include",
		"line",
		"pragma",
		"undef",
		(char const *) (0)
	};
	okeywords::mtitle = "cprocwords";
	okeywords::mcount = sizeof (table) / sizeof (table [0]) - 1;
	okeywords::mtable = table;
	okeywords::mcheck ();
	return;
}

/*====================================================================*
 *
 *   ~ocprocwords();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ocprocwords::~ ocprocwords ()

{
	return;
}

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif



