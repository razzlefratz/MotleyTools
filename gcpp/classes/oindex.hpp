/*====================================================================*
 *
 *   oindex.hpp - interface for the oindex class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oINDEX_HEADER
#define oINDEX_HEADER

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oindex 

{
public:
	oindex ();
	virtual ~ oindex ();
	static unsigned qmod (signed domain, signed range);
	static unsigned pmod (signed domain, signed range);
protected:
	private:
};

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

