/*====================================================================*
 *
 *   ocpluswords.cpp - definition of ocpluswords class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCPLUSWORDS_SOURCE
#define oCPLUSWORDS_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ocpluswords.hpp"
#include "../classes/types.h"

/*====================================================================*
 * 
 *   ocpluswords ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ocpluswords::ocpluswords () 

{
	static char const * table [] = 
	{
		"__based",
		"__cdecl",
		"__declspecbool",
		"__exceptcatch",
		"__fastcall",
		"__finally",
		"__inline",
		"__int16",
		"__int32",
		"__int64",
		"__int8",
		"__leave",
		"__stdcall",
		"__uuidof",
		"_try",
		"auto",
		"bool",
		"break",
		"case",
		"char",
		"class",
		"const",
		"continue",
		"default",
		"delete",
		"dllexport",
		"dllimport",
		"do",
		"double",
		"dynamic_cast",
		"else",
		"entry",
		"enum",
		"extern",
		"false",
		"float",
		"for",
		"friend",
		"goto",
		"if",
		"inline",
		"int",
		"long",
		"main",
		"mutable",
		"naked",
		"namespace",
		"new",
		"noreturn",
		"operator",
		"private",
		"protected",
		"public",
		"register",
		"reinterpret_cast",
		"return",
		"short",
		"signed",
		"sizeof",
		"static",
		"static_cast",
		"struct",
		"switch",
		"template",
		"this",
		"thread",
		"throw",
		"true",
		"try",
		"typedef",
		"typeid",
		"typename",
		"union",
		"unsigned",
		"using",
		"uuid",
		"virtual",
		"void",
		"volatile",
		"while",
		"wmain",
		(char const *) (0)
	};
	okeywords::mtitle = "cpluswords";
	okeywords::mcount = SIZEOF (table) - 1;
	okeywords::mtable = table;
	okeywords::mcheck ();
	return;
}


/*====================================================================*
 * 
 *   ~ ocpluswords ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ocpluswords::~ocpluswords () 

{
	return;
}


/*====================================================================*
 *  end definition
 *--------------------------------------------------------------------*/

#endif

