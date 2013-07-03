/*====================================================================*
 *
 *   oclangwords.cpp - definition of oclangwords class.
 *
 *   symbol table containing ANSI C reserved words;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCLANGWORDS_SOURCE
#define oCLANGWORDS_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oclangwords.hpp"
#include "../../gcc/tools/types.h"

/*====================================================================*
 *
 *   oclangwords ();
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oclangwords::oclangwords () 

{
	static char const * table [] = 
	{
		"auto",
		"break",
		"case",
		"char",
		"const",
		"continue",
		"default",
		"do",
		"double",
		"else",
		"entry",
		"enum",
		"extern",
		"float",
		"for",
		"goto",
		"if",
		"int",
		"long",
		"register",
		"return",
		"short",
		"signed",
		"sizeof",
		"static",
		"struct",
		"switch",
		"typedef",
		"typeof",
		"union",
		"unsigned",
		"void",
		"volatile",
		"while",
		(char const *) (0)
	};
	okeywords::mtitle = "clangwords";
	okeywords::mcount = SIZEOF (table) - 1;
	okeywords::mtable = table;
	okeywords::mcheck ();
	return;
}

/*====================================================================*
 *
 *   ~oclangwords ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oclangwords::~oclangwords () 

{
	return;
}

/*====================================================================*
 *    end definition;
 *--------------------------------------------------------------------*/

#endif

