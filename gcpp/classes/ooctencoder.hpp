/*====================================================================*
 *
 *   ooctencoder.hpp - interface for the ooctencoder class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oOCTENCODER_HEADER
#define oOCTENCODER_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ooctencoder 

{
public:
	ooctencoder ();
	virtual ~ ooctencoder ();
	char *encode (char const *string);
	char *decode (char *string);
private:
	static char const mdigit [];
	char *mbuffer;
	size_t mlength;
};


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

