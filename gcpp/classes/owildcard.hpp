/*====================================================================*
 *
 *   owildcard.hpp - interface for the owildcard class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oWILDCARD_HEADER
#define oWILDCARD_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) owildcard 

{
public:
	owildcard ();
	owildcard (unsigned char anychar, unsigned char allchar);
	virtual~ owildcard ();
	bool match (char const * literal, char const * pattern);
protected:
	private: unsigned char anychar;
	unsigned char allchar;
};


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

