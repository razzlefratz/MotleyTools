/*====================================================================*
 *
 *   ohexencode.hpp - interface for the ohexencode class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oHEXENCODE_HEADER
#define oHEXENCODE_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   start class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ohexencode 

{
public:
	ohexencode ();
	virtual~ ohexencode ();
	static char * octet (char * string, char const c);
	static char * literal (char * string, char const c);
	static char * clang (char * string, char const c);
	static char * iso (char * string, char const c);
	static char * html (char * string, char const c);
	static char * ietf (char * string, char const c);
private:
	static char const mdigit [];
};

/*====================================================================*
 *   end class declaration;
 *--------------------------------------------------------------------*/

#endif

