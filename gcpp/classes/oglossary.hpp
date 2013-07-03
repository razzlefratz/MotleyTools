/*====================================================================*
 *
 *   oglossary.hpp - interface for the oHeap class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oGLOSSARY_HEADER
#define oGLOSSARY_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstddef>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oitem.hpp"
#include "../classes/olist.hpp"

/*====================================================================*
 *7
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oglossary 

{
public:
	oglossary ();
	oglossary (signed order (char const *, char const *));
	virtual~ oglossary ();
	char const * title () const;
	oglossary & title (char const * string);
	size_t index () const;
	size_t count () const;
	char const * symbol () const;
	char const * string () const;
	char const * symbols (size_t index) const;
	char const * strings (size_t index) const;
	bool defined (char const * symbol);
	size_t indexof (char const * symbol);
	bool define (char const * symbol, char const * string);
	bool create (char const * symbol, char const * string);
	bool assign (char const * symbol, char const * string);
	char const * lookup (char const * symbol);
	char const * expand (char const * symbol);
	oglossary & clear ();
private:
	olist * mlist;
};

/*====================================================================*
 *   end class declaration;
 *--------------------------------------------------------------------*/

#endif

