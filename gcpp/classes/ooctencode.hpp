/*====================================================================*
 *
 *   ooctencode.hpp - interface for the ooctencode class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oOCTENCODE_HEADER
#define oOCTENCODE_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   start class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ooctencode

{
public: 
	ooctencode ();
	virtual ~ ooctencode ();
	static char * numeric (char * string, const unsigned c);
	static char * literal (char * string, const unsigned c);
private: 
	static char const mdigit [];
};

/*====================================================================*
 *   end class declaration;
 *--------------------------------------------------------------------*/

#endif



