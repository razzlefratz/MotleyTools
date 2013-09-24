/*====================================================================*
 *
 *   otext.cpp - implementation of the otext class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oTEXT_SOURCE
#define oTEXT_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/otext.hpp"

/*====================================================================*
 *
 *   char * replace (char * memory, char const * string);
 *
 *   replace buffer with string only if their values differ;
 *
 *--------------------------------------------------------------------*/

char * otext::replace (char * memory, char const * string)

{
	if (std::strcmp (memory, string))
	{
		delete [] memory;
		memory = otext::save (string);
	}
	return (memory);
}

/*====================================================================*
 *
 *   char const * save (char const * string);
 *
 *--------------------------------------------------------------------*/

char * otext::save (char const * string)

{
	char * memory = new char [std::strlen (string) +  1];
	std::strcpy (memory, string);
	return (memory);
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif



