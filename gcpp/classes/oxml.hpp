/*====================================================================*
 *
 *   oxml.hpp - interface for the oxml class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oXML_HEADER
#define oXML_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/omarkup.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oxml: public omarkup 

{
public:
	oxml ();
	virtual~ oxml ();
	char quote () const;
	oxml & quote (signed c);
	char const * element () const;
	char const * attribute () const;
	char const * value () const;
	signed page (signed c);
	signed element (signed c);
	signed content (signed c);
	signed xml (signed c);
protected:
	private:
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

