/*====================================================================*
 *
 *   oHTMLEmpty.cpp - definition of oHTMLEmpty class.
 *
 *   symbol table containing empty HTML element names;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oHTMLEMPTY_SOURCE
#define oHTMLEMPTY_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oHTMLEmpty.hpp"

/*====================================================================*
 *
 *   oHTMLEmpty ();
 *   
 *   constructor for oHTMLEmpty class; replace the base class table with
 *   this one;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oHTMLEmpty::oHTMLEmpty () 

{
	static char const * table [] = 
	{
		"AREA",
		"BASE",
		"BASEFONT",
		"BR",
		"COL",
		"FRAME",
		"HR",
		"IMG",
		"INPUT",
		"ISINDEX",
		"LINK",
		"META",
		"PARAM",
		"area",
		"base",
		"basefont",
		"br",
		"col",
		"frame",
		"hr",
		"img",
		"input",
		"isindex",
		"link",
		"meta",
		"param",
		(char const *)(0)
	};
	okeywords::mtitle = "HTMLEmpty";
	okeywords::mcount = sizeof (table) / sizeof (char const *) - 1;
	okeywords::mtable = table;
	okeywords::mcheck ();
	return;
}


/*====================================================================*
 *
 *   ~oHTMLEmpty ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oHTMLEmpty::~oHTMLEmpty () 

{
	return;
}


/*====================================================================*
 *    end definition;
 *--------------------------------------------------------------------*/

#endif

