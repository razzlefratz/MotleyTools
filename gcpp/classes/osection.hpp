/*====================================================================*
 *
 *   osection.hpp - interface for the osection classr;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSECTION_HEADER
#define oSECTION_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   class constants;    
 *--------------------------------------------------------------------*/

#define oSECTION_BARWIDTH 68

/*====================================================================*
 *   class interface;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) osection 

{
public:
	osection ();
	virtual ~ osection ();
	osection & width (size_t width);
	osection & title (char const * title);
private:
	char * mstart;
	char * mupper;
	char * mlower;
};


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

