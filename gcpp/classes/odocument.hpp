/*====================================================================*
 *
 *   owebpage.hpp - interface for the owebpage class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oDOCUMENT_HEADER
#define oDOCUMENT_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdio>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/otree.hpp"

/*====================================================================*
 * 
 *--------------------------------------------------------------------*/

class __declspec(dllexport) odocument

{
public: 
	odocument ();
	virtual ~ odocument();
	char const * title() const;
	odocument & title(char const * title);
private: 
	char * mtitle;
	otree root;
	otree temp;
};

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



