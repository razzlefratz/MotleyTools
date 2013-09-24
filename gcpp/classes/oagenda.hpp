/*====================================================================*
 *
 *   oagenda.hpp - oagenda class declaration;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oAGENDA_HEADER
#define oAGENDA_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include <cstddef>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oheap.hpp"

/*====================================================================*
 *   interface declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oagenda

{
public: 
	oagenda ();
	oagenda (signed comp (char const *, char const *));
	virtual ~ oagenda ();
	unsigned count () const;
	char const * event () const;
	char const * title () const;
	oagenda & insert (char const * event);
	oagenda & insert (char const * event, char const * title);
	oagenda & remove ();
	oagenda & clear ();
private: 
	oheap * mheap;
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif



