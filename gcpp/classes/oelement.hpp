/*====================================================================*
 *
 *   oelement.hpp - interface for the oelement class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oELEMENT_HEADER
#define oELEMENT_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/otext.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oelement: private otext 

{
public:
	oelement (char const * scope, char const * title);
	oelement (char const * title);
	virtual ~ oelement ();
	char const * scope () const;
	char const * title () const;
	oelement & print ();
private:
	char * mscope;
	char * mtitle;
};


/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

