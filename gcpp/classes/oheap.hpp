/*====================================================================*
 *
 *   oheap.hpp - interface for the oheap class.
 *
 *   this object implements a head using sequential storage; it is used
 *   t   by the oagenda object class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oHEAP_HEADER
#define oHEAP_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstddef>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oitem.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oheap

{
public: 
	oheap ();
	oheap (int order (char const *, char const *));
	virtual ~ oheap ();
	oitem * item () const;
	char const * title () const;
	oheap & title (char const * string);
	size_t count () const;
	oitem * item ();
	oheap & insertitem (oitem * item);
	oheap & clear ();
private: 
	char * mtitle;
	oitem ** mtable;
	signed (* morder) (char const *, char const *);
	unsigned mstart;
	unsigned mblock;
	unsigned mlimit;
	unsigned mcount;
	unsigned mlower;
	unsigned mupper;
};

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif



