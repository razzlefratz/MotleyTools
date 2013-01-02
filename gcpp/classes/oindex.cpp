/*====================================================================*
 *
 *   oindex.cpp - implementation of the oindex class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oINDEX_SOURCE
#define oINDEX_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oindex.hpp"

/*====================================================================*
 *
 *   unsigned qmod (signed domain, unsigned range)
 *
 *   convert signed integer index to a positive integer in the range
 *   0 through range-1;
 *
 *--------------------------------------------------------------------*/

unsigned oindex::qmod (signed domain, signed range) 

{
	domain %= range;
	if (range < 0) 
	{
		return ((domain < 0)? (domain - range): (domain));
	}
	if (range > 0) 
	{
		return ((domain < 0)? (domain + range): (domain));
	}
	return (0);
}


/*====================================================================*
 *
 *   unsigned pmod (signed domain, unsigned range)
 *
 *   convert signed integer index to a positive integer in the range
 *   1 through range;
 *
 *--------------------------------------------------------------------*/

unsigned oindex::pmod (signed domain, signed range) 

{
	domain %= range;
	if (range < 0) 
	{
		return ((domain > 0)? (domain): (domain - range));
	}
	if (range > 0) 
	{
		return ((domain > 0)? (domain): (domain + range));
	}
	return (0);
}


/*====================================================================*
 *
 *   oindex ();
 *
 *   nothing to do;
 *
 *--------------------------------------------------------------------*/

oindex::oindex () 

{
	return;
}


/*====================================================================*
 *
 *   ~oindex ();
 *
 *   nothing to do;
 *
 *--------------------------------------------------------------------*/

oindex::~oindex () 

{
	return;
}


/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

