/*====================================================================*
 *
 *   oconstants.cpp - definition of oconstants class.
 *
 *   symbol table containing standard C library function names;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCONSTANTS_SOURCE
#define oCONSTANTS_SOURCE

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../classes/oconstants.hpp"
#include "../../gcc/tools/types.h"

/*====================================================================*
 *
 *   oconstants();
 *
 *
 *--------------------------------------------------------------------*/

oconstants::oconstants () 

{
	static char const * table [] = 
	{
		"CHAR_BIT",
		"CHAR_MAX",
		"CHAR_MIN",
		"DBL_DIG",
		"DBL_EPSILON",
		"DBL_MANT_DIG",
		"DBL_MAX",
		"DBL_MAX_EXP",
		"DBL_MIN",
		"DBL_MIN_EXP",
		"EOF",
		"FILE",
		"FLT_DIG",
		"FLT_EPSILON",
		"FLT_MANT_DIG",
		"FLT_MAX",
		"FLT_MAX_EXP",
		"FLT_MIN",
		"FLT_MIN_EXP",
		"FLT_RADIX",
		"FLT_ROUNDS",
		"INT_MAX",
		"INT_MIN",
		"LONG_MAX",
		"LONG_MIN",
		"NULL",
		"SCHAR_MAX",
		"SCHAR_MIN",
		"SHRT_MAX",
		"SHRT_MIN",
		"UCHAR_MAX",
		"UINT_MAX",
		"ULONG_MAX",
		"USHRT_MAX",
		(char const *)(0)
	};
	okeywords::mtitle = "constants";
	okeywords::mcount = SIZEOF (table) - 1;
	okeywords::mtable = table;
	okeywords::mcheck ();
	return;
}

/*====================================================================*
 *
 *   ~oconstants();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oconstants::~oconstants () 

{
	return;
}

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

