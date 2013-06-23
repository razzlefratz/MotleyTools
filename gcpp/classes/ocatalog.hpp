/*====================================================================*
 *
 *   ocatalog.hpp - interface for the ocatalog class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCATALOG_HEADER
#define oCATALOG_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstddef>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/olist.hpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ocatalog 

{
public:
	ocatalog ();
	ocatalog (signed order (char const *, char const *));
	virtual~ ocatalog ();
	char const * title () const;
	ocatalog & title (char const * string);
	unsigned index () const;
	unsigned count () const;
	char const * symbol ();
	char const * string ();
	char const * symbols (unsigned index);
	char const * strings (unsigned index);
	bool related (char const * symbol, char const * string);
	unsigned indexof (char const * symbol, char const * string);
	bool relate (char const * symbol, char const * string);
	ocatalog & clear ();
private:
	olist * mlist;
};

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

