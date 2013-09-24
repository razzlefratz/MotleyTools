/*====================================================================*
 *
 *   otext.hpp - interface for the otext class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oTEXT_HEADER
#define oTEXT_HEADER

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) otext

{
public: 
	static char * replace (char * buffer, char const * string);
	static char * save (char const * string);
};

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif



