/*====================================================================*
 *
 *   ochrhex.hpp - interface for the ochrhex class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCHRHEX_HEADER
#define oCHRHEX_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ochrhex 

{
public:
	ochrhex ();
	virtual~ ochrhex ();
	static char const * digits;
	static char * tohex (char * string, unsigned c);
	static char * toiso (char * string, unsigned c);
	static char * tohtml (char * string, unsigned c);
	static char * toietf (char * string, unsigned c);
	static char * toconst (char * string, unsigned c);
private:
	
};

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

