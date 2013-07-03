/*====================================================================*
 *
 *   ocontext.hpp - interface for the ocontext class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCONTEXT_HEADER
#define oCONTEXT_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ocontext 

{
public:
	ocontext ();
	virtual~ ocontext ();
	char const * string () const;
	char const * prefix () const;
	char const * suffix () const;
	ocontext & string (char buffer [], size_t length);
	ocontext & prefix (char buffer [], size_t length);
	ocontext & suffix (char buffer [], size_t length);
	ocontext & split (char const * string, char const * charset, bool first, bool required);
	ocontext & merge (char const * prefix, char const * middle, char const * suffix);
private:
	bool member (char const * charset, char c);
	char * mstring;
	char * mprefix;
	char * msuffix;
};

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

