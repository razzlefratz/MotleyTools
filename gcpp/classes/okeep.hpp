/*====================================================================*
 *
 *   okeep.hpp - interface for the okeep class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oKEEP_HEADER
#define oKEEP_HEADER

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec (dllexport) okeep 

{
public:
	okeep ();
	virtual~ okeep ();
	void * fetch (char const * string) const;
	void * store (char const * string, void * object);
private:
	char * mstring;
	void * mobject;
	okeep * mprior;
	okeep * mafter;
};

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

