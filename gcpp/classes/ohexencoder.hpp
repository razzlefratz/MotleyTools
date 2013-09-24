/*====================================================================*
 *
 *   ohexencoder.hpp - interface for the ohexencoder class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oHEXENCODER_HEADER
#define oHEXENCODER_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/ochrupr.hpp"
#include "../classes/oascii.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec(dllexport) ohexencoder: private oascii

{
public: 
	ohexencoder ();
	virtual ~ ohexencoder();
	static char * encode(char const * string);
	static char * decode(char * string);
private: 
	static ochrupr mchrupr;
	static char const mdigit[];
	char * mbuffer;
	size_t mlength;
};

/*====================================================================*
 *   end definiton;
 *--------------------------------------------------------------------*/

#endif



