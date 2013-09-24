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
	virtual ~ ocontext ();
	char const * prefix () const;
	char const * suffix () const;
	ocontext & prefix (char buffer [], size_t length);
	ocontext & suffix (char buffer [], size_t length);
	ocontext & split (char const * string, char c, bool initial, bool required);
private: 
	bool member (char const * charset, char c);
	ocontext & copy (char const * string, char buffer [], size_t length);
	char * mstring;
	char * mprefix;
	char * msuffix;
};

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



