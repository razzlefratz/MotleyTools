/*====================================================================*
 *
 *   otruth.hpp - declaration of otruth class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oTRUTH_HEADER
#define oTRUTH_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/ocode.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) otruth: public ocode 

{
public:
	otruth ();
	virtual ~ otruth ();
protected:
private:
	static const size_t count;
	static const struct _code_ table [];
};


/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

