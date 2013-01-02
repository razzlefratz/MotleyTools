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
 *   char * replace (char * buffer, char const * string);
 *
 *   replace buffer with string only if their values differ;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char * otext::replace (char * buffer, char const * string) 

{
	if (std::strcmp (buffer, string)) 
	{
		delete [] buffer;
		buffer = otext::save (string);
	}
	return (buffer);
}


/*====================================================================*
 *
 *   char const *otext::save(char const * string);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char *otext::save (char const * string) 

{
	char *buffer = new char [strlen (string) + 1];
	std::strcpy (buffer, string);
	return (buffer);
}


/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

