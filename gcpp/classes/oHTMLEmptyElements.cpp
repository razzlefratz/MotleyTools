/*====================================================================*
 *
 *   oHTMLEmptyElements.cpp - definition of oHTMLEmptyElements class.
 *
 *   symbol table containing empty HTML element names;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oHTMLEMPTYELEMENTS_SOURCE
#define oHTMLEMPTYELEMENTS_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oHTMLEmptyElements.hpp"
#include "../classes/otypes.hpp"

/*====================================================================*
 *
 *   oHTMLEmptyElements ();
 *   
 *   constructor for oHTMLEmptyElements class; replace the base class table with
 *   this one;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oHTMLEmptyElements::oHTMLEmptyElements () 

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
	okeywords::mcount = SIZEOF (table) - 1;
	okeywords::mtable = table;
	okeywords::mcheck ();
	return;
}

/*====================================================================*
 *
 *   ~oHTMLEmptyElements ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oHTMLEmptyElements::~oHTMLEmptyElements () 

{
	return;
}

/*====================================================================*
 *    end definition;
 *--------------------------------------------------------------------*/

#endif

