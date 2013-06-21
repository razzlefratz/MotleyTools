/*====================================================================*
 *
 *   oprefix.hpp - interface for the oprefix class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPREFIX_HEADER
#define oPREFIX_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdio>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *7
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oprefix 

{
public:
	oprefix ();
	oprefix (const unsigned c);
	virtual~ oprefix ();
	oprefix * lookup (char const * symbol);
	char const * assume (char const * symbol) const;
	char const * revise (char const * symbol) const;
	char const * prefix (char const * symbol) const;
	char const * suffix (char const * symbol) const;
	oprefix & define (char const * symbol, char const * string);
	oprefix & report (char * buffer, size_t length);
private:
	char msymbol;
	char * mstring;
	oprefix * mprior;
	oprefix * mafter;
	oprefix * mequal;
};


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

