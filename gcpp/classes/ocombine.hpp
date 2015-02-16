/*====================================================================*
 *
 *   ocombine.hpp - interface for the ocombine class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCOMBINE_HEADER
#define oCOMBINE_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ocombine

{
public: 
	ocombine ();
	virtual ~ ocombine ();
	char const * string () const;
	char const * prefix () const;
	char const * suffix () const;
	ocombine & string (char buffer [], size_t length);
	ocombine & prefix (char buffer [], size_t length);
	ocombine & suffix (char buffer [], size_t length);
	ocombine & split (char const * string, char const * charset, bool first, bool required);
	ocombine & merge (char const * prefix, char const * middle, char const * suffix);
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



