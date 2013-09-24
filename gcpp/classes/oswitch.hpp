/*====================================================================*
 *
 *   oswitch.hpp - declaration of oswitch class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSWITCH_HEADER
#define oSWITCH_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oswitch

{
public: 
	oswitch ();
	virtual ~ oswitch ();
	bool state (char const * string, bool state);
private: 
	static char const * mstate [];
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif



