/*====================================================================*
 *
 *   ochroct.hpp - interface for the ochroct class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCHROCT_HEADER
#define oCHROCT_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ochroct 

{
public:
	ochroct ();
	virtual~ ochroct ();
	static char const * digits;
	static char * tooctal (char * string, unsigned c);
	static char * tounix (char * string, unsigned c);
private:
	
};


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

