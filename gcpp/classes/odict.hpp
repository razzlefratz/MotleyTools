/*====================================================================*
 *
 *   odict.hpp - interface for the odict class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oDICTIONARY_HEADER
#define oDICTIONARY_HEADER

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oqueue.hpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec (dllexport) odict 

{
public:
	odict (char const * symbol);
	odict (char const * symbol, char const * string);
	virtual~ odict ();
	bool defined (char const * symbol) const;
	char const * expand (char const * symbol) const;
	char const * lookup (char const * symbol) const;
	odict & define (char const * symbol, char const * string);
	odict & enumerate ();
	odict & clear ();
protected:
	private: static signed comp (char const *, char const *);
	const odict * node (char const *) const;
	odict * mprior;
	odict * mafter;
	char * msymbol;
	char * mstring;
};

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

