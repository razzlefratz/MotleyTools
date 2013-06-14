/*====================================================================*
 *
 *   ochrtbl.hpp - interface for the ochrtbl class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCHRTBL_HEADER
#define oCHRTBL_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ochrtbl 

{
public:
	ochrtbl ();
	virtual ~ ochrtbl ();
	unsigned convert (unsigned c) const;
	signed compare (char const * string1, char const * string2) const;
	ochrtbl & convert (char * string);
protected:
	const unsigned char * mtable;
private:
	unsigned c;
};


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

